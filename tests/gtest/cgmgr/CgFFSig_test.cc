
/// @file CgFFSig_test.cc
/// @brief CgFFSig_test の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "cgmgr/CgSignature.h"
#include "ym/PermGen.h"
#include "ym/MultiCombiGen.h"
#include "ym/MultiPermGen.h"
#include "ym/ClibIOMap.h"
#include "ym/ClibSeqAttr.h"


BEGIN_NAMESPACE_YM_CLIB

// FF の情報
struct FFSpec
{
  SizeType mNi;
  SizeType mNo;
  SizeType mNb;
  vector<TvFunc> mFuncList;
  vector<TvFunc> mTristateList;
  TvFunc mClockedOn;
  TvFunc mClockedOnAlso;
  TvFunc mNextState;
  TvFunc mClear;
  TvFunc mPreset;
  ClibSeqAttr mSeqAttr;
};

BEGIN_NONAMESPACE


// 真理値表を取り出す．
vector<bool>
extract_table(
  const TvFunc& func
)
{
  if ( func.is_invalid() ) {
    return vector<bool>{};
  }

  SizeType ni_exp = 1 << func.input_num();
  vector<bool> ans(ni_exp);
  for ( SizeType i = 0; i < ni_exp; ++ i ) {
    ans[i] = func.value(i);
  }
  return ans;
}

void
dump_hex(
  ostream& s,
  SizeType val
)
{
  if ( val < 10 ) {
    s << val;
  }
  else {
    s << static_cast<char>('A' + val - 10);
  }
}

// 結果のHEX文字列を作る．
string
to_hex(
  const vector<bool>& table ///< [in] 真理値表
)
{
  SizeType n = table.size();
  ostringstream buf;
  SizeType val = 0;
  SizeType count = 0;
  for ( auto v: table ) {
    val <<= 1;
    if ( v ) {
      val |= 1;
    }
    ++ count;
    if ( count == 4 ) {
      dump_hex(buf, val);
      val = 0;
      count = 0;
    }
  }
  if ( count > 0 ) {
    dump_hex(buf, val);
  }
  return buf.str();
}

string
cpv_to_str(
  ClibCPV cpv
)
{
  switch ( cpv ) {
  case ClibCPV::L: return "L";
  case ClibCPV::H: return "H";
  case ClibCPV::N: return "N";
  case ClibCPV::T: return "T";
  case ClibCPV::X: return "X";
  }
  return string{};
}

// CgSignature::str() の期待値を作る．
string
gen_str(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<vector<bool>>& func_table_list,
  const vector<vector<bool>>& tristate_table_list,
  ClibSeqAttr seq_attr
)
{
  ostringstream buf;
  buf << "F"
      << cpv_to_str(seq_attr.cpv1())
      << cpv_to_str(seq_attr.cpv2()) << ":"
      << ni << ":" << no << ":" << nb;
  SizeType n = func_table_list.size();
  for ( SizeType i = 0; i < n; ++ i ) {
    buf << ":" << to_hex(func_table_list[i])
	<< ":" << to_hex(tristate_table_list[i]);
  }
  return buf.str();
}

// 真理値表を変換する．
vector<bool>
xform_table(
  const vector<bool>& table,
  bool oinv,
  const vector<bool>& ipol_list,
  const vector<bool>& bpol_list,
  const PermGen& ipg,
  const PermGen& bpg
)
{
  SizeType ni_exp = table.size();
  if ( ni_exp == 0 ) {
    return vector<bool>{};
  }

  SizeType ni = 0;
  while ( (1 << ni) < ni_exp ) {
    ++ ni;
  }
  vector<bool> ans(ni_exp, false);
  for ( SizeType bits = 0; bits < ni_exp; ++ bits ) {
    vector<bool> ival(ni, false);
    for ( SizeType i = 0; i < ni; ++ i ) {
      if ( bits & (1 << i) ) {
	ival[i] = true;
      }
    }
    SizeType xbits = 0;
    for ( SizeType i = 0; i < ni; ++ i ) {
      SizeType j = ipg(i);
      if ( ival[i] ^ ipol_list[i] ) {
	xbits |= 1 << j;
      }
    }
    if ( table[xbits] ^ oinv ) {
      ans[bits] = true;
    }
  }
  return ans;
}

END_NONAMESPACE


void
check(
  const FFSpec& spec
)
{
  auto sig = CgSignature::make_ff_sig(spec.mNi, spec.mNo, spec.mNb,
				      spec.mFuncList,
				      spec.mTristateList,
				      spec.mClockedOn,
				      spec.mClockedOnAlso,
				      spec.mNextState,
				      spec.mClear,
				      spec.mPreset,
				      spec.mSeqAttr);

  SizeType ni = spec.mNi;
  SizeType no = spec.mNo;
  SizeType nb = spec.mNb;
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;
  SizeType ni3 = ni2 + 2; // IQ と IXQ
  SizeType no3 = no2 + 5; // clock, clock2, next_state, clear, preset

  SizeType ni_exp = 1 << ni3;

  // mFunc の真理値表を取り出す．
  vector<vector<bool>> func_table_list(no3);
  vector<vector<bool>> tristate_table_list(no3, vector<bool>{});
  for ( SizeType o = 0; o < no2; ++ o ) {
    func_table_list[o] = extract_table(spec.mFuncList[o]);
    // mTristate の真理値表を取り出す．
    tristate_table_list[o] = extract_table(spec.mTristateList[o]);
  }
  func_table_list[no2 + 0] = extract_table(spec.mClockedOn);
  func_table_list[no2 + 1] = extract_table(spec.mClockedOnAlso);
  func_table_list[no2 + 2] = extract_table(spec.mNextState);
  func_table_list[no2 + 3] = extract_table(spec.mClear);
  func_table_list[no2 + 4] = extract_table(spec.mPreset);

  // str() の期待値を作る．
  auto exp_str = gen_str(ni, no, nb,
			 func_table_list,
			 tristate_table_list,
			 spec.mSeqAttr);
  EXPECT_EQ( exp_str, sig.str() );

  // 代表シグネチャを求める．
  auto iomap = sig.rep_map();
  auto rep_sig = sig.xform(iomap);
  auto rep_str = rep_sig.str();

  // 同位体変換のチェック
  auto idmap_list = sig.idmap_list();
  for ( const auto& idmap: idmap_list ) {
    auto sig1 = sig.xform(idmap);
    auto sig1_str = sig1.str();
    EXPECT_EQ( exp_str, sig1_str );
  }

  for ( MultiCombiGen icg{vector<pair<int, int>>(ni, make_pair(2, 1))};
	!icg.is_end(); ++ icg ) {
    vector<bool> ipol_list(ni);
    for ( SizeType i = 0; i < ni; ++ i ) {
      ipol_list[i] = (icg(i, 0) == 1);
    }
    for ( MultiCombiGen ocg{vector<pair<int, int>>(no, make_pair(2, 1))};
	  !ocg.is_end(); ++ ocg ) {
      vector<bool> opol_list(no);
      for ( SizeType i = 0; i < no; ++ i ) {
	opol_list[i] = (ocg(i, 0) == 1);
      }
      for ( MultiCombiGen bcg{vector<pair<int, int>>(nb, make_pair(2, 1))};
	    !bcg.is_end(); ++ bcg ) {
	vector<bool> bpol_list(nb);
	for ( SizeType i = 0; i < nb; ++ i ) {
	  bpol_list[i] = (bcg(i, 0) == 1);
	}
	for ( PermGen ipg(ni, ni); !ipg.is_end(); ++ ipg ) {
	  vector<ClibPinMap> ipin_map(ni);
	  for ( SizeType i = 0; i < ni; ++ i ) {
	    SizeType pos = ipg(i);
	    ipin_map[i] = ClibPinMap(pos, ipol_list[pos]);
	  }
	  for ( PermGen opg(no, no); !opg.is_end(); ++ opg ) {
	    vector<ClibPinMap> opin_map(no);
	    for ( SizeType i = 0; i < no; ++ i ) {
	      SizeType pos = opg(i);
	      opin_map[i] = ClibPinMap(pos, opol_list[pos]);
	    }
	    for ( PermGen bpg(nb, nb); !bpg.is_end(); ++ bpg ) {
	      vector<ClibPinMap> bpin_map(nb);
	      for ( SizeType i = 0; i < nb; ++ i ) {
		SizeType pos = bpg(i);
		bpin_map[i] = ClibPinMap(pos, bpol_list[pos]);
	      }
	      auto xform = ClibIOMap{ipin_map, opin_map, bpin_map};
	      auto xsig = sig.xform(xform);

	      // func_table, tristate_table を変換する．
	      vector<vector<bool>> xfunc_table_list(no3);
	      vector<vector<bool>> xtristate_table_list(no3);
	      for ( SizeType i = 0; i < no; ++ i ) {
		SizeType pos = opg(i);
		xfunc_table_list[i] = xform_table(func_table_list[pos],
						  opol_list[pos],
						  ipol_list, bpol_list,
						  ipg, bpg);
		xtristate_table_list[i] = xform_table(tristate_table_list[pos],
						      false,
						      ipol_list, bpol_list,
						      ipg, bpg);
	      }
	      for ( SizeType i = 0; i < nb; ++ i ) {
		SizeType pos = bpg(i) + no;
		xfunc_table_list[i + no] = xform_table(func_table_list[pos],
						       opol_list[pos],
						       ipol_list, bpol_list,
						       ipg, bpg);
		xtristate_table_list[i] = xform_table(tristate_table_list[pos],
						      false,
						      ipol_list, bpol_list,
						      ipg, bpg);
	      }
	      for ( SizeType i = no2; i < no3; ++ i ) {
		xfunc_table_list[i] = xform_table(func_table_list[i],
						  false,
						  ipol_list, bpol_list,
						  ipg, bpg);
		xtristate_table_list[i] = vector<bool>{};
	      }
	      // str() の期待値を作る．
	      auto exp_str = gen_str(ni, no, nb,
				     xfunc_table_list,
				     xtristate_table_list,
				     spec.mSeqAttr);
	      EXPECT_EQ( exp_str, xsig.str() );
	      if ( exp_str != xsig.str() ) {
		for ( SizeType i = 0; i < no2; ++ i ) {
		  cout << "#" << i << ": " << spec.mFuncList[i]
		       << ": " << spec.mTristateList[i] << endl;
		}
		cout << "ipol: ";
		for ( SizeType i = 0; i < ni; ++ i ) {
		  if ( ipol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "opol: ";
		for ( SizeType i = 0; i < no; ++ i ) {
		  if ( opol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "bpol: ";
		for ( SizeType i = 0; i < nb; ++ i ) {
		  if ( bpol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "imap: ";
		for ( SizeType i = 0; i < ni; ++ i ) {
		  cout << " " << ipg(i);
		}
		cout << endl;
		cout << "omap: ";
		for ( SizeType i = 0; i < no; ++ i ) {
		  cout << " " << opg(i);
		}
		cout << endl;
		cout << "bmap: ";
		for ( SizeType i = 0; i < nb; ++ i ) {
		  cout << " " << bpg(i);
		}
		cout << endl;
		cout << " ==> " << endl;
		for ( SizeType i = 0; i < no2; ++ i ) {
		  cout << "#" << i << ": " << to_hex(xfunc_table_list[i])
		       << ": " << to_hex(xtristate_table_list[i]) << endl;
		}
	      }
	      // 代表シグネチャを求める．
	      auto xiomap = xsig.rep_map();
	      auto xrep_sig = xsig.xform(xiomap);
	      auto xrep_str = xrep_sig.str();
	      EXPECT_EQ( rep_str, xrep_str );
	      if ( rep_str != xrep_str ) {
		for ( SizeType i = 0; i < no2; ++ i ) {
		  cout << "#" << i << ": " << spec.mFuncList[i]
		       << ": " << spec.mTristateList[i] << endl;
		}
		cout << "ipol: ";
		for ( SizeType i = 0; i < ni; ++ i ) {
		  if ( ipol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "opol: ";
		for ( SizeType i = 0; i < no; ++ i ) {
		  if ( opol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "bpol: ";
		for ( SizeType i = 0; i < nb; ++ i ) {
		  if ( bpol_list[i] ) {
		    cout << "N";
		  }
		  else {
		    cout << "P";
		  }
		}
		cout << endl;
		cout << "imap: ";
		for ( SizeType i = 0; i < ni; ++ i ) {
		  cout << " " << ipg(i);
		}
		cout << endl;
		cout << "omap: ";
		for ( SizeType i = 0; i < no; ++ i ) {
		  cout << " " << opg(i);
		}
		cout << endl;
		cout << "bmap: ";
		for ( SizeType i = 0; i < nb; ++ i ) {
		  cout << " " << bpg(i);
		}
		cout << endl;
		cout << " ==> " << endl;
		for ( SizeType i = 0; i < no2; ++ i ) {
		  cout << "#" << i << ": " << to_hex(xfunc_table_list[i])
		       << ": " << to_hex(xtristate_table_list[i]) << endl;
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

TEST(GenFuncTest, base1)
{
  SizeType ni = 4;
  SizeType no = 1;
  SizeType nb = 0;
  SizeType ni3 = ni + 2;
  auto clock_var = TvFunc::posi_literal(ni3, 0);
  auto data_var = TvFunc::posi_literal(ni3, 1);
  auto clear_var = TvFunc::posi_literal(ni3, 2);
  auto preset_var = TvFunc::posi_literal(ni3, 3);
  auto qout_var = TvFunc::posi_literal(ni3, 4);
  FFSpec spec{ni, no, nb,
	      {qout_var},
	      {TvFunc::invalid()},
	      clock_var,
	      TvFunc::invalid(),
	      data_var,
	      clear_var,
	      preset_var,
	      ClibSeqAttr{false, ClibCPV::L, ClibCPV::H}};
  check(spec);
}

#if 0
TEST(GenFuncTest, manual1)
{
  SizeType ni = 4;
  SizeType no = 2;
  SizeType nb = 0;
  auto v0 = TvFunc::posi_literal(ni + nb, 0);
  auto v1 = TvFunc::posi_literal(ni + nb, 1);
  auto v2 = TvFunc::posi_literal(ni + nb, 2);
  auto v3 = TvFunc::posi_literal(ni + nb, 3);
  auto f0 = v0 & v1;
  auto f1 = v2 | v3;
  auto iv = TvFunc::invalid();
  auto sig1 = CgSignature::make_logic_sig(ni, no, nb,
					  {f0, f1},
					  {iv, iv});
  auto g0 = ~v3 & ~v2;
  auto g1 = ~v0 | ~v1;
  auto sig2 = CgSignature::make_logic_sig(ni, no, nb,
					  {g0, g1},
					  {iv, iv});
  auto map1 = sig1.rep_map();
  auto sig1_rep = sig1.xform(map1);

  auto map2 = sig2.rep_map();
  auto sig2_rep = sig2.xform(map2);

  EXPECT_EQ( sig1_rep.str(), sig2_rep.str() );
}
#endif

END_NAMESPACE_YM_CLIB
