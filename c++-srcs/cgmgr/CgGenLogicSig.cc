
/// @file CgGenLogicSig.cc
/// @brief CgGenLogicSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgGenLogicSig.h"


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
    buf << hex_str(mFuncList[i]);
  }
  buf << ":";
  for ( SizeType i = 0; i < no2; ++ i ) {
    buf << hex_str(mTristateList[i]);
  }
  return buf.str();
}

// @brief 変換を施した後のシグネチャを返す．
unique_ptr<const CgSigRep>
CgGenLogicSig::xform(
  const ClibIOMap& iomap
) const
{
  auto npnmap = to_npnmap(iomap);
  SizeType no2 = mNo + mNb;
  vector<TvFunc> xfunc_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    xfunc_list[i] = mFuncList[i].xform(npnmap);
  }
  vector<TvFunc> xtristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    xtristate_list[i] = mTristateList[i].xform(npnmap);
  }
  return make_signature(mNi, mNo, mNb, xfunc_list, xtristate_list);
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgGenLogicSig::rep_map() const
{
  auto npnmap = mFuncList[0].npn_cannonical_map();
  return from_npnmap(npnmap);
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

END_NAMESPACE_YM_CLIB
