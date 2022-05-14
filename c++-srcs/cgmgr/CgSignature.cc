
/// @file CgSignature.cc
/// @brief CgSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "cgmgr/CgSignature.h"
#include "ym/ClibIOMap.h"
#include "CgSigRep.h"
#include "CgLogicSig.h"
#include "CgTriLogicSig.h"
#include "CgGenLogicSig.h"
#include "CgFFSig.h"
#include "CgLatchSig.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CgSignature
//
// 基本的にはただ CgSigRep の同名の関数を呼んでいるだけなのだが，
// CgSigRep.h が必要なのでヘッダファイル中では定義できない．
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
CgSignature::CgSignature()
{
}

// @brief コンストラクタ
CgSignature::CgSignature(
  unique_ptr<const CgSigRep>&& ptr
) : mRepPtr{std::move(ptr)}
{
}

// @brief ムーブコンストラクタ
CgSignature::CgSignature(
  CgSignature&& src
) : mRepPtr{std::move(src.mRepPtr)}
{
}

// @brief ムーブ代入演算子
CgSignature&
CgSignature::operator=(
  CgSignature&& src
)
{
  if ( this != &src ) {
    mRepPtr.swap(src.mRepPtr);
  }
  return *this;
}

// @brief デストラクタ
CgSignature::~CgSignature()
{
}

// @brief 1出力論理関数用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  const TvFunc& func
)
{
  SizeType ni = func.input_num();
  SizeType no = 1;
  SizeType nb = 0;
  vector<TvFunc> func_list{func};
  vector<TvFunc> tristate_list{TvFunc::make_invalid()};
  return make_logic_sig(ni, no, nb, func_list, tristate_list);
}

// @brief 1出力tristate関数用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  const TvFunc& func,
  const TvFunc& tristate
)
{
  SizeType ni = func.input_num();
  SizeType no = 1;
  SizeType nb = 0;
  vector<TvFunc> func_list{func};
  vector<TvFunc> tristate_list{tristate};
  return make_logic_sig(ni, no, nb, func_list, tristate_list);
}

// @brief 一般的な組み合わせ回路用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list
)
{
  return CgSignature{CgGenLogicSig::make_signature(ni, no, nb, func_list, tristate_list)};
}

// @brief FF用のシグネチャを作る．
CgSignature
CgSignature::make_ff_sig(
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
)
{
  return CgSignature{CgFFSig::make_signature(ni, no, nb, func_list, tristate_list,
					     clocked_on, clocked_on_also, next_state,
					     clear, preset, clear_preset_var1, clear_preset_var2)};
}

// @brief ラッチ用のシグネチャを作る．
CgSignature
CgSignature::make_latch_sig(
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
)
{
  return CgSignature{CgLatchSig::make_signature(ni, no, nb, func_list, tristate_list,
						enable_on, enable_on_also, data_in,
						clear, preset,
						clear_preset_var1, clear_preset_var2)};
}

// @brief シグネチャ文字列を返す．
string
CgSignature::str() const
{
  if ( is_valid() ) {
    return mRepPtr->str();
  }
  else {
    return string{};
  }
}

// @brief 変換を施したシグネチャを返す．
CgSignature
CgSignature::xform(
  const ClibIOMap& iomap ///< [in] 変換マップ
) const
{
  CgSignature ans;
  if ( is_valid() ) {
    auto tmp_ptr = mRepPtr->xform(iomap);
    ans.mRepPtr.swap(tmp_ptr);
  }
  return ans;
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgSignature::rep_map() const
{
  if ( is_valid() ) {
    return mRepPtr->rep_map();
  }
  else {
    return ClibIOMap{};
  }
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgSignature::idmap_list() const
{
  if ( is_valid() ) {
    return mRepPtr->idmap_list();
  }
  else {
    return vector<ClibIOMap>{};
  }
}

END_NAMESPACE_YM_CLIB
