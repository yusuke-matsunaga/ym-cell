
/// @file CgGenLogicSig_test.cc
/// @brief CgGenLogicSig_test の実装ファイル
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


BEGIN_NAMESPACE_YM_CLIB

// 関数とそのシグネチャの期待値
struct GenFuncSpec
{
  SizeType mNi;
  SizeType mNo;
  SizeType mNb;
  vector<TvFunc> mFuncList;
  vector<TvFunc> mTristateList;
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

// CgSignature::str() の期待値を作る．
string
gen_str(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<vector<bool>>& func_table_list,
  const vector<vector<bool>>& tristate_table_list
)
{
  ostringstream buf;
  buf << "C:" << ni << ":" << no << ":" << nb;
  SizeType no2 = no + nb;
  for ( SizeType i = 0; i < no2; ++ i ) {
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
  const GenFuncSpec& spec
)
{
  auto sig = CgSignature::make_logic_sig(spec.mNi, spec.mNo, spec.mNb,
					 spec.mFuncList, spec.mTristateList);

  SizeType ni = spec.mNi;
  SizeType no = spec.mNo;
  SizeType nb = spec.mNb;
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;

  SizeType ni_exp = 1 << ni2;

  // mFunc の真理値表を取り出す．
  vector<vector<bool>> func_table_list(no2);
  vector<vector<bool>> tristate_table_list(no2);
  for ( SizeType o = 0; o < no2; ++ o ) {
    func_table_list[o] = extract_table(spec.mFuncList[o]);
    // mTristate の真理値表を取り出す．
    tristate_table_list[o] = extract_table(spec.mTristateList[o]);
  }

  // str() の期待値を作る．
  auto exp_str = gen_str(ni, no, nb, func_table_list, tristate_table_list);
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
	      vector<vector<bool>> xfunc_table_list(no2);
	      vector<vector<bool>> xtristate_table_list(no2);
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
	      // str() の期待値を作る．
	      auto exp_str = gen_str(ni, no, nb, xfunc_table_list, xtristate_table_list);
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
  SizeType no = 2;
  SizeType nb = 0;
  auto v0 = TvFunc::make_posi_literal(ni + nb, VarId{0});
  auto v1 = TvFunc::make_posi_literal(ni + nb, VarId{1});
  auto v2 = TvFunc::make_posi_literal(ni + nb, VarId{2});
  auto v3 = TvFunc::make_posi_literal(ni + nb, VarId{3});
  auto f0 = v0 & v1;
  auto f1 = v2 | v3;
  GenFuncSpec spec{ni, no, nb,
		   {f0, f1},
		   {TvFunc::make_invalid(), TvFunc::make_invalid()}};
  check(spec);
}

TEST(GenFuncTest, manual1)
{
  SizeType ni = 4;
  SizeType no = 2;
  SizeType nb = 0;
  auto v0 = TvFunc::make_posi_literal(ni + nb, VarId{0});
  auto v1 = TvFunc::make_posi_literal(ni + nb, VarId{1});
  auto v2 = TvFunc::make_posi_literal(ni + nb, VarId{2});
  auto v3 = TvFunc::make_posi_literal(ni + nb, VarId{3});
  auto f0 = v0 & v1;
  auto f1 = v2 | v3;
  auto iv = TvFunc::make_invalid();
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

END_NAMESPACE_YM_CLIB
