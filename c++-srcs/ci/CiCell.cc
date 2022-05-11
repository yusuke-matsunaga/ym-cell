﻿
/// @file CiCell.cc
/// @brief CiCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"
#include "ci/CiTiming.h"
#include "cgmgr/CgSignature.h"
#include "ym/ClibCellGroup.h"
#include "ym/ClibFFInfo.h"
#include "ym/ClibLatchInfo.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCell::CiCell(
  CiCellLibrary* library,
  const ShString& name,
  ClibArea area
) : mLibrary{library},
    mName{name},
    mArea{area}
{
}

// @brief デストラクタ
CiCell::~CiCell()
{
  // unique_ptr のためにインラインにすると余計なインクルードが発生する．
}

// @brief ID番号の取得
SizeType
CiCell::id() const
{
  return mId;
}

// @brief 名前の取得
string
CiCell::name() const
{
  return mName;
}

// @brief 面積の取得
ClibArea
CiCell::area() const
{
  return mArea;
}

// @brief ピン数の取得
SizeType
CiCell::pin_num() const
{
  return mPinList.size();
}

// @brief ピンの取得
// @param[in] pin_id ピン番号 ( 0 <= pin_id < pin_num() )
// @return ピン情報を返す．
const ClibPin&
CiCell::pin(
  SizeType pin_id
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < pin_num() );
  return *mPinList[pin_id];
}

// @brief 名前からピン番号の取得
SizeType
CiCell::pin_id(
  const string& name
) const
{
  return pin_id(ShString(name));
}

// @brief 名前からピン番号の取得
SizeType
CiCell::pin_id(
  const ShString& name
) const
{
  return mLibrary->get_pin_id(this, name);
}

// @brief 入力ピン数の取得
SizeType
CiCell::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数の取得
SizeType
CiCell::output_num() const
{
  return mOutputNum;
}

// @brief 入出力ピン数の取得
SizeType
CiCell::inout_num() const
{
  return mInoutNum;
}

// @brief 内部ピン数の取得
SizeType
CiCell::internal_num() const
{
  return 0;
}

// @brief 入力ピン+入出力ピン数の取得
SizeType
CiCell::input_num2() const
{
  return mInputList.size();
}

// @brief 入力ピンの取得
const ClibPin&
CiCell::input(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < input_num2() );
  return *mInputList[pos];
}

// @brief 出力ピン+入出力ピン数の取得
SizeType
CiCell::output_num2() const
{
  return mOutputList.size();
}

// @brief 出力ピンの取得
const ClibPin&
CiCell::output(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < output_num2() );
  return *mOutputList[pos];
}

// @brief 入出力ピンの取得
const ClibPin&
CiCell::inout(
  SizeType id
) const
{
  ASSERT_COND( 0 <= id && id < inout_num() );
  return *mInputList[id + input_num()];
}

// @brief 内部ピンの取得
const ClibPin&
CiCell::internal(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < mInternalList.size() );
  return *mInternalList[pos];
}

// @brief バス数の取得
SizeType
CiCell::bus_num() const
{
  return mBusList.size();
}

// @brief バスの取得
const ClibBus&
CiCell::bus(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < bus_num() );
  return *mBusList[pos];
}

// @brief 名前からバス番号の取得
SizeType
CiCell::bus_id(
  const string& name
) const
{
  return mLibrary->get_bus_id(this, ShString{name});
}

// @brief バンドル数の取得
SizeType
CiCell::bundle_num() const
{
  return mBundleList.size();
}

// @brief バンドルの取得
const ClibBundle&
CiCell::bundle(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < bundle_num() );
  return *mBundleList[pos];
}

// @brief 名前からバンドル番号の取得
SizeType
CiCell::bundle_id(
  const string& name
) const
{
  return mLibrary->get_bundle_id(this, ShString{name});
}

// @brief タイミング情報の数を返す．
SizeType
CiCell::timing_num() const
{
  return mTimingList.size();
}

// @brief タイミング情報を返す．
const ClibTiming&
CiCell::timing(
  SizeType pos ///< [in] インデックス ( 0 <= pos < timing_num() )
) const
{
  ASSERT_COND( 0 <= pos && pos < timing_num() );
  return *mTimingList[pos];
}

// @brief 条件に合致するタイミング情報のインデックスのリストを返す．
const vector<SizeType>&
CiCell::timing_id_list(
  SizeType ipos,        ///< [in] 開始ピン番号 ( 0 <= ipos < input_num2() )
  SizeType opos,        ///< [in] 終了ピン番号 ( 0 <= opos < output_num2() )
  ClibTimingSense sense ///< [in] タイミング情報の摘要条件
) const
{
  SizeType base = (opos * input_num2() + ipos) * 2;
  switch ( sense ) {
  case ClibTimingSense::positive_unate: base += 0; break;
  case ClibTimingSense::negative_unate: base += 1; break;
  default:
    ASSERT_NOT_REACHED;
  }
  return mTimingMap[base];
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

// @brief 出力の論理式を持っている時に true を返す．
bool
CiCell::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return output(pin_id).function().is_valid();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCell::has_logic() const
{
  for ( SizeType id = 0; id < output_num2(); ++ id ) {
    if ( !has_logic(id) ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiCell::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return output(pin_id).function();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiCell::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return !output(pin_id).tristate().is_zero();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
CiCell::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return output(pin_id).tristate();
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

// @brief 非同期 clear を持つ時 true を返す．
//
// FF/ラッチセル以外の場合には返り値は不定
bool
CiCell::has_clear() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
//
// クリア端子がない場合の返り値は不定
Expr
CiCell::clear_expr() const
{
  return Expr::make_zero();
}

// @brief 非同期 preset を持つ時 true を返す．
//
// FF/ラッチセル以外の場合には返り値は不定
bool
CiCell::has_preset() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
//
// プリセット端子がない場合の返り値は不定
Expr
CiCell::preset_expr() const
{
  return Expr::make_zero();
}

// @brief clear と preset が同時にアクティブになった時の値1
//
// has_clear() == true && has_preset() == true の時のみ意味を持つ．
// FF/ラッチセル以外の場合には返り値は不定
ClibCPV
CiCell::clear_preset_var1() const
{
  return ClibCPV::X;
}

// @brief clear と preset が同時にアクティブになった時の値1
//
// has_clear() == true && has_preset() == true の時のみ意味を持つ．
// FF/ラッチセル以外の場合には返り値は不定
ClibCPV
CiCell::clear_preset_var2() const
{
  return ClibCPV::X;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::clock_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::clock2_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::next_state_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::enable_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::enable2_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCell::data_in_expr() const
{
  return Expr::make_invalid();
}

// @brief 入力ピンを追加する．
CiInputPin*
CiCell::add_input(
  const ShString& name,             ///< [in] ピン名
  ClibCapacitance capacitance,      ///< [in] 負荷容量
  ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
  ClibCapacitance fall_capacitance  ///< [in] 立ち下がり時の負荷容量
)
{
  auto iid = mInputList.size();
  auto pin = new CiInputPin{iid, name, capacitance,
                            rise_capacitance, fall_capacitance};
  mInputList.push_back(pin);
  ++ mInputNum;
  reg_pin(pin);
  return pin;
}

// @brief 出力ピンを追加する．
CiOutputPin*
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
  auto oid = mOutputList.size();
  auto pin = new CiOutputPin{oid, name,
                             max_fanout, min_fanout,
			     max_capacitance, min_capacitance,
			     max_transition, min_transition,
			     function, tristate};
  mOutputList.push_back(pin);
  ++ mOutputNum;
  reg_pin(pin);
  return pin;
}

// @brief 入出力ピンを追加する．
CiInoutPin*
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
  auto iid = mInputList.size();
  auto oid = mOutputList.size();
  auto pin = new CiInoutPin{iid, oid, name,
                            capacitance, rise_capacitance, fall_capacitance,
			    max_fanout, min_fanout,
			    max_capacitance, min_capacitance,
			    max_transition, min_transition,
			    function, tristate};
  mInputList.push_back(pin);
  mOutputList.push_back(pin);
  ++ mInoutNum;
  reg_pin(pin);
  return pin;
}

// @brief 内部ピンを追加する．
CiInternalPin*
CiCell::add_internal(
  const ShString& name
)
{
  auto iid = mInternalList.size();
  auto pin = new CiInternalPin{iid, name};
  mInternalList.push_back(pin);
  reg_pin(pin);
  return pin;
}

// @brief バスを追加する．
CiBus*
CiCell::add_bus(
  const ShString& name,            ///< [in] 名前
  const ClibBusType* bus_type,     ///< [in] バスタイプ
  vector<const ClibPin*>& pin_list ///< [in] ピンリスト
)
{
  auto id = mBusList.size();
  auto bus = new CiBus{name, bus_type, pin_list};
  mBusList.push_back(unique_ptr<CiBus>(bus));
  mLibrary->reg_bus(this, bus->_name(), id);
  return bus;
}

// @brief バンドルを追加する．
CiBundle*
CiCell::add_bundle(
  const ShString& name,            ///< [in] 名前
  vector<const ClibPin*>& pin_list ///< [in] ピンリスト
)
{
  auto id = mBundleList.size();
  auto bundle = new CiBundle(name, pin_list);
  mBundleList.push_back(unique_ptr<CiBundle>(bundle));
  mLibrary->reg_bundle(this, bundle->_name(), id);
  return bundle;
}

// @brief タイミング情報を作る(ジェネリック遅延モデル)．
SizeType
CiCell::add_timing_generic(
  ClibTimingType type,            ///< [in] タイミングの種類
  const Expr& cond,               ///< [in] 条件式
  ClibTime intrinsic_rise,        ///< [in] 立ち上がり固有遅延
  ClibTime intrinsic_fall,        ///< [in] 立ち下がり固有遅延
  ClibTime slope_rise,            ///< [in] 立ち上がり負荷依存遅延
  ClibTime slope_fall,            ///< [in] 立ち下がり負荷依存遅延
  ClibResistance rise_resistance, ///< [in] 立ち上がり抵抗
  ClibResistance fall_resistance  ///< [in] 立ち下がり抵抗
)
{
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingGeneric(tid, type, cond,
				    intrinsic_rise,
				    intrinsic_fall,
				    slope_rise,
				    slope_fall,
				    rise_resistance,
				    fall_resistance);
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(折れ線近似)．
SizeType
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
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingPiecewise(tid, timing_type, cond,
				      intrinsic_rise,
				      intrinsic_fall,
				      slope_rise,
				      slope_fall,
				      rise_pin_resistance,
				      fall_pin_resistance);
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(非線形タイプ1)．
SizeType
CiCell::add_timing_lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  CiLut* cell_rise,
  CiLut* cell_fall,
  CiLut* rise_transition,
  CiLut* fall_transition
)
{
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingLut1(tid, timing_type, cond,
				 cell_rise,
				 cell_fall,
				 rise_transition,
				 fall_transition);

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(非線形タイプ2)．
SizeType
CiCell::add_timing_lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  CiLut* rise_transition,
  CiLut* fall_transition,
  CiLut* rise_propagation,
  CiLut* fall_propagation
)
{
  SizeType tid = mTimingList.size();
  CiTiming* timing = new CiTimingLut2(tid, timing_type, cond,
				      rise_transition,
				      fall_transition,
				      rise_propagation,
				      fall_propagation);

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報用のデータ構造を初期化する．
void
CiCell::init_timing_map(
  SizeType input_num,
  SizeType output_num
)
{
  SizeType map_size = input_num * output_num * 2;
  mTimingMap.clear();
  mTimingMap.resize(map_size, vector<SizeType>{});
}

// @brief タイミング情報をセットする．
void
CiCell::set_timing(
  SizeType ipin_id,                   ///< [in] 入力ピン番号
  SizeType opin_id,                   ///< [in] 出力ピン番号
  ClibTimingSense timing_sense,       ///< [in] タイミング条件
  const vector<SizeType>& timing_list ///< [in] タイミング番号のリスト
)
{
  SizeType base = (opin_id * input_num2() + ipin_id) * 2;
  switch ( timing_sense ) {
  case ClibTimingSense::positive_unate: base += 0; break;
  case ClibTimingSense::negative_unate: base += 1; break;
  default:
    ASSERT_NOT_REACHED;
  }
  mTimingMap[base] = timing_list;
}

// @brief シグネチャを返す．
CgSignature
CiCell::make_signature() const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;
  if ( no == 1 && nb == 0 && has_logic(0) ) {
    auto expr = logic_expr(0);
    auto func = expr.make_tv(input_num());
    if ( has_tristate(0) ) {
      auto tri_expr = tristate_expr(0);
      auto tristate = tri_expr.make_tv(input_num());
      return CgSignature::make_logic_sig(func, tristate);
    }
    else {
      return CgSignature::make_logic_sig(func);
    }
  }
  else {
    vector<TvFunc> logic_list(no2);
    vector<TvFunc> tristate_list(no2);
    for ( SizeType i = 0; i < no2; ++ i ) {
      if ( has_logic(i) ) {
	logic_list[i] = logic_expr(i).make_tv(ni2);
      }
      if ( has_tristate(i) ) {
	tristate_list[i] = tristate_expr(i).make_tv(ni2);
      }
    }
    return CgSignature::make_logic_sig(ni, no, nb, logic_list, tristate_list);
  }
}

// @brief ピンを登録する．
void
CiCell::reg_pin(
  CiPin* pin
)
{
  SizeType pin_id = mPinList.size();
  mPinList.push_back(unique_ptr<CiPin>{pin});
  mLibrary->reg_pin(this, pin->_name(), pin_id);
}

END_NAMESPACE_YM_CLIB