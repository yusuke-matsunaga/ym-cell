
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
) : CgFLSig{ni, no, nb,
	    func_list, tristate_list,
	    clocked_on, clocked_on_also, next_state,
	    clear, preset,
	    clear_preset_var1,
	    clear_preset_var2}
{
}

// @brief シグネチャ文字列を返す．
string
CgFFSig::str() const
{
  return "F:" + base_str();
}

// @brief インスタンスを作る．
unique_ptr<const CgSigRep>
CgFFSig::make_instance(
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
) const
{
  return make_signature(ni, no, nb, func_list, tristate_list,
			clocked_on, clocked_on_also, next_state,
			clear, preset, clear_preset_var1, clear_preset_var2);
}

END_NAMESPACE_YM_CLIB
