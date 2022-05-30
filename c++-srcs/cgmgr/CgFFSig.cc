
/// @file CgFFSig.cc
/// @brief CgFFSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgFFSig.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief コンストラクタ
CgFFSig::CgFFSig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const TvFunc& clocked_on,
  const TvFunc& clocked_on_also,
  const TvFunc& next_state,
  const TvFunc& clear,
  const TvFunc& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
) : mNi{ni},
    mNo{no},
    mNb{nb},
    mFuncList{func_list},
    mTristateList{tristate_list},
    mClockedOn{clocked_on},
    mClockedOnAlso{clocked_on_also},
    mNextState{next_state},
    mClear{clear},
    mPreset{preset},
    mCpv1{clear_preset_var1},
    mCpv2{clear_preset_var2}
{
}

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
    buf << hex_str(mFuncList[i])
	<< ":"
	<< hex_str(mTristateList[i]);
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
  const ClibIOMap& iomap
) const
{
  ASSERT_COND( iomap.input_num() == mNi );
  ASSERT_COND( iomap.output_num() == mNo );
  ASSERT_COND( iomap.inout_num() == mNb );

  SizeType no2 = mNo + mNb;
  vector<TvFunc> func_list(no2);
  vector<TvFunc> tristate_list(no2);
  // tristate 用の変換マップ
  // 出力の反転属性がない．
  auto npnmap0 = to_npnmap(iomap, -1);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto npnmap = to_npnmap(iomap, i);
    auto pos = iomap.output_map(i).id();
    func_list[i] = mFuncList[pos].xform(npnmap);
    tristate_list[i] = mTristateList[i].xform(npnmap0);
  }
  TvFunc clock = mClockedOn.xform(npnmap0);
  TvFunc clock2 = mClockedOnAlso.xform(npnmap0);
  TvFunc next = mNextState.xform(npnmap0);
  TvFunc clear = mClear.xform(npnmap0);
  TvFunc preset = mPreset.xform(npnmap0);
  return make_signature(mNi, mNo, mNb, func_list, tristate_list,
			clock, clock2, next,
			clear, preset, mCpv1, mCpv2);
}

// @brief 正規形への変換を求める．
vector<ClibIOMap>
CgFFSig::gen_cannonical_map() const
{
  // 今は恒等変換を返す．
  return {ClibIOMap::identity(mNi, mNo, mNb)};
}

END_NAMESPACE_YM_CLIB
