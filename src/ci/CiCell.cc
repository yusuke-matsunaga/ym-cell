
/// @file CiCell.cc
/// @brief CiCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
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


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] internal_list 内部ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] alloc メモリアロケータ
CiCell::CiCell(CiCellLibrary* library,
	       const ShString& name,
	       ClibArea area,
	       const vector<CiInputPin*>& input_list,
	       const vector<CiOutputPin*>& output_list,
	       const vector<CiInoutPin*>& inout_list,
	       const vector<CiInternalPin*>& internal_list,
	       const vector<CiBus*>& bus_list,
	       const vector<CiBundle*>& bundle_list,
	       Alloc& alloc)
{
  mLibrary = library;

  mName = name;
  mArea = area;

  mInputNum = input_list.size();
  mOutputNum = output_list.size();
  mInOutNum = inout_list.size();
  mInternalNum = internal_list.size();

  int ni2 = mInputNum + mInOutNum;
  int no2 = mOutputNum + mInOutNum;

  mPinNum = mInputNum + mOutputNum + mInOutNum + mInternalNum;
  if ( mPinNum > 0 ) {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * mPinNum);
    mPinArray = new (p) CiCellPin*[mPinNum];
  }
  else {
    mPinArray = nullptr;
  }

  if ( ni2 > 0 ) {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * ni2);
    mInputArray = new (p) CiCellPin*[ni2];
  }
  else {
    mInputArray = nullptr;
  }

  if ( no2 > 0 ) {
    void* q = alloc.get_memory(sizeof(CiCellPin*) * no2);
    mOutputArray = new (q) CiCellPin*[no2];
  }
  else {
    mOutputArray = nullptr;
  }

  if ( mInternalNum > 0 ) {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * mInternalNum);
    mInternalArray = new (p) CiCellPin*[mInternalNum];
  }
  else {
    mInternalArray = nullptr;
  }

  if ( ni2 > 0 && no2 > 0 ) {
    int n = ni2 * no2 * 2;
    void* s = alloc.get_memory(sizeof(const CiTimingList) * n);
    mTimingMap = new (s) CiTimingList[n];
  }
  else {
    mTimingMap = nullptr;
  }

  // バス，バンドル関係は未完

  mBusNum = bus_list.size();

  mBundleNum = bundle_list.size();

  int pin_id = 0;
  for ( int i = 0; i < mInputNum; ++ i ) {
    CiInputPin* pin = input_list[i];

    pin->mCell = this;
    mLibrary->reg_pin(pin);

    mPinArray[pin_id] = pin;
    pin->mId = pin_id; ++ pin_id;

    mInputArray[i] = pin;
    pin->mInputId = i;
  }

  for ( int i = 0; i < mOutputNum; ++ i ) {
    CiOutputPin* pin = output_list[i];

    pin->mCell = this;
    mLibrary->reg_pin(pin);

    mPinArray[pin_id] = pin;
    pin->mId = pin_id; ++ pin_id;

    mOutputArray[i] = pin;
    pin->mOutputId = i;
  }

  for ( int i = 0; i < mInOutNum; ++ i ) {
    CiInoutPin* pin = inout_list[i];

    pin->mCell = this;
    mLibrary->reg_pin(pin);

    mPinArray[pin_id] = pin;
    pin->mId = pin_id; ++ pin_id;

    mInputArray[i + mInputNum] = pin;
    pin->mInputId = i + mInputNum;

    mOutputArray[i + mOutputNum] = pin;
    pin->mOutputId = i + mOutputNum;
  }

  for ( int i = 0; i < mInternalNum; ++ i ) {
    CiInternalPin* pin = internal_list[i];

    pin->mCell = this;
    mLibrary->reg_pin(pin);

    mPinArray[pin_id] = pin;
    pin->mId = pin_id; ++ pin_id;

    mInternalArray[i] = pin;
    pin->mInternalId = i;
  }
}

// @brief デストラクタ
CiCell::~CiCell()
{
  // メモリの確保は別のクラスが担当している．
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
int
CiCell::pin_num() const
{
  return mPinNum;
}

// @brief ピンの取得
// @param[in] id ピン番号 ( 0 <= id < pin_num() )
const ClibCellPin*
CiCell::pin(int id) const
{
  return mPinArray[id];
}

// @brief 名前からピンの取得
// @param[in] name ピン名
// @return name という名前をピンを返す．
// @note なければ nullptr を返す．
const ClibCellPin*
CiCell::pin(const string& name) const
{
  return mLibrary->get_pin(this, ShString(name));
}

// @brief 名前からピンの取得
// @param[in] name ピン名
// @return name という名前をピンを返す．
// @note なければ nullptr を返す．
const ClibCellPin*
CiCell::pin(const char* name) const
{
  return mLibrary->get_pin(this, ShString(name));
}

// @brief 入力ピン数の取得
int
CiCell::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数の取得
int
CiCell::output_num() const
{
  return mOutputNum;
}

// @brief 入出力ピン数の取得
int
CiCell::inout_num() const
{
  return mInOutNum;
}

// @brief 内部ピン数の取得
int
CiCell::internal_num() const
{
  return mInternalNum;
}

// @brief 入力ピン+入出力ピン数の取得
// @note input_num() + inout_num() に等しい．
int
CiCell::input_num2() const
{
  return mInputNum + mInOutNum;
}

// @brief 入力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < input_num2() )
const ClibCellPin*
CiCell::input(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < input_num2() );

  return mInputArray[pos];
}

// @brief 出力ピン+入出力ピン数の取得
// @note output_num() + inout_num() に等しい．
int
CiCell::output_num2() const
{
  return mOutputNum + mInOutNum;
}

// @brief 出力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < output_num2() )
const ClibCellPin*
CiCell::output(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < output_num2() );

  return mOutputArray[pos];
}

// @brief 内部ピンの取得
// @param[in] pos 内部ピン番号 ( 0 <= pos < internal_num() )
const ClibCellPin*
CiCell::internal(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < internal_num() );

  return mInternalArray[pos];
}

// @brief バス数の取得
int
CiCell::bus_num() const
{
  return mBusNum;
}

// @brief バスの取得
// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
const ClibBus*
CiCell::bus(int pos) const
{
  return &mBusArray[pos];
}

// @brief 名前からバスの取得
// @param[in] name バス名
// @return name という名前のバスを返す．
// @note なければ nullptr を返す．
const ClibBus*
CiCell::bus(const string& name) const
{
  // 未完
  return nullptr;
}

// @brief バンドル数の取得
int
CiCell::bundle_num() const
{
  return mBundleNum;
}

// @brief バンドルの取得
// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
const ClibBundle*
CiCell::bundle(int pos) const
{
  return &mBundleArray[pos];
}

// @brief 名前からバンドルの取得
const ClibBundle*
CiCell::bundle(const string& name) const
{
  // 未完
  return nullptr;
}

// @brief タイミング情報のリストを返す．
const ClibTimingList&
CiCell::timing_list() const
{
  return mTimingList;
}

// @brief タイミング情報を返す．
// @param[in] tid タイミング番号 ( 0 <= tid < timing_list().num() )
const ClibTiming*
CiCell::timing(int pos) const
{
  return mTimingList[pos];
}

// @brief 条件に合致するタイミング情報のリストを返す．
// @param[in] ipos 開始ピン番号 ( 0 <= ipos < input_num2() )
// @param[in] opos 終了ピン番号 ( 0 <= opos < output_num2() )
// @param[in] timing_sense タイミング情報の摘要条件
const ClibTimingList&
CiCell::timing_list(int ipos,
		    int opos,
		    ClibTimingSense sense) const
{
  int base = (opos * input_num2() + ipos) * 2;
  switch ( sense ) {
  case kClibPosiUnate: base += 0; break;
  case kClibNegaUnate: base += 1; break;
  default:
    ASSERT_NOT_REACHED;
  }
  return mTimingMap[base];
}

// @brief 属している ClibCellGroup を返す．
const ClibCellGroup*
CiCell::cell_group() const
{
  return mClibCellGroup;
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
  return output(pin_id)->has_function();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCell::has_logic() const
{
  for ( int i = 0; i < output_num2(); ++ i ) {
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
  return output(pin_id)->function();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
bool
CiCell::has_tristate(int pin_id) const
{
  return output(pin_id)->has_three_state();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
// @note 論理式中の変数番号は入力ピン番号に対応する．
// @note 通常の論理セルの場合には定数0を返す．
Expr
CiCell::tristate_expr(int pin_id) const
{
  return output(pin_id)->three_state();
}

// @brief FFセルの場合にFFのピン情報を得る．
ClibFFInfo
CiCell::ff_info() const
{
  if ( is_ff() ) {
    return cell_group()->ff_info();
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
  return Expr::const_zero();
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::clock_expr() const
{
  return Expr::const_zero();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::clock2_expr() const
{
  return Expr::const_zero();
}

// @brief ラッチセルの場合にFFのピン情報を得る．
ClibLatchInfo
CiCell::latch_info() const
{
  if ( is_latch() ) {
    return cell_group()->latch_info();
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
  return Expr::const_zero();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::enable_expr() const
{
  return Expr::const_zero();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiCell::enable2_expr() const
{
  return Expr::const_zero();
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
  return Expr::const_zero();
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
  return Expr::const_zero();
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
  mClibCellGroup = group;
}

END_NAMESPACE_YM_CLIB
