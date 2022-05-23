
/// @file CgGenLogicSig.cc
/// @brief CgGenLogicSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgGenLogicSig.h"
#include "CgInputInfo.h"
#include "CgOutputInfo.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief コンストラクタ
CgGenLogicSig::CgGenLogicSig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list
) : mNi{ni},
    mNo{no},
    mNb{nb},
    mFuncList{func_list},
    mTristateList{tristate_list}
{
}

// @brief シグネチャ文字列を返す．
string
CgGenLogicSig::str() const
{
  ostringstream buf;
  buf << "C:"
      << mNi << ":"
      << mNo << ":"
      << mNb << ":";
  SizeType no2 = mNo + mNb;
  for ( SizeType i = 0; i < no2; ++ i ) {
    buf << hex_str(mFuncList[i])
	<< ":"
	<< hex_str(mTristateList[i]);
  }
  return buf.str();
}

// @brief 変換を施した後のシグネチャを返す．
unique_ptr<const CgSigRep>
CgGenLogicSig::xform(
  const ClibIOMap& iomap
) const
{
  ASSERT_COND( iomap.input_num() == mNi );
  ASSERT_COND( iomap.output_num() == mNo );
  ASSERT_COND( iomap.inout_num() == mNb );

  SizeType no2 = mNo + mNb;
  vector<TvFunc> xfunc_list(no2);
  vector<TvFunc> xtristate_list(no2);
  // tristate 用の変換マップ
  // 出力の反転属性がない．
  auto npnmap0 = to_npnmap(iomap, -1);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto npnmap = to_npnmap(iomap, i);
    auto pos = iomap.output_map(i).id();
    xfunc_list[i] = mFuncList[pos].xform(npnmap);
    xtristate_list[i] = mTristateList[pos].xform(npnmap0);
  }
  return make_signature(mNi, mNo, mNb, xfunc_list, xtristate_list);
}


struct CgPinGroup
{
  int mFuncW;
  int mTristateW;
  vector<SizeType> mIdList;
};

struct CgSymInfo
{
  SizeType mRepId{static_cast<SizeType>(-1)};
  bool mInv{false};
  bool mBiSym{false};
};

BEGIN_NONAMESPACE

// @brief 極性の定まっていない番号のリストを作る．
vector<SizeType>
gen_floating_list(
  const vector<CgPolInfo>& pol_list
)
{
  vector<SizeType> floating_list;
  for ( SizeType i = 0; i < pol_list.size(); ++ i ) {
    if ( pol_list[i] == CgPolInfo::Both ) {
      floating_list.push_back(i);
    }
  }
  return floating_list;
}

// @brief 極性を展開する．
vector<CgPolInfo>
expand_pol(
  SizeType bits,
  const vector<SizeType>& floating_pos_list,
  const vector<CgPolInfo>& src_pol_list
)
{
  auto pol_list = src_pol_list;
  SizeType nf = floating_pos_list.size();
  for ( SizeType i = 0; i < nf; ++ i ) {
    if ( bits & (1 << i) ) {
      pol_list[floating_pos_list[i]] = CgPolInfo::Negative;
    }
    else {
      pol_list[floating_pos_list[i]] = CgPolInfo::Positive;
    }
  }
  return pol_list;
}

END_NONAMESPACE


// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgGenLogicSig::rep_map() const
{
  SizeType ni2 = mNi + mNb;
  SizeType no2 = mNo + mNb;

  // Walsh の0次の係数を用いて出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  vector<SizeType> opos_list(mNo);
  for ( SizeType i = 0; i < mNo; ++ i ) {
    opos_list[i] = i;
  }
  vector<CgPinGroup> og_list;
  vector<CgPolInfo> opol_list(mNo, CgPolInfo::Both);
  w0_refine(opos_list, og_list, opol_list);

  // Walsh の0次の係数を用いて入出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  vector<SizeType> bpos_list(mNo);
  for ( SizeType i = 0; i < mNb; ++ i ) {
    bpos_list[i] = i + mNo;
  }
  vector<CgPinGroup> bg_list;
  vector<CgPolInfo> bpol_list(mNb, CgPolInfo::Both);
  w0_refine(bpos_list, bg_list, bpol_list);

  // 入力の対称グループを作る．
  vector<CgSymInfo> syminfo_list(mNi);
  auto symrep_list = gen_symgroup(syminfo_list);

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

  // 極性の定まっていない入力番号のリスト
  auto floating_ipos_list = gen_floating_list(ipol_list);

  // 極性の定まっていない出力番号のリスト
  auto floating_opos_list = gen_floating_list(opol_list);

  // 極性の定まっていない入出力番号のリスト
  auto floating_bpos_list = gen_floating_list(bpol_list);

  SizeType nfi = floating_ipos_list.size();
  SizeType nfi_exp = 1U << nfi;
  SizeType nfo = floating_opos_list.size();
  SizeType nfo_exp = 1U << nfo;
  SizeType nfb = floating_bpos_list.size();
  SizeType nfb_exp = 1U << nfb;

  // 入力極性を展開する．
  for ( SizeType ibits = 0; ibits < nfi_exp; ++ ibits ) {
    auto ipol_list1 = expand_pol(ibits, floating_ipos_list, ipol_list);
    // 出力極性を展開する．
    for ( SizeType obits = 0; obits < nfo_exp; ++ obits ) {
      auto opol_list1 = expand_pol(obits, floating_opos_list, opol_list);
      // 入出力極性を展開する．
      for ( SizeType bbits = 0; bbits < nfb_exp; ++ bbits ) {
	auto bpol_list1 = expand_pol(bbits, floating_bpos_list, bpol_list);

      }
    }
  }

  auto npnmap = mFuncList[0].npn_cannonical_map();
  return from_npnmap(npnmap);
}

// @brief Walsh_0 を用いて出力のグループ分けを行う．
void
CgGenLogicSig::w0_refine(
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
      if ( og.mFuncW > func_w0 ||
	   og.mFuncW == func_w0 && og.mTristateW > tristate_w0 ) {
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
CgGenLogicSig::gen_symgroup(
  vector<CgSymInfo>& syminfo_list
) const
{
  SizeType no2 = mNo + mNb;
  // Walsh_1 の値のリストを作る．
  // Walsh_1 が異なる入力は対称ではない．
  vector<vector<int>> w1_list(mNi);
  for ( SizeType id = 0; id < mNi; ++ id ) {
    for ( SizeType oid = 0; oid < no2; ++ oid ) {
      w1_list[id].push_back(mFuncList[oid].walsh_1(VarId{id}));
      w1_list[id].push_back(mTristateList[oid].walsh_1(VarId{id}));
    }
  }

  // 代表元のリスト
  vector<SizeType> rep_list;
  // 各対称グループの要素数
  // 対称グループの見つかった時に bissymmetry テストを行うために用いる．
  vector<SizeType> n_list(mNi, 0);
  for ( SizeType id1 = 0; id1 < mNi; ++ id1 ) {
    auto& syminfo1 = syminfo_list[id1];
    if ( syminfo1.mRepId != -1 ) {
      continue;
    }
    // id1 を代表元にする．
    rep_list.push_back(id1);
    n_list[id1] = 1;
    for ( SizeType id2 = id1 + 1; id2 < mNi; ++ id2 ) {
      auto& syminfo2 = syminfo_list[id2];
      if ( syminfo2.mRepId != -1 ) {
	continue;
      }
      if ( w1_list[id1] != w1_list[id2] ) {
	continue;
      }
      if ( check_sym(id1, id2, false) ) {
	if ( n_list[id1] == 1 && check_sym(id1, id2, true) ) {
	  syminfo1.mBiSym = true;
	}
	syminfo2.mRepId = id1;
	++ n_list[id1];
      }
      else if ( check_sym(id1, id2, true) ) {
	syminfo2.mRepId = id1;
	syminfo2.mInv = true;
	++ n_list[id1];
      }
    }
  }

  return rep_list;
}

// @brief Walsh_1_sum を用いて入力グループの細分化を行う．
void
CgGenLogicSig::w1sum_refine(
  const vector<SizeType>& src_list,
  const vector<CgPolInfo>& opol_list,
  vector<CgPinGroup>& ig_list,
  vector<CgPolInfo>& ipol_list
) const
{
  SizeType no2 = mNo + mNb;
  for ( SizeType i: src_list ) {
    int func_w1sum = 0;
    int tristate_w1sum = 0;
    for ( SizeType j = 0; j < no2; ++ j ) {
      int w1 = mFuncList[j].walsh_1(VarId{i});
      if ( opol_list[j] == CgPolInfo::Negative ) {
	w1 = - w1;
      }
      func_w1sum += w1;
      int tristate_w1 = mTristateList[j].walsh_1(VarId{i});
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
      if ( ig.mFuncW > func_w1sum ||
	   ig.mFuncW == func_w1sum && ig.mTristateW > tristate_w1sum ) {
	break;
      }
    }
    if ( !done ) {
      ig_list.insert(ig_list.begin() + pos, CgPinGroup{func_w1sum, tristate_w1sum, {i}});
    }
  }
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgGenLogicSig::idmap_list() const
{
  auto npnmap0 = mFuncList[0].npn_cannonical_map();
  auto invmap = inverse(npnmap0);
  auto npn_idmap_list = mFuncList[0].npn_cannonical_all_map();
  vector<ClibIOMap> ans;
  ans.reserve(npn_idmap_list.size());
  for ( auto npnmap: npn_idmap_list ) {
    auto npnmap1 = invmap * npnmap;
    ans.push_back(from_npnmap(npnmap1));
  }
  return ans;
}

// @brief 入力の対称性を調べる．
bool
CgGenLogicSig::check_sym(
  SizeType i1,
  SizeType i2,
  bool inv
) const
{
  VarId v1{i1};
  VarId v2{i2};
  SizeType no2 = mNo + mNb;
  for ( SizeType o = 0; o < no2; ++ o ) {
    if ( !mFuncList[o].check_sym(v1, v2, inv) ) {
      return false;
    }
    if ( !mTristateList[o].check_sym(v1, v2, inv) ) {
      return false;
    }
  }
  return true;
}

END_NAMESPACE_YM_CLIB
