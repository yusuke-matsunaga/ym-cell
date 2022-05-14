
/// @file CgFFSig.cc
/// @brief CgFFSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgFFSig.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief シグネチャ文字列を返す．
string
CgFFSig::str() const
{
  ostringstream buf;
  buf << "F:"
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
  buf << ":" << hex_str(mClockedOn)
      << ":" << hex_str(mClockedOnAlso)
      << ":" << hex_str(mNextState)
      << ":" << hex_str(mClear)
      << ":" << hex_str(mPreset)
      << ":" << mCpv1 << mCpv2;
  return buf.str();
}

// @brief 変換を施した後のシグネチャを返す．
unique_ptr<const CgSigRep>
CgFFSig::xform(
  const ClibIOMap& iomap ///< [in] 変換マップ
) const
{
  SizeType no2 = mNo + mNb;
  vector<TvFunc> xfunc_list(no2);
  vector<TvFunc> xtristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto npnmap = to_npnmap(iomap, i);
    auto pos = iomap.output_map(i).id();
    xfunc_list[pos] = mFuncList[i].xform(npnmap);
    xtristate_list[pos] = mTristateList[i].xform(npnmap);
  }
  auto npnmap = to_npnmap(iomap, -1);
  TvFunc xclock = mClockedOn.xform(npnmap);
  TvFunc xclock2 = mClockedOnAlso.xform(npnmap);
  TvFunc xnext = mNextState.xform(npnmap);
  TvFunc clear = mClear.xform(npnmap);
  TvFunc preset = mClear.xform(npnmap);
  return make_signature(mNi, mNo, mNb, xfunc_list, xtristate_list,
			xclock, xclock2, xnext,
			clear, preset, mCpv1, mCpv2);
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgFFSig::rep_map() const
{
  // 今は恒等変換を返す．
  return ClibIOMap::identity(mNi, mNo, mNb);
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgFFSig::idmap_list() const
{
  // 今は恒等変換を返す．
  return {ClibIOMap::identity(mNi, mNo, mNb)};
}

END_NAMESPACE_YM_CLIB
