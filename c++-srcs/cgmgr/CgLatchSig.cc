
/// @file CgLatchSig.cc
/// @brief CgLatchSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgLatchSig.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief コンストラクタ
CgLatchSig::CgLatchSig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const TvFunc& enable_on,
  const TvFunc& enable_on_also,
  const TvFunc& data_in,
  const TvFunc& clear,
  const TvFunc& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
) : CgFLSig{ni, no, nb, func_list, tristate_list,
	    enable_on, enable_on_also, data_in,
	    clear, preset, clear_preset_var1, clear_preset_var2}
{
}

// @brief シグネチャ文字列を返す．
string
CgLatchSig::str() const
{
  return "L:" + base_str();
}

// @brief インスタンスを作る．
unique_ptr<const CgSigRep>
CgLatchSig::make_instance(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const TvFunc& enable_on,
  const TvFunc& enable_on_also,
  const TvFunc& next_state,
  const TvFunc& clear,
  const TvFunc& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
) const
{
  return make_signature(ni, no, nb, func_list, tristate_list,
			enable_on, enable_on_also, next_state,
			clear, preset, clear_preset_var1, clear_preset_var2);
}

END_NAMESPACE_YM_CLIB
