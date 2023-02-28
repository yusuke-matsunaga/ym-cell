
/// @file CiCell.cc
/// @brief CiCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"
#include "ci/CiTiming.h"
#include "cgmgr/CgSignature.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiCell::type() const
{
  return ClibCellType::Logic;
}

// @brief 組み合わせ論理タイプの時 true を返す．
bool
CiCell::is_logic() const
{
  return true;
}

// @brief FFタイプの時 true を返す．
bool
CiCell::is_ff() const
{
  return false;
}

// @brief ラッチタイプの時 true を返す．
bool
CiCell::is_latch() const
{
  return false;
}

// @brief FSMタイプの時 true を返す．
bool
CiCell::is_fsm() const
{
  return false;
}

// @brief 内部変数1の名前を返す．
string
CiCell::qvar1() const
{
  return string{};
}

// @brief 内部変数1の名前を返す．
string
CiCell::qvar2() const
{
  return string{};
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
Expr
CiCell::clear_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
Expr
CiCell::preset_expr() const
{
  return Expr::make_invalid();
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
CiCell::clear_preset_var1() const
{
  return ClibCPV::X;
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
CiCell::clear_preset_var2() const
{
  return ClibCPV::X;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
Expr
CiCell::clock_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
Expr
CiCell::clock2_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
Expr
CiCell::next_state_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
Expr
CiCell::enable_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
Expr
CiCell::enable2_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
Expr
CiCell::data_in_expr() const
{
  return Expr::make_invalid();
}

// @brief 入力ピンを追加する．
void
CiCell::add_input(
  CiInputPin* pin,
  SizeType id
)
{
  SizeType pid = mPinList.size();
  pin->set_pin_id(pid);
  mPinList.push_back(id);

  SizeType iid = mInputList.size();
  pin->set_input_id(iid);
  mInputList.push_back(id);

  ++ mInputNum;
}

// @brief 出力ピンを追加する．
void
CiCell::add_output(
  CiOutputPin* pin,
  SizeType id
)
{
  SizeType pid = mPinList.size();
  pin->set_pin_id(pid);
  mPinList.push_back(id);

  SizeType oid = mOutputList.size();
  pin->set_output_id(oid);
  mOutputList.push_back(id);

  ++ mOutputNum;
}

// @brief 入出力ピンを追加する．
void
CiCell::add_inout(
  CiInoutPin* pin,
  SizeType id
)
{
  SizeType pid = mPinList.size();
  pin->set_pin_id(pid);
  mPinList.push_back(id);

  SizeType iid = mInputList.size();
  pin->set_input_id(iid);
  mInputList.push_back(id);

  SizeType oid = mOutputList.size();
  pin->set_output_id(oid);
  mOutputList.push_back(id);

  ++ mInoutNum;
}

// @brief 内部ピンを追加する．
void
CiCell::add_internal(
  CiInternalPin* pin,
  SizeType id
)
{
  // mPinList には含まれない．
  auto iid = mInternalList.size();
  pin->set_internal_id(iid);
  mInternalList.push_back(id);
}

// @brief バスを追加する．
void
CiCell::add_bus(
  SizeType id
)
{
  mBusList.push_back(id);
}

// @brief バンドルを追加する．
void
CiCell::add_bundle(
  SizeType id
)
{
  mBundleList.push_back(id);
}

// @brief タイミング情報用のデータ構造を初期化する．
void
CiCell::init_timing_map()
{
  SizeType map_size = input2_num() * output2_num() * 2;
  mTimingMap.clear();
  mTimingMap.resize(map_size, {});
}

// @brief タイミング情報をセットする．
void
CiCell::set_timing(
  SizeType ipin_id,
  SizeType opin_id,
  ClibTimingSense timing_sense,
  const vector<SizeType>& timing_list
)
{
  SizeType base = (opin_id * input2_num() + ipin_id) * 2;
  switch ( timing_sense ) {
  case ClibTimingSense::positive_unate: base += 0; break;
  case ClibTimingSense::negative_unate: base += 1; break;
  default: ASSERT_NOT_REACHED;
  }
  mTimingMap[base] = timing_list;
}

// @brief シグネチャを返す．
CgSignature
CiCell::make_signature(
  const CiCellLibrary* library
) const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;
  if ( no == 1 && nb == 0 ) {
    auto opin = library->_pin(output(0));
    auto expr = opin->function();
    if ( expr.is_valid() ) {
      // 1出力，双方向なし
      auto tri_expr = opin->tristate();
      if ( tri_expr.is_valid() ) {
	// tristate あり
	auto func = expr.make_tv(ni2);
	auto tristate = tri_expr.make_tv(ni2);
	return CgSignature::make_logic_sig(func, tristate);
      }
      // tristate なし
      return CgSignature::make_logic_sig(ni2, expr);
    }
  }
  vector<TvFunc> logic_list(no2);
  vector<TvFunc> tristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto opin = library->_pin(output(i));
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  return CgSignature::make_logic_sig(ni, no, nb, logic_list, tristate_list);
}

END_NAMESPACE_YM_CLIB
