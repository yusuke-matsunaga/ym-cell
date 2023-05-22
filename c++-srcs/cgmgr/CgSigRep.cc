
/// @file CgSigRep.cc
/// @brief CgSigRep の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "ym/Expr.h"
#include "ym/MultiCombiGen.h"
#include "ym/MultiPermGen.h"


BEGIN_NAMESPACE_YM_CLIB

// 同じ重みを持つピングループを表す構造体
struct CgPinGroup
{
  int mFuncW;
  int mTristateW;
  vector<SizeType> mIdList;
};

// 対称な入力グループの情報を表す構造体
struct CgSymInfo
{
  bool mBiSym{false};
  vector<SizeType> mIdList;
};


BEGIN_NONAMESPACE

// デバッグフラグ
bool debug = false;

// @brief 4ビットの整数値を16進数表記の文字に変換する
inline
char
to_hex(
  std::uint8_t val
)
{
  if ( val < 10 ) {
    return '0' + val;
  }
  else {
    return 'A' + (val - 10);
  }
}

// @brief 関数の内容を文字列に変換する．
string
hex_str(
  const TvFunc& func
)
{
  if ( func.is_invalid() ) {
    return string{};
  }
  SizeType ni = func.input_num();
  SizeType nexp = 1U << ni;
  std::uint8_t val = 0U;
  ostringstream buf;
  for ( SizeType i = 0; i < nexp; ++ i ) {
    val <<= 1;
    if ( func.value(i) ) {
      val |= 1U;
    }
    if ( (i % 4) == 3 ) {
      buf << to_hex(val);
      val = 0U;
    }
  }
  if ( nexp <= 3 ) {
    buf << to_hex(val);
  }
  return buf.str();
}

// ClibIOMap から NpnMap を作る．
NpnMap
to_npnmap(
  const ClibIOMap& iomap,
  SizeType ni0,
  SizeType opos
)
{
  SizeType ni = iomap.input_num();
  SizeType no = iomap.output_num();
  SizeType nb = iomap.inout_num();
  NpnMap npnmap(ni0);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto ipinmap = iomap.input_map(i);
    npnmap.set(i, ipinmap.id(), ipinmap.inv());
  }
  for ( SizeType i = 0; i < nb; ++ i ) {
    auto bpinmap = iomap.inout_map(i);
    npnmap.set(i + ni, bpinmap.id() + ni, bpinmap.inv());
  }
  for ( SizeType i = ni + nb; i < ni0; ++ i ) {
    npnmap.set(i, i, false);
  }
  if ( opos < no ) {
    npnmap.set_oinv(iomap.output_map(opos).inv());
  }
  return npnmap;
}

// NpnMap から ClibIOMap を作る．
ClibIOMap
from_npnmap(
  const NpnMap& npnmap
)
{
  SizeType ni = npnmap.input_num();
  vector<ClibPinMap> input_map(ni);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto v = npnmap.imap(i);
    input_map[i] = ClibPinMap{v.var(), v.inv()};
  }
  return ClibIOMap{input_map, npnmap.oinv()};
}

END_NONAMESPACE


// @brief コンストラクタ
CgSigRep::CgSigRep(
  const string& prefix,
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const Expr& expr
) : mPrefix{prefix},
    mNi{ni},
    mNo{no},
    mNb{nb},
    mFuncList{func_list},
    mTristateList{tristate_list},
    mExpr{expr}
{
}

// @brief シグネチャ文字列を返す．
string
CgSigRep::str() const
{
  ostringstream buf;
  buf << mPrefix << ":"
      << mNi << ":"
      << mNo << ":"
      << mNb;
  SizeType n = mFuncList.size();
  for ( SizeType i = 0; i < n; ++ i ) {
    buf << ":" << hex_str(mFuncList[i])
	<< ":"<< hex_str(mTristateList[i]);
  }
  return buf.str();
}

// @brief 単一の論理式を持つ場合，その式を返す．
Expr
CgSigRep::expr() const
{
  return mExpr;
}

BEGIN_NONAMESPACE

// 論理式の変数を map にしたがって変換する．
Expr
xform_expr(
  const Expr& expr,
  const NpnMap& map
)
{
  auto ni = map.input_num();
  unordered_map<SizeType, Expr> vlm;
  for ( auto src_var = 0; src_var < ni; ++ src_var ) {
    NpnVmap imap = map.imap(src_var);
    auto dst_var = imap.var();
    auto expr = Expr::make_literal(dst_var, imap.inv());
    vlm[src_var] = expr;
  }
  Expr cexpr = expr.compose(vlm);
  if ( map.oinv() ) {
    cexpr = ~cexpr;
  }
  return cexpr;
}

END_NONAMESPACE


// @brief 変換を施した後のシグネチャを返す．
unique_ptr<const CgSigRep>
CgSigRep::xform(
  const ClibIOMap& iomap ///< [in] 変換マップ
) const
{
  ASSERT_COND( iomap.input_num() == mNi );
  ASSERT_COND( iomap.output_num() == mNo );
  ASSERT_COND( iomap.inout_num() == mNb );

  SizeType n = mFuncList.size();
  vector<TvFunc> xfunc_list(n);
  vector<TvFunc> xtristate_list(n);
  SizeType ni = 0;
  if ( n > 0 ) {
    ni = mFuncList[0].input_num();
  }
  // tristate 用の変換マップ
  // 出力の反転属性がない．
  auto npnmap0 = to_npnmap(iomap, ni, -1);
  SizeType no2 = mNo + mNb;
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto npnmap = to_npnmap(iomap, ni, i);
    auto pos = iomap.output_map(i).id();
    xfunc_list[i] = mFuncList[pos].xform(npnmap);
    xtristate_list[i] = mTristateList[pos].xform(npnmap0);
  }
  for ( SizeType i = no2; i < n; ++ i ) {
    xfunc_list[i] = mFuncList[i].xform(npnmap0);
    xtristate_list[i] = mTristateList[i].xform(npnmap0);
  }
  auto xexpr = Expr::make_invalid();
  if ( mExpr.is_valid() ) {
    auto npnmap = to_npnmap(iomap, ni, 0);
    xexpr = xform_expr(mExpr, npnmap);
  }
  auto rep = new CgSigRep{mPrefix, mNi, mNo, mNb, xfunc_list, xtristate_list, xexpr};
  return unique_ptr<CgSigRep>{rep};
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgSigRep::rep_map() const
{
  auto map_list = gen_cannonical_map();
  return map_list.front();
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgSigRep::idmap_list() const
{
  auto map_list = gen_cannonical_map();
  vector<ClibIOMap> ans_list;
  const auto& map0 = map_list.front();
  auto invmap = map0.inverse();
  for ( const auto& map: map_list ) {
    ans_list.push_back(map * invmap);
  }
  return ans_list;
}


BEGIN_NONAMESPACE

// @brief 極性展開用のジェネレータを作る(入力用)．
MultiCombiGen
gen_pol_gen(
  const vector<SizeType>& rep_list,
  const vector<CgPolInfo>& pol_list
)
{
  SizeType n = rep_list.size();
  vector<pair<int, int>> n_array;
  n_array.reserve(n);
  for ( SizeType id: rep_list ) {
    if ( pol_list[id] == CgPolInfo::Both ) {
      n_array.push_back(make_pair(2, 1));
    }
    else {
      n_array.push_back(make_pair(1, 1));
    }
  }
  return MultiCombiGen{n_array};
}

// @brief 極性を展開する．
vector<bool>
expand_pol(
  const MultiCombiGen& mcg,
  const vector<SizeType>& rep_list,
  const vector<CgPolInfo>& src_pol_list
)
{
  SizeType n = src_pol_list.size();
  vector<bool> pol_list(n, false);
  for ( SizeType i = 0; i < rep_list.size(); ++ i ) {
    SizeType id = rep_list[i];
    if ( src_pol_list[id] == CgPolInfo::Negative ) {
      pol_list[id] = true;
    }
    else if ( src_pol_list[id] == CgPolInfo::Both && mcg(i, 0) == 1 ) {
      pol_list[id] = true;
    }
  }
  return pol_list;
}

// @brief 極性展開用のジェネレータを作る．
MultiCombiGen
gen_pol_gen(
  const vector<CgPolInfo>& pol_list
)
{
  SizeType n = pol_list.size();
  vector<pair<int, int>> n_array(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    if ( pol_list[i] == CgPolInfo::Both ) {
      n_array[i] = make_pair(2, 1);
    }
    else {
      n_array[i] = make_pair(1, 1);
    }
  }
  return MultiCombiGen{n_array};
}

// @brief 極性を展開する．
vector<bool>
expand_pol(
  const MultiCombiGen& mcg,
  const vector<CgPolInfo>& src_pol_list
)
{
  SizeType n = src_pol_list.size();
  vector<bool> pol_list(n, false);
  for ( SizeType i = 0; i < n; ++ i ) {
    if ( src_pol_list[i] == CgPolInfo::Negative ) {
      pol_list[i] = true;
    }
    else if ( src_pol_list[i] == CgPolInfo::Both && mcg(i, 0) == 1 ) {
      pol_list[i] = true;
    }
  }
  return pol_list;
}

// @brief 順番展開用のジェネレータを作る．
MultiPermGen
gen_perm_gen(
  const vector<CgPinGroup>& pg_list
)
{
  vector<pair<int, int>> nk_array;
  for ( const auto& pg: pg_list ) {
    SizeType n = pg.mIdList.size();
    nk_array.push_back(make_pair(n, n));
  }
  return MultiPermGen{nk_array};
}

// @brief ピンの順列を展開する(入力用)．
vector<ClibPinMap>
expand_pin(
  const MultiPermGen& mpg,
  const vector<CgPinGroup>& pg_list,
  const vector<bool>& pol_list,
  const vector<CgSymInfo>& syminfo_list,
  const vector<bool>& syminv_list
)
{
  vector<ClibPinMap> pin_map;
  SizeType ng = pg_list.size();
  for ( SizeType i = 0; i < ng; ++ i ) {
    const auto& pg = pg_list[i];
    SizeType n = pg.mIdList.size();
    for ( SizeType j = 0; j < n; ++ j ) {
      SizeType id0 = pg.mIdList[mpg(i, j)];
      const auto& syminfo = syminfo_list[id0];
      for ( SizeType id: syminfo.mIdList ) {
	bool inv = pol_list[id0];
	if ( inv ) {
	  // bisymmentry かどうかで反転の仕方が変わる．
	  if ( id != id0 && syminfo.mBiSym ) {
	    inv = false;
	  }
	}
	if ( syminv_list[id] ) {
	  inv = !inv;
	}
	pin_map.push_back(ClibPinMap{id, inv});
      }
    }
  }
  return pin_map;
}

// @brief ピンの順列を展開する．
vector<ClibPinMap>
expand_pin(
  const MultiPermGen& mpg,
  const vector<CgPinGroup>& pg_list,
  const vector<bool>& pol_list
)
{
  vector<ClibPinMap> pin_map;
  SizeType ng = pg_list.size();
  for ( SizeType i = 0; i < ng; ++ i ) {
    const auto& pg = pg_list[i];
    SizeType n = pg.mIdList.size();
    for ( SizeType j = 0; j < n; ++ j ) {
      SizeType id = pg.mIdList[mpg(i, j)];
      pin_map.push_back(ClibPinMap{id, pol_list[id]});
    }
  }
  return pin_map;
}

END_NONAMESPACE


// @brief 正規形への変換を求める．
vector<ClibIOMap>
CgSigRep::gen_cannonical_map() const
{
  // 本当の入力数
  SizeType ni2 = mNi;
  // 本当の出力数
  SizeType no2 = mFuncList.size();
  if ( no2 > 0 ) {
    ni2 = mFuncList[0].input_num();
  }

  if ( debug ) {
    cout << endl;
    cout << "gen_cannonical_map()" << endl;
    for ( SizeType i = 0; i < mNo; ++ i ) {
      cout << "O#" << setw(2) << i << ": " << mFuncList[i] << "|"
	   << mTristateList[i] << endl;
    }
    cout << "---------" << endl;
    for ( SizeType i = 0; i < mNb; ++ i ) {
      cout << "B#" << setw(2) << i << ": " << mFuncList[i + mNo] << "|"
	   << mTristateList[i + mNo] << endl;
    }
    cout << "=========" << endl;
    for ( SizeType i = mNo + mNb; i < no2; ++ i ) {
      cout << "X#" << setw(2) << (i - mNo + mNb) << ": "
	   << mFuncList[i] << "|" << mTristateList[i] << endl;
    }
  }

  // Walsh の0次の係数を用いて出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  vector<SizeType> opos_list(mNo);
  for ( SizeType i = 0; i < mNo; ++ i ) {
    opos_list[i] = i;
  }
  vector<CgPinGroup> og_list;
  vector<CgPolInfo> opol_list(no2, CgPolInfo::Both);
  for ( SizeType i = mNo; i < no2; ++ i ) {
    opol_list[i] = CgPolInfo::Positive;
  }
  w0_refine(opos_list, og_list, opol_list);

  // Walsh の0次の係数を用いて入出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  vector<SizeType> bpos_list(mNb);
  for ( SizeType i = 0; i < mNb; ++ i ) {
    bpos_list[i] = i + mNo;
  }
  vector<CgPinGroup> bg_list;
  vector<CgPolInfo> bpol_list(mNb, CgPolInfo::Both);
  w0_refine(bpos_list, bg_list, bpol_list);

  // 入力の対称グループを作る．
  vector<CgSymInfo> syminfo_list(mNi);
  vector<bool> syminv_list(mNi, false);
  auto symrep_list = gen_symgroup(syminfo_list, syminv_list);

  // Walsh_1 の和を用いて入力の極性と順序を決める．
  vector<CgPinGroup> ig_list;
  vector<CgPolInfo> ipol_list(mNi, CgPolInfo::Both);
  w1sum_refine(symrep_list, opol_list, ig_list, ipol_list);

  // Walsh_1 の和を用いて入出力の極性と順序を決める．
  {
    vector<CgPinGroup> new_bg_list;
    for ( const auto& group: bg_list ) {
      w1sum_refine(group.mIdList, opol_list, new_bg_list, bpol_list);
    }
    bg_list.swap(new_bg_list);
  }

  if ( debug ) {
    for ( SizeType i = 0; i < symrep_list.size(); ++ i ) {
      cout << "IG#" << i;
      SizeType id0 = symrep_list[i];
      const auto& syminfo = syminfo_list[id0];
      if ( syminfo.mBiSym ) {
	cout << "*";
      }
      cout << ":";
      for ( SizeType id: syminfo.mIdList ) {
	cout << " ";
	if ( syminv_list[id] ) {
	  cout << "-";
	}
	cout << id;
      }
      cout << endl;
    }
    cout << "Input:";
    for ( const auto& ig: ig_list ) {
      cout << " (";
      for ( SizeType id: ig.mIdList ) {
	cout << " ";
	switch ( ipol_list[id] ) {
	case CgPolInfo::Positive: cout << "P"; break;
	case CgPolInfo::Negative: cout << "N"; break;
	case CgPolInfo::Both:     cout << "-"; break;
	}
	cout << id;
      }
      cout << ")";
    }
    cout << endl;
    cout << "Output:";
    for ( const auto& og: og_list ) {
      cout << " (";
      for ( SizeType id: og.mIdList ) {
	cout << " ";
	switch ( opol_list[id] ) {
	case CgPolInfo::Positive: cout << "P"; break;
	case CgPolInfo::Negative: cout << "N"; break;
	case CgPolInfo::Both:     cout << "-"; break;
	}
	cout << id;
      }
      cout << ")";
    }
    cout << endl;
    cout << "Inout:";
    for ( const auto& bg: bg_list ) {
      cout << " (";
      for ( SizeType id: bg.mIdList ) {
	cout << " ";
	switch ( bpol_list[id] ) {
	case CgPolInfo::Positive: cout << "P"; break;
	case CgPolInfo::Negative: cout << "N"; break;
	case CgPolInfo::Both:     cout << "-"; break;
	}
	cout << id;
      }
      cout << ")";
    }
    cout << endl;
  }

  string min_sig_str{};
  vector<ClibIOMap> min_map_list;

  // 入力極性を展開する．
  for ( auto imcg = gen_pol_gen(symrep_list, ipol_list); !imcg.is_end(); ++ imcg) {
    if ( 0 ) {
      cout << "imcg:" << endl;
      for ( SizeType g = 0; g < imcg.group_num(); ++ g ) {
	for ( SizeType i = 0; i < imcg.k(g); ++ i ) {
	  cout << " " << imcg(g, i);
	}
	cout << endl;
      }
    }
    auto ipol_list1 = expand_pol(imcg, symrep_list, ipol_list);
    if ( 0 ) {
      cout << "I:";
      for ( SizeType id: symrep_list ) {
	if ( ipol_list1[id] ) {
	  cout << "N";
	}
	else {
	  cout << "-";
	}
      }
      cout << endl;
    }
    // 出力極性を展開する．
    for ( auto omcg = gen_pol_gen(opol_list); !omcg.is_end(); ++ omcg ) {
      auto opol_list1 = expand_pol(omcg, opol_list);
      if ( 0 ) {
	cout << "O:";
	for ( SizeType id = 0; id < mNo; ++ id ) {
	  if ( opol_list1[id] ) {
	    cout << "N";
	  }
	  else {
	    cout << "-";
	  }
	}
	cout << endl;
      }
      // 入出力極性を展開する．
      for ( auto bmcg = gen_pol_gen(bpol_list); !bmcg.is_end(); ++ bmcg ) {
	auto bpol_list1 = expand_pol(bmcg, bpol_list);
	if ( 0 ) {
	  cout << "B:";
	  for ( SizeType id = 0; id < mNb; ++ id ) {
	    if ( bpol_list1[id] ) {
	      cout << "N";
	    }
	    else {
	      cout << "-";
	    }
	  }
	  cout << endl;
	}
	// 入力順序を展開する．
	for ( auto impg = gen_perm_gen(ig_list); !impg.is_end(); ++ impg ) {
	  // 入力の変換マップを作る．
	  auto ipin_map = expand_pin(impg, ig_list, ipol_list1, syminfo_list, syminv_list);
	  ASSERT_COND( ipin_map.size() == mNi );

	  // 出力順序を展開する．
	  for ( auto ompg = gen_perm_gen(og_list); !ompg.is_end(); ++ ompg ) {
	    // 出力の変換マップを作る．
	    auto opin_map = expand_pin(ompg, og_list, opol_list1);
	    ASSERT_COND( opin_map.size() == mNo );

	    // 入出力順序を展開する．
	    for ( auto bmpg = gen_perm_gen(bg_list); !bmpg.is_end(); ++ bmpg ) {
	      // 入出力の変換マップを作る．
	      auto bpin_map = expand_pin(bmpg, bg_list, bpol_list1);
	      ASSERT_COND( bpin_map.size() == mNb );

	      // シグネチャを求める．
	      ClibIOMap iomap{ipin_map, opin_map, bpin_map};
	      iomap = iomap.inverse();
	      auto sig1 = xform(iomap);
	      auto sig_str = sig1->str();
	      if ( min_sig_str == string{} || min_sig_str > sig_str ) {
		min_sig_str = sig_str;
		min_map_list = vector<ClibIOMap>{iomap};
	      }
	      else if ( min_sig_str == sig_str ) {
		min_map_list.push_back(iomap);
	      }
	    }
	  }
	}
      }
    }
  }
  ASSERT_COND( min_map_list.size() > 0 );

  return min_map_list;
}

// @brief Walsh_0 を用いて出力のグループ分けを行う．
void
CgSigRep::w0_refine(
  const vector<SizeType>& pos_list,
  vector<CgPinGroup>& og_list,
  vector<CgPolInfo>& opol_list
) const
{
  // Walsh の 0次の係数を用いて出力の極性を正規化する．
  SizeType n = pos_list.size();
  for ( SizeType id = 0; id < n; ++ id ) {
    SizeType pos = pos_list[id];
    int func_w0 = mFuncList[pos].walsh_0();
    if ( func_w0 < 0 ) {
      func_w0 = - func_w0;
      opol_list[id] = CgPolInfo::Negative;
    }
    else if ( func_w0 > 0 ) {
      opol_list[id] = CgPolInfo::Positive;
    }
    else {
      opol_list[id] = CgPolInfo::Both;
    }

    // tristate 関数は反転しない．
    int tristate_w0 = mTristateList[pos].walsh_0();

    // (func_w0, tristate_w0) のグループを探す．
    bool done = false;
    SizeType ipos = 0;
    for ( ; ipos < og_list.size(); ++ ipos ) {
      auto& og = og_list[ipos];
      if ( og.mFuncW == func_w0 && og.mTristateW == tristate_w0 ) {
	og.mIdList.push_back(id);
	done = true;
	break;
      }
      if ( og.mFuncW > func_w0 ) {
	break;
      }
      else if ( og.mFuncW == func_w0 && og.mTristateW > tristate_w0 ) {
	break;
      }
    }
    if ( !done ) {
      og_list.insert(og_list.begin() + ipos, CgPinGroup{func_w0, tristate_w0, {id}});
    }
  }
}

// @brief 対称グループを作る．
vector<SizeType>
CgSigRep::gen_symgroup(
  vector<CgSymInfo>& syminfo_list,
  vector<bool>& syminv_list
) const
{
  SizeType no2 = mFuncList.size();
  // Walsh_1 の値のリストを作る．
  // Walsh_1 が異なる入力は対称ではない．
  vector<vector<int>> w1_list(mNi);
  for ( SizeType id = 0; id < mNi; ++ id ) {
    for ( SizeType oid = 0; oid < no2; ++ oid ) {
      int w1 = mFuncList[oid].walsh_1(id);
      if ( w1 < 0 ) {
	w1 = - w1;
      }
      w1_list[id].push_back(w1);
      w1_list[id].push_back(mTristateList[oid].walsh_1(id));
    }
  }

  // 代表元のリスト
  vector<SizeType> rep_list;
  // 処理済みのマーク
  vector<bool> marks(mNi, false);
  for ( SizeType id1 = 0; id1 < mNi; ++ id1 ) {
    if ( marks[id1] ) {
      continue;
    }
    // id1 を代表元にする．
    rep_list.push_back(id1);
    auto& syminfo1 = syminfo_list[id1];
    syminfo1.mIdList.push_back(id1);
    for ( SizeType id2 = id1 + 1; id2 < mNi; ++ id2 ) {
      if ( marks[id2] ) {
	continue;
      }
      if ( w1_list[id1] != w1_list[id2] ) {
	continue;
      }
      auto& syminfo2 = syminfo_list[id2];
      if ( check_sym(id1, id2, false) ) {
	if ( syminfo1.mIdList.size() == 1 && check_sym(id1, id2, true) ) {
	  syminfo1.mBiSym = true;
	}
	syminfo1.mIdList.push_back(id2);
	marks[id2] = true;
      }
      else if ( check_sym(id1, id2, true) ) {
	syminfo1.mIdList.push_back(id2);
	marks[id2] = true;
	syminv_list[id2] = true;
      }
    }
  }

  return rep_list;
}

// @brief Walsh_1_sum を用いて入力グループの細分化を行う．
void
CgSigRep::w1sum_refine(
  const vector<SizeType>& src_list,
  const vector<CgPolInfo>& opol_list,
  vector<CgPinGroup>& ig_list,
  vector<CgPolInfo>& ipol_list
) const
{
  SizeType no2 = mFuncList.size();
  for ( SizeType i: src_list ) {
    int func_w1sum = 0;
    int tristate_w1sum = 0;
    for ( SizeType j = 0; j < no2; ++ j ) {
      int w1 = mFuncList[j].walsh_1(i);
      if ( opol_list[j] == CgPolInfo::Negative ) {
	w1 = - w1;
      }
      func_w1sum += w1;
      int tristate_w1 = mTristateList[j].walsh_1(i);
      tristate_w1sum += tristate_w1;
    }
    if ( ipol_list[i] == CgPolInfo::Both ) {
      // 極性が未確定なら正規化する．
      if ( func_w1sum < 0 ) {
	func_w1sum = - func_w1sum;
	ipol_list[i] = CgPolInfo::Negative;
      }
      else if ( func_w1sum > 0 ) {
	ipol_list[i] = CgPolInfo::Positive;
      }
      else { // func_w1sum == 0
	if ( tristate_w1sum < 0 ) {
	  tristate_w1sum = - tristate_w1sum;
	  ipol_list[i] = CgPolInfo::Negative;
	}
	else {
	  ipol_list[i] = CgPolInfo::Positive;
	}
      }
    }
    // (func_w1sum, tristate_w1sum) を ig_list に挿入する．
    bool done = false;
    SizeType pos = 0;
    for ( ; pos < ig_list.size(); ++ pos ) {
      auto& ig = ig_list[pos];
      if ( ig.mFuncW == func_w1sum && ig.mTristateW == tristate_w1sum ) {
	ig.mIdList.push_back(i);
	done = true;
	break;
      }
      if ( ig.mFuncW > func_w1sum ) {
	break;
      }
      else if ( ig.mFuncW == func_w1sum && ig.mTristateW > tristate_w1sum ) {
	break;
      }
    }
    if ( !done ) {
      ig_list.insert(ig_list.begin() + pos, CgPinGroup{func_w1sum, tristate_w1sum, {i}});
    }
  }
}

// @brief 入力の対称性を調べる．
bool
CgSigRep::check_sym(
  SizeType i1,
  SizeType i2,
  bool inv
) const
{
  for ( const auto& f: mFuncList ) {
    if ( !f.check_sym(i1, i2, inv) ) {
      return false;
    }
  }
  for ( const auto& f: mTristateList ) {
    if ( !f.check_sym(i1, i2, inv) ) {
      return false;
    }
  }
  return true;
}

END_NAMESPACE_YM_CLIB
