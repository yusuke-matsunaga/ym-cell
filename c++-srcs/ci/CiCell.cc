
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
#include "ci/Serializer.h"
#include "ci/Deserializer.h"
#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 論理セルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_Logic(
  CiCellLibrary* lib,
  const ShString& name,
  ClibArea area
)
{
  auto ptr = new CiCell{lib, name, area};
  return unique_ptr<CiCell>{ptr};
}

// @brief master/slave型のFFセルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_FF(
  CiCellLibrary* lib,
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& clocked_on,
  const Expr& clocked_on_also,
  const Expr& next_state,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* ptr = nullptr;
  if ( clocked_on_also.is_valid() ) {
    ptr = new CiFF2Cell{
      lib, name, area,
      var1, var2,
      clocked_on, clocked_on_also,
      next_state,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  else {
    ptr = new CiFFCell{
      lib, name, area,
      var1, var2,
      clocked_on,
      next_state,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  return unique_ptr<CiCell>{ptr};
}

// @brief single-stage 型のラッチセルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_Latch(
  CiCellLibrary* lib,
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& enable,
  const Expr& enable_also,
  const Expr& data_in,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* ptr = nullptr;
  if ( enable_also.is_valid() ) {
    ptr = new CiLatch2Cell{
      lib, name, area,
      var1, var2,
      enable, enable_also,
      data_in,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  else {
    ptr = new CiLatchCell{
      lib, name, area,
      var1, var2,
      enable,
      data_in,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  return unique_ptr<CiCell>{ptr};
}

// @brief FSM型の順序セルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_FSM(
  CiCellLibrary* lib,
  const ShString& name,
  ClibArea area
)
{
  auto ptr = new CiFsmCell{lib, name, area};
  return unique_ptr<CiCell>{ptr};
}

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

// @brief 名前からピンの取得
const CiPin*
CiCell::find_pin(
  const ShString& name
) const
{
  return parent()->find_pin(this, name);
}

// @brief 名前からバスの取得
const CiBus*
CiCell::find_bus(
  const ShString& name
) const
{
  return parent()->find_bus(this, name);
}

// @brief 名前からバスの取得
const CiBundle*
CiCell::find_bundle(
  const ShString& name
) const
{
  return parent()->find_bundle(this, name);
}

// @brief 入力ピンを追加する．
CiPin*
CiCell::add_input(
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance
)
{
  SizeType pid = mPinList.size();
  SizeType iid = mInputList.size();
  auto ptr = CiPin::new_Input(pid, iid, name,
			      capacitance,
			      rise_capacitance,
			      fall_capacitance);
  auto pin = ptr.get();
  mPinList.push_back(std::move(ptr));
  mInputList.push_back(pin);
  _parent()->reg_pin(this, pin);
  ++ mInputNum;
  return pin;
}

// @brief 出力ピンを追加する．
CiPin*
CiCell::add_output(
  const ShString& name,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition,
  const Expr& function,
  const Expr& tristate
)
{
  SizeType pid = mPinList.size();
  SizeType oid = mOutputList.size();
  auto ptr = CiPin::new_Output(pid, oid, name,
			       max_fanout, min_fanout,
			       max_capacitance, min_capacitance,
			       max_transition, min_transition,
			       function, tristate);
  auto pin = ptr.get();
  mPinList.push_back(std::move(ptr));
  mOutputList.push_back(pin);
  _parent()->reg_pin(this, pin);
  ++ mOutputNum;
  return pin;
}

// @brief 入出力ピンを追加する．
CiPin*
CiCell::add_inout(
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition,
  const Expr& function,
  const Expr& tristate
)
{
  SizeType pid = mPinList.size();
  SizeType iid = mInputList.size();
  SizeType oid = mOutputList.size();
  auto ptr = CiPin::new_Inout(pid, iid, oid, name,
			      capacitance,
			      rise_capacitance,
			      fall_capacitance,
			      max_fanout, min_fanout,
			      max_capacitance, min_capacitance,
			      max_transition, min_transition,
			      function, tristate);
  auto pin = ptr.get();
  mPinList.push_back(std::move(ptr));
  mInputList.push_back(pin);
  mOutputList.push_back(pin);
  _parent()->reg_pin(this, pin);
  ++ mInoutNum;
  return pin;
}

// @brief 内部ピンを追加する．
CiPin*
CiCell::add_internal(
  const ShString& name
)
{
  // mPinList には含まれない．
  auto iid = mInternalList.size();
  auto ptr = CiPin::new_Internal(iid, name);
  auto pin = ptr.get();
  mInternalList.push_back(std::move(ptr));
  return pin;
}

// @brief バスを追加する．
CiBus*
CiCell::add_bus(
  const ShString& name,
  const CiBusType* bus_type,
  const vector<const CiPin*>& pin_list
)
{
  auto bus = new CiBus{name, bus_type, pin_list};
  mBusList.push_back(unique_ptr<CiBus>{bus});
  _parent()->reg_bus(this, bus);
  return bus;
}

// @brief バンドルを追加する．
CiBundle*
CiCell::add_bundle(
  const ShString& name,
  const vector<const CiPin*>& pin_list
)
{
  auto bundle = new CiBundle{name, pin_list};
  mBundleList.push_back(unique_ptr<CiBundle>{bundle});
  _parent()->reg_bundle(this, bundle);
  return bundle;
}

// @brief タイミング情報を作る(ジェネリック遅延モデル)．
CiTiming*
CiCell::add_timing_generic(
  ClibTimingType type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_resistance,
  ClibResistance fall_resistance
)
{
  auto ptr = CiTiming::new_Generic(type, cond,
				   intrinsic_rise,
				   intrinsic_fall,
				   slope_rise,
				   slope_fall,
				   rise_resistance,
				   fall_resistance);
  auto timing = ptr.get();
  mTimingList.push_back(std::move(ptr));
  return timing;
}

// @brief タイミング情報を作る(折れ線近似)．
CiTiming*
CiCell::add_timing_piecewise(
  ClibTimingType timing_type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_pin_resistance,
  ClibResistance fall_pin_resistance
)
{
  auto ptr = CiTiming::new_Piecewise(timing_type, cond,
				     intrinsic_rise,
				     intrinsic_fall,
				     slope_rise,
				     slope_fall,
				     rise_pin_resistance,
				     fall_pin_resistance);
  auto timing = ptr.get();
  mTimingList.push_back(std::move(ptr));
  return timing;
}

// @brief タイミング情報を作る(非線形タイプ1)．
CiTiming*
CiCell::add_timing_lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  unique_ptr<CiLut>&& cell_rise,
  unique_ptr<CiLut>&& cell_fall,
  unique_ptr<CiLut>&& rise_transition,
  unique_ptr<CiLut>&& fall_transition
)
{
  auto ptr = CiTiming::new_Lut1(timing_type, cond,
				std::move(cell_rise),
				std::move(cell_fall),
				std::move(rise_transition),
				std::move(fall_transition));
  auto timing = ptr.get();
  mTimingList.push_back(std::move(ptr));
  return timing;
}

// @brief タイミング情報を作る(非線形タイプ2)．
CiTiming*
CiCell::add_timing_lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  unique_ptr<CiLut>&& rise_transition,
  unique_ptr<CiLut>&& fall_transition,
  unique_ptr<CiLut>&& rise_propagation,
  unique_ptr<CiLut>&& fall_propagation
)
{
  auto ptr = CiTiming::new_Lut2(timing_type, cond,
				std::move(rise_transition),
				std::move(fall_transition),
				std::move(rise_propagation),
				std::move(fall_propagation));
  auto timing = ptr.get();
  mTimingList.push_back(std::move(ptr));
  return timing;
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
  const vector<const CiTiming*>& timing_list
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
    auto opin = output(0);
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
    auto opin = output(i);
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  return CgSignature::make_logic_sig(ni, no, nb, logic_list, tristate_list);
}

// @brief 内容をシリアライズする．
void
CiCell::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
  for ( auto& pin: mPinList ) {
    pin->serialize(s);
  }
  for ( auto& pin: mInternalList ) {
    pin->serialize(s);
  }
  for ( auto& bus: mBusList ) {
    bus->serialize(s);
  }
  for ( auto& bundle: mBundleList ) {
    bundle->serialize(s);
  }
  for ( auto& timing: mTimingList ) {
    timing->serialize(s);
  }
}

// @brief 共通部分のダンプ
void
CiCell::dump_common(
  Serializer& s
) const
{
  s.dump(mName);
  s.out() << mArea;
  s.dump(mInputNum);
  s.dump(mOutputNum);
  s.dump(mInoutNum);
  s.dump(mPinList);
  s.dump(mInputList);
  s.dump(mOutputList);
  s.dump(mInternalList);
  s.dump(mBusList);
  s.dump(mBundleList);
  s.dump(mTimingList);
  s.dump(mTimingMap.size());
  for ( auto& timing_list: mTimingMap ) {
    s.dump(timing_list);
  }
}

// @brief 内容をバイナリダンプする．
void
CiCell::dump(
  Serializer& s
) const
{
  // シグネチャ
  s.out().write_8(0);
  dump_common(s);
}

// @brief 内容を読み込む．
unique_ptr<CiCell>
CiCell::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto type = s.in().read_8();
  unique_ptr<CiCell> cell;
  switch ( type ) {
  case 0: cell = unique_ptr<CiCell>{new CiCell{lib}}; break;
  case 1: cell = unique_ptr<CiCell>{new CiFFCell{lib}}; break;
  case 2: cell = unique_ptr<CiCell>{new CiFF2Cell{lib}}; break;
  case 3: cell = unique_ptr<CiCell>{new CiLatchCell{lib}}; break;
  case 4: cell = unique_ptr<CiCell>{new CiLatch2Cell{lib}}; break;
  case 5: cell = unique_ptr<CiCell>{new CiFsmCell{lib}}; break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }
  cell->_restore(s);
  return cell;
}

// logic タイプのセルの復元
void
CiCell::_restore(
  Deserializer& s
)
{
  s.in() >> mName
	 >> mArea;
  s.restore(mInputNum);
  s.restore(mOutputNum);
  s.restore(mInoutNum);

  // ピンリスト
  s.restore(mPinList);

  // 入力ピンリスト
  s.restore(mInputList);

  // 出力ピンリスト
  s.restore(mOutputList);

  // 内部ピンリスト
  s.restore(mInternalList);

  // バスのリスト
  s.restore(mBusList);

  // バンドルのリスト
  s.restore(mBundleList);

  // タイミングのリスト
  s.restore(mTimingList);

  // タイミングマップ
#if 0
  SizeType n = s.in().read_64();
  mTimingMap.resize(n);
  for ( SizeType i: Range(n) ) {
    s.restore(mTimingMap[i]);
  }
#else
  s.restore(mTimingMap);
#endif
}

END_NAMESPACE_YM_CLIB
