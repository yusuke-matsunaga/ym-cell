
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


// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgGenLogicSig::rep_map() const
{
  SizeType ni2 = mNi + mNb;
  SizeType no2 = mNo + mNb;

  // Walsh の0次の係数を用いて出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  vector<CgPinGroup> og_list;
  vector<CgPolInfo> opol_list(no2, CgPolInfo::Both);
  {
    vector<SizeType> src_group(mNo);
    for ( SizeType i = 0; i < mNo; ++ i ) {
      src_group[i] = i;
    }
    w0_refine(src_group, og_list, opol_list);
  }
  {
    vector<SizeType> src_group(mNb);
    for ( SizeType i = 0; i < mNb; ++ i ) {
      src_group[i] = i + mNo;
    }
    w0_refine(src_group, og_list, opol_list);
  }

  // 入力の対称グループを作る．
  vector<CgSymGroup> symgroup_list;
  vector<CgPolInfo> ipol_list(ni2, CgPolInfo::Both);
  {
    vector<SizeType> src_group(mNi);
    for ( SizeType i = 0; i < mNi; ++ i ) {
      src_group[i] = i;
    }
    gen_symgroup(src_group, symgroup_list, ipol_list);
  }
  { // 入出力は対称グループを持たない．
    for ( SizeType i = 0; i < mNb; ++ i ) {

      src_group[i] = i + mNi;
    }
    gen_symgroup(src_group, symgroup_list, ipol_list);
  }

  // Walsh の1次の係数の和を用いて極性と順序を決める．
  vector<CgPinGroup> ig_list;
  w1sum_refine(symgroup_list, opol_list, ig_list, ipol_list);

  auto npnmap = mFuncList[0].npn_cannonical_map();
  return from_npnmap(npnmap);
}

// @brief Walsh_0 を用いて出力のグループ分けを行う．
void
CgGenLogicSig::w0_refine(
  const vector<SizeType>& src_group,
  vector<CgPinGroup>& og_list,
  vector<CgPolInfo>& opol_list
) const
{
  // Walsh の 0次の係数を用いて出力の極性を正規化する．
  // 同時に出力のグループ分けと順序付けを行う．
  SizeType head = og_list.size();
  for ( auto id: src_group ) {
    int func_w0 = mFuncList[id].walsh_0();
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
    int tristate_w0 = mTristateList[id].walsh_0();

    // (func_w0, tristate_w0) のグループを探す．
    bool done = false;
    SizeType pos = head;
    for ( ; pos < og_list.size(); ++ pos ) {
      auto& og = og_list[pos];
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
      og_list.insert(og_list.begin() + pos, CgPinGroup{func_w0, tristate_w0, {id}});
    }
  }
}

// @brief 対称グループを作る．
void
CgGenLogicSig::gen_symgroup(
  const vector<SizeType>& src_group,
  vector<CgSymGroup>& symgroup_list,
  vector<CgPolInfo>& ipol_list
) const
{
  SizeType ni2 = mNi + mNb;
  SizeType no2 = mNo + mNb;

  // Walsh_1 の値のリスト
  vector<vector<int>> w1_list(ni2);
  for ( SizeType id: src_group ) {
    for ( SizeType oid = 0; oid < no2; ++ oid ) {
      w1_list[id].push_back(mFuncList[oid].walsh_1(VarId{id}));
      w1_list[id].push_back(mTristateList[oid].walsh_1(VarId{id}));
    }
  }

  vector<bool> marks(ni2, false);
  SizeType n = src_group.size();
  for ( SizeType i = 0; i < n; ++ i ) {
    SizeType id1 = src_group[i];
    if ( marks[id1] ) {
      continue;
    }
    // id1 を代表元にする．
    symgroup_list.push_back(CgSymGroup{{id1}, false});
    auto& symgroup = symgroup_list.back();
    for ( SizeType j = i + 1; j < mNi; ++ j ) {
      SizeType id2 = src_group[j];
      if ( marks[id2] ) {
	continue;
      }
      if ( w1_list[id1] != w1_list[id2] ) {
	continue;
      }
      if ( check_sym(id1, id2, false) ) {
	if ( symgroup.mIdList.size() == 1 && check_sym(id1, id2, true) ) {
	  symgroup.mBiSym = true;
	}
	symgroup.mIdList.push_back(id2);
	marks[id2] = true;
      }
      else if ( check_sym(id1, id2, true) ) {
	ipol_list[id2] = CgPolInfo::Negative;
	symgroup.mIdList.push_back(id2);
	marks[id2] = true;
      }
    }
  }
}

// @brief Walsh_1_sum を用いて入力グループの細分化を行う．
void
CgGenLogicSig::w1sum_refine(
  const vector<CgSymGroup>& symgroup_list,
  const vector<CgPolInfo>& opol_list,
  vector<CgPinGroup>& ig_list,
  vector<CgPolInfo>& ipol_list
) const
{
  SizeType no2 = mNo + mNb;
  for ( auto& symgroup: symgroup_list ) {
    SizeType i = symgroup.mIdList[0];
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
    if ( func_w1sum < 0 ) {
      for ( SizeType j: symgroup.mIdList ) {
	if ( ipol_list[j] == CgPolInfo::Negative ) {
	  ipol_list[j] = CgPolInfo::Positive;
	}
	else {
	  ipol_list[j] = CgPolInfo::Negative;
	}
      }
      func_w1sum = - func_w1sum;
    }
    else if ( func_w1sum > 0 ) {
      ipol_list[i] = CgPolInfo::Positive;
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
