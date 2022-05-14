
/// @file CgTriLogicSig.cc
/// @brief CgTriLogicSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgTriLogicSig.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief コンストラクタ
CgTriLogicSig::CgTriLogicSig(
  const TvFunc& func,
  const TvFunc& tristate
) : mFunc{func},
    mTristate{tristate}
{
}

// @brief シグネチャ文字列を返す．
string
CgTriLogicSig::str() const
{
  SizeType ni = mFunc.input_num();
  ostringstream buf;
  buf << "C:" << ni << ":1:0:"
      << hex_str(mFunc)
      << ":"
      << hex_str(mTristate);
  return buf.str();
}

// @brief 変換を施した後のシグネチャを返す．
unique_ptr<const CgSigRep>
CgTriLogicSig::xform(
  const ClibIOMap& iomap
) const
{
  auto npnmap = to_npnmap(iomap, 0);
  auto xfunc = mFunc.xform(npnmap);
  auto xtristate = mTristate.xform(npnmap);
  return make_signature(xfunc, xtristate);
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgTriLogicSig::rep_map() const
{
  auto npnmap = mFunc.npn_cannonical_map();
  return from_npnmap(npnmap);
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgTriLogicSig::idmap_list() const
{
  auto npnmap0 = mFunc.npn_cannonical_map();
  auto invmap = inverse(npnmap0);
  auto npn_idmap_list = mFunc.npn_cannonical_all_map();
  vector<ClibIOMap> ans;
  ans.reserve(npn_idmap_list.size());
  for ( auto npnmap: npn_idmap_list ) {
    auto npnmap1 = invmap * npnmap;
    ans.push_back(from_npnmap(npnmap1));
  }
  return ans;
}

END_NAMESPACE_YM_CLIB
