
/// @file CiCell.cc
/// @brief CiCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiCellPin.h"
#include "ci/CiTiming.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"
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
  ClibArea area,
  const vector<CiInputPin*>& input_list,
  const vector<CiOutputPin*>& output_list,
  const vector<CiInoutPin*>& inout_list,
  const vector<CiInternalPin*>& internal_list,
  const vector<CiBus*>& bus_list,
  const vector<CiBundle*>& bundle_list,
  const vector<CiTiming*>& timing_list
) : mLibrary{library},
    mName{name},
    mArea{area},
    mInputNum{input_list.size()},
    mOutputNum{output_list.size()},
    mInOutNum{inout_list.size()}
{
  auto ni2 = mInputNum + mInOutNum;
  auto no2 = mOutputNum + mInOutNum;
  if ( ni2 > 0 && no2 > 0 ) {
    auto n = ni2 * no2 * 2;
    mTimingMap.resize(n);
  }

  // バス，バンドル関係は未完

  mPinList.reserve(mInputNum + mOutputNum + mInOutNum + internal_list.size());
  mInputList.reserve(mInputNum + mInOutNum);
  mOutputList.reserve(mOutputNum + mInOutNum);
  mInternalList.reserve(internal_list.size());

  SizeType pin_id = 0;
  // 入力ピン
  for ( auto iid: Range(mInputNum) ) {
    auto pin = input_list[iid];
    pin->mCell = this;
    pin->mId = pin_id;
    ++ pin_id;
    pin->mInputId = iid;

    mPinList.push_back(unique_ptr<CiCellPin>{pin});
    mInputList.push_back(pin);
    mLibrary->reg_pin(pin);
  }

  // 出力ピン
  for ( auto oid: Range(mOutputNum) ) {
    auto pin = output_list[oid];
    pin->mCell = this;
    pin->mId = pin_id;
    ++ pin_id;
    pin->mOutputId = oid;

    mPinList.push_back(unique_ptr<CiCellPin>{pin});
    mOutputList.push_back(pin);
    mLibrary->reg_pin(pin);
  }

  // 入出力ピン
  for ( auto id: Range(mInOutNum) ) {
    auto pin = inout_list[id];

    pin->mCell = this;
    pin->mId = pin_id;
    ++ pin_id;
    pin->mInputId = mInputNum + id;
    pin->mOutputId = mOutputNum + id;

    mPinList.push_back(unique_ptr<CiCellPin>{pin});
    mInputList.push_back(pin);
    mOutputList.push_back(pin);
    mLibrary->reg_pin(pin);
  }

  // 内部ピン
  for ( auto id: Range(internal_list.size()) ) {
    auto pin = internal_list[id];

    pin->mCell = this;
    pin->mId = pin_id;
    ++ pin_id;
    pin->mInternalId = id;

    mPinList.push_back(unique_ptr<CiCellPin>{pin});
    mInternalList.push_back(pin);
    mLibrary->reg_pin(pin);
  }

  // タイミングリスト
  auto nt = timing_list.size();
  mTimingList.reserve(nt);
  for ( auto id: Range(nt) ) {
    auto timing = timing_list[id];
    timing->mId = id;
    mTimingList.push_back(unique_ptr<CiTiming>{timing});
  }
}

/// @brief エラーオブジェクト用のコンストラクタ
CiCell::CiCell()
{
}

/// @brief デストラクタ
CiCell::~CiCell()
{
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
const ClibCellPin&
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
  const char* name
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
  return mInOutNum;
}

// @brief 内部ピン数の取得
SizeType
CiCell::internal_num() const
{
  return mInternalList.size();
}

// @brief 入力ピン+入出力ピン数の取得
SizeType
CiCell::input_num2() const
{
  return mInputList.size();
}

// @brief 入力ピンの取得
const ClibCellPin&
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
const ClibCellPin&
CiCell::output(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < output_num2() );
  return *mOutputList[pos];
}

// @brief 入出力ピンの取得
const ClibCellPin&
CiCell::inout(
  SizeType id
) const
{
  ASSERT_COND( 0 <= id && id < inout_num() );
  return *mInputList[id + input_num()];
}

// @brief 内部ピンの取得
const ClibCellPin&
CiCell::internal(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < internal_num() );
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
  // 未完
  return -1;
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
  // 未完
  return -1;
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

// @brief 属している ClibCellGroup を返す．
const ClibCellGroup&
CiCell::cell_group() const
{
  return *mCellGroup;
}

// @brief 組み合わせ論理セルの時に true を返す．
bool
CiCell::is_logic() const
{
  return false;
}

// @brief FFセルの時に true を返す．
bool
CiCell::is_ff() const
{
  return false;
}

// @brief ラッチセルの時に true を返す．
bool
CiCell::is_latch() const
{
  return false;
}

// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
bool
CiCell::is_fsm() const
{
  return false;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiCell::has_logic(
  SizeType pin_id
) const
{
  return output(pin_id).has_function();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCell::has_logic() const
{
  for ( auto i: Range(output_num2()) ) {
    if ( !has_logic(i) ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
Expr
CiCell::logic_expr(
  SizeType pin_id
) const
{
  return output(pin_id).function();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiCell::has_tristate(
  SizeType pin_id
) const
{
  return output(pin_id).has_three_state();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
Expr
CiCell::tristate_expr(
  SizeType pin_id
) const
{
  return output(pin_id).three_state();
}

// @brief FFセルの場合にFFのピン情報を得る．
ClibFFInfo
CiCell::ff_info() const
{
  if ( is_ff() ) {
    return cell_group().ff_info();
  }
  else {
    return ClibFFInfo();
  }
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::next_state_expr() const
{
  return Expr::make_zero();
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::clock_expr() const
{
  return Expr::make_zero();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::clock2_expr() const
{
  return Expr::make_zero();
}

// @brief ラッチセルの場合にFFのピン情報を得る．
ClibLatchInfo
CiCell::latch_info() const
{
  if ( is_latch() ) {
    return cell_group().latch_info();
  }
  else {
    return ClibLatchInfo();
  }
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::data_in_expr() const
{
  return Expr::make_zero();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::enable_expr() const
{
  return Expr::make_zero();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::enable2_expr() const
{
  return Expr::make_zero();
}

// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiCell::has_clear() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
// @note クリア端子がない場合の返り値は不定
Expr
CiCell::clear_expr() const
{
  return Expr::make_zero();
}

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiCell::has_preset() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiCell::preset_expr() const
{
  return Expr::make_zero();
}

// @brief clear_preset_var1 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
SizeType
CiCell::clear_preset_var1() const
{
  return 0;
}

// @brief clear_preset_var2 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
SizeType
CiCell::clear_preset_var2() const
{
  return 0;
}

END_NAMESPACE_YM_CLIB
