
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
    mArea{area}
{
  mInputNum = input_list.size();
  mOutputNum = output_list.size();
  mInOutNum = inout_list.size();

  int ni2 = mInputNum + mInOutNum;
  int no2 = mOutputNum + mInOutNum;
  if ( ni2 > 0 && no2 > 0 ) {
    int n = ni2 * no2 * 2;
    mTimingMap.resize(n);
  }

  // バス，バンドル関係は未完

  mBusNum = bus_list.size();

  mBundleNum = bundle_list.size();

  vector<ClibCellPin*> _pin_list;
  vector<ClibCellPin*> _input_list;
  vector<ClibCellPin*> _output_list;
  vector<ClibCellPin*> _internal_list;

  int pin_id = 0;
  for ( int i: Range(mInputNum) ) {
    CiInputPin* pin = input_list[i];

    pin->mCell = this;

    _pin_list.push_back(pin);
    _input_list.push_back(pin);

    pin->mId = pin_id; ++ pin_id;
    pin->mInputId = i;

    mLibrary->reg_pin(pin);
  }

  for ( int i: Range(mOutputNum) ) {
    CiOutputPin* pin = output_list[i];

    pin->mCell = this;

    _pin_list.push_back(pin);
    _output_list.push_back(pin);

    pin->mId = pin_id; ++ pin_id;
    pin->mOutputId = i;

    mLibrary->reg_pin(pin);
  }

  for ( int i: Range(mInOutNum) ) {
    CiInoutPin* pin = inout_list[i];

    pin->mCell = this;

    _pin_list.push_back(pin);
    _input_list.push_back(pin);
    _output_list.push_back(pin);


    pin->mId = pin_id; ++ pin_id;
    pin->mInputId = i + mInputNum;
    pin->mOutputId = i + mOutputNum;

    mLibrary->reg_pin(pin);
  }

  for ( int i: Range(internal_list.size()) ) {
    CiInternalPin* pin = internal_list[i];

    pin->mCell = this;

    _pin_list.push_back(pin);
    _internal_list.push_back(pin);

    pin->mId = pin_id; ++ pin_id;
    pin->mInternalId = i;

    mLibrary->reg_pin(pin);
  }

  mPinList.init(_pin_list);
  mInputList.init(_input_list);
  mOutputList.init(_output_list);
  mInternalList.init(_internal_list);

  mTimingList.reserve(timing_list.size());
  for ( auto timing: timing_list ) {
    mTimingList.push_back(timing);
    mTimingPool.push_back(unique_ptr<const ClibTiming>{timing});
  }
}

// @brief エラーオブジェクト用のコンストラクタ
CiCell::CiCell() :
  mLibrary(nullptr),
  mId(-1),
  mInputNum(0),
  mOutputNum(0),
  mInOutNum(0),
  mBusNum(0),
  mBusArray(nullptr),
  mBundleNum(0),
  mBundleArray(nullptr),
  mCellGroup(nullptr)
{
}

// @brief デストラクタ
CiCell::~CiCell()
{
}

// @brief ID番号の取得
// @note ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
int
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
  return mPinList.num();
}

// @brief ピンのリストの取得
const ClibCellPinList&
CiCell::pin_list() const
{
  return mPinList;
}

// @brief ピンの取得
// @param[in] pin_id ピン番号 ( 0 <= pin_id < pin_num() )
// @return ピン情報を返す．
const ClibCellPin&
CiCell::pin(int pin_id) const
{
  return mPinList[pin_id];
}

// @brief 名前からピン番号の取得
// @param[in] name ピン名
// @return name という名前のピン番号を返す．
//
// なければ -1 を返す．
int
CiCell::pin_id(const string& name) const
{
  return pin_id(ShString(name));
}

// @brief 名前からピン番号の取得
// @param[in] name ピン名
// @return name という名前のピン番号を返す．
//
// なければ -1 を返す．
int
CiCell::pin_id(const char* name) const
{
  return pin_id(ShString(name));
}

// @brief 名前からピン番号の取得
// @param[in] name ピン名
// @return name という名前のピン番号を返す．
//
// なければ -1 を返す．
int
CiCell::pin_id(const ShString& name) const
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
  return mInternalList.num();
}

// @brief 入力ピン+入出力ピン数の取得
// @note input_num() + inout_num() に等しい．
SizeType
CiCell::input_num2() const
{
  return mInputList.num();
}

// @brief 入力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < input_num2() )
const ClibCellPin&
CiCell::input(int pos) const
{
  return mInputList[pos];
}

// @brief 出力ピン+入出力ピン数の取得
// @note output_num() + inout_num() に等しい．
SizeType
CiCell::output_num2() const
{
  return mOutputList.num();
}

// @brief 出力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < output_num2() )
const ClibCellPin&
CiCell::output(int pos) const
{
  return mOutputList[pos];
}

// @brief 入出力ピンの取得
// @param[in] id 番号 ( 0 <= id < inout_num() )
const ClibCellPin&
CiCell::inout(int id) const
{
  return mInputList[id + input_num()];
}

// @brief 内部ピンの取得
// @param[in] pos 内部ピン番号 ( 0 <= pos < internal_num() )
const ClibCellPin&
CiCell::internal(int pos) const
{
  return mInternalList[pos];
}

// @brief バス数の取得
SizeType
CiCell::bus_num() const
{
  return mBusNum;
}

// @brief バスの取得
// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
const ClibBus&
CiCell::bus(int pos) const
{
  return mBusArray[pos];
}

// @brief 名前からバス番号の取得
// @param[in] name バス名
// @return name という名前のバス番号を返す．
//
// なければ -1 を返す．
int
CiCell::bus_id(const string& name) const
{
  // 未完
  return -1;
}

// @brief バンドル数の取得
SizeType
CiCell::bundle_num() const
{
  return mBundleNum;
}

// @brief バンドルの取得
// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
const ClibBundle&
CiCell::bundle(int pos) const
{
  return mBundleArray[pos];
}

// @brief 名前からバンドル番号の取得
// @param[in] name バンドル名
// @return name という名前のバンドル番号を返す．
//
// なければ -1 を返す．
int
CiCell::bundle_id(const string& name) const
{
  // 未完
  return -1;
}

// @brief タイミング情報のリストを返す．
vector<const ClibTiming*>
CiCell::timing_list() const
{
  return mTimingList;
}

// @brief 条件に合致するタイミング情報のリストを返す．
vector<const ClibTiming*>
CiCell::timing_list(
  int ipos,
  int opos,
  ClibTimingSense sense
) const
{
  int base = (opos * input_num2() + ipos) * 2;
  switch ( sense ) {
  case ClibTimingSense::positive_unate: base += 0; break;
  case ClibTimingSense::negative_unate: base += 1; break;
  default:
    ASSERT_NOT_REACHED;
  }
  return mTimingMap[base];
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
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
bool
CiCell::has_logic(int pin_id) const
{
  return output(pin_id).has_function();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCell::has_logic() const
{
  for ( int i: Range(output_num2()) ) {
    if ( !has_logic(i) ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
// @note 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiCell::logic_expr(int pin_id) const
{
  return output(pin_id).function();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
bool
CiCell::has_tristate(int pin_id) const
{
  return output(pin_id).has_three_state();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
// @note 論理式中の変数番号は入力ピン番号に対応する．
// @note 通常の論理セルの場合には定数0を返す．
Expr
CiCell::tristate_expr(int pin_id) const
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
int
CiCell::clear_preset_var1() const
{
  return 0;
}

// @brief clear_preset_var2 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
int
CiCell::clear_preset_var2() const
{
  return 0;
}

// @brief セルグループを設定する．
void
CiCell::set_group(const ClibCellGroup* group)
{
  mCellGroup = group;
}

END_NAMESPACE_YM_CLIB
