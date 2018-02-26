﻿
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
// @param[in] id ID番号
// @param[in] name 名前
// @param[in] area 面積
// @param[in] ni 入力ピン数
// @param[in] no 出力ピン数
// @param[in] nio 入出力ピン数
// @param[in] nit 内部ピン数
// @param[in] nb バス数
// @param[in] nc バンドル数
// @param[in] output_array 出力の情報の配列(*1)
// @param[in] logic_array 出力の論理式の配列
// @param[in] tristated_array トライステート条件の論理式の配列
// @param[in] alloc メモリアロケータ
// *1: - false 論理式なし
//     - true 論理式あり
CiCell::CiCell(CiCellLibrary* library,
	       ymuint id,
	       const ShString& name,
	       ClibArea area,
	       ymuint ni,
	       ymuint no,
	       ymuint nio,
	       ymuint nit,
	       ymuint nb,
	       ymuint nc,
	       const vector<bool>& output_array,
	       const vector<Expr>& logic_array,
	       const vector<Expr>& tristate_array,
	       Alloc& alloc)
{
  mLibrary = library;

  mId = id;
  mName = name;
  mArea = area;

  ymuint ni2 = ni + nio;
  ymuint no2 = no + nio;

  mPinNum = ni + no + nio + nit;
  {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * mPinNum);
    mPinArray = new (p) CiCellPin*[mPinNum];
  }

  mInputNum = ni;
  {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * ni2);
    mInputArray = new (p) CiCellPin*[ni2];
  }

  mOutputNum = no;
  {
    void* q = alloc.get_memory(sizeof(CiCellPin*) * no2);
    mOutputArray = new (q) CiCellPin*[no2];
  }

  mInternalNum = nit;
  if ( nit > 0 ) {
    void* p = alloc.get_memory(sizeof(CiCellPin*) * nit);
    mInternalArray = new (p) CiCellPin*[nit];
  }
  else {
    mInternalArray = nullptr;
  }

  {
    int n = ni2 * no2 * 2;
    void* s = alloc.get_memory(sizeof(const CiTimingList) * n);
    mTimingMap = new (s) CiTimingList[n];
  }

  // バス，バンドル関係は未完

  mBusNum = nb;

  mBundleNum = nc;

  void* x = alloc.get_memory(sizeof(ymuint8) * no2);
  mLTArray = new (x) ymuint8[no2];

  void* t = alloc.get_memory(sizeof(Expr) * no2);
  mLogicArray = new (t) Expr[no2];

  void* u = alloc.get_memory(sizeof(Expr) * no2);
  mTristateArray = new (u) Expr[no2];

  for (ymuint i = 0; i < no2; ++ i) {
    ymuint8 val = 0U;
    if ( output_array[i] ) {
      if ( !tristate_array[i].is_zero() ) {
	val = 2U;
      }
      else {
	val = 1U;
      }
    }
    mLTArray[i] = val;
    mLogicArray[i] = logic_array[i];
    mTristateArray[i] = tristate_array[i];
  }
}

// @brief デストラクタ
CiCell::~CiCell()
{
  // メモリの確保は別のクラスが担当している．
}

// @brief ID番号の取得
// @note ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
ymuint
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
ymuint
CiCell::pin_num() const
{
  return mPinNum;
}

// @brief ピンの取得
// @param[in] id ピン番号 ( 0 <= id < pin_num() )
const ClibCellPin*
CiCell::pin(ymuint id) const
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
ymuint
CiCell::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数の取得
ymuint
CiCell::output_num() const
{
  return mOutputNum;
}

// @brief 入出力ピン数の取得
ymuint
CiCell::inout_num() const
{
  return mPinNum - mInputNum - mOutputNum - mInternalNum;
}

// @brief 内部ピン数の取得
ymuint
CiCell::internal_num() const
{
  return mInternalNum;
}

// @brief 入力ピン+入出力ピン数の取得
// @note input_num() + inout_num() に等しい．
ymuint
CiCell::input_num2() const
{
  return mInputNum + inout_num();
}

// @brief 入力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < input_num2() )
const ClibCellPin*
CiCell::input(ymuint pos) const
{
  return mInputArray[pos];
}

// @brief 出力ピン+入出力ピン数の取得
// @note output_num() + inout_num() に等しい．
ymuint
CiCell::output_num2() const
{
  return mOutputNum + inout_num();
}

// @brief 出力ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < output_num2() )
const ClibCellPin*
CiCell::output(ymuint pos) const
{
  return mOutputArray[pos];
}

// @brief 内部ピンの取得
// @param[in] internal_id 内部ピン番号 ( 0 <= internal_id < internal_num() )
const ClibCellPin*
CiCell::internal(ymuint internal_id) const
{
  return mInternalArray[internal_id];
}

// @brief バス数の取得
ymuint
CiCell::bus_num() const
{
  return mBusNum;
}

// @brief バスの取得
// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
const ClibBus*
CiCell::bus(ymuint pos) const
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
ymuint
CiCell::bundle_num() const
{
  return mBundleNum;
}

// @brief バンドルの取得
// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
const ClibBundle*
CiCell::bundle(ymuint pos) const
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
CiCell::timing_num(ymuint ipos,
		   ymuint opos,
		   ClibTimingSense sense) const
{
  ymuint base = (opos * input_num2() + ipos) * 2;
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
CiCell::has_logic(ymuint pin_id) const
{
  return mLTArray[pin_id] != 0U;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCell::has_logic() const
{
  for (ymuint i = 0; i < output_num2(); ++ i) {
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
CiCell::logic_expr(ymuint pin_id) const
{
  return mLogicArray[pin_id];
}

// @brief 出力がトライステート条件を持っている時に true を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
bool
CiCell::has_tristate(ymuint pin_id) const
{
  return mLTArray[pin_id] == 2U;
}

// @brief トライステートセルの場合にトライステート条件式を返す．
// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
// @note 論理式中の変数番号は入力ピン番号に対応する．
// @note 通常の論理セルの場合には定数0を返す．
Expr
CiCell::tristate_expr(ymuint pin_id) const
{
  return mTristateArray[pin_id];
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
ymuint
CiCell::clear_preset_var1() const
{
  return 0;
}

// @brief clear_preset_var2 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
ymuint
CiCell::clear_preset_var2() const
{
  return 0;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiCell::dump(ODO& s) const
{
  ymuint8 tid = 0;
  if ( is_logic() ) {
    tid = 0;
  }
  else if ( is_ff() ) {
    tid = 1;
  }
  else if ( is_latch() ) {
    tid = 2;
  }
  else if ( is_fsm() ) {
    tid = 3;
  }
  else {
    // 無視？
    ASSERT_NOT_REACHED;
  }
  ymuint ni = input_num();
  ymuint no = output_num();
  ymuint nio = inout_num();
  ymuint nit = internal_num();
  ymuint nbus = bus_num();
  ymuint nbundle = bundle_num();

  s << tid
    << name()
    << area()
    << ni
    << no
    << nio
    << nit
    << nbus
    << nbundle;

  ymuint no2 = no + nio;
  for (ymuint opos = 0; opos < no2; ++ opos) {
    s << has_logic()
      << logic_expr(opos)
      << tristate_expr(opos);
  }

  if ( is_ff() ) {
    s << next_state_expr()
      << clock_expr()
      << clock2_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }
  else if ( is_latch() ) {
    s << data_in_expr()
      << enable_expr()
      << enable2_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }

  // 入力ピンのダンプ
  for (ymuint ipin = 0; ipin < ni; ++ ipin) {
    input(ipin)->dump(s);
  }

  // 出力ピンのダンプ
  for (ymuint opin = 0; opin < no; ++ opin) {
    output(opin)->dump(s);
  }

  // 入出力ピンのダンプ
  for (ymuint iopin = 0; iopin < nio; ++ iopin) {
    output(iopin)->dump(s);
  }

  // 内部ピンのダンプ
  for (ymuint itpin = 0; itpin < nit; ++ itpin) {
    internal(itpin)->dump(s);
  }

  // タイミング情報のダンプ
  ymuint nt = timing_num();
  s << nt;
  for (ymuint i = 0; i < nt; ++ i) {
    timing(i)->dump(s);
  }

  // ちょっと効率が悪いけど線形探索を用いている．
  // 効率が気になるならハッシュ関数を用いればよい．
  for (ymuint ipos = 0; ipos < ni + nio; ++ ipos) {
    for (ymuint opos = 0; opos < no + nio; ++ opos) {
      ymuint np = timing_num(ipos, opos, kClibPosiUnate);
      s << np;
      for (ymuint i = 0; i < np; ++ i) {
	const ClibTiming* timing1 = timing(ipos, opos, kClibPosiUnate, i);
	for (ymuint j = 0; j < nt; ++ j) {
	  if ( timing(j) == timing1 ) {
	    s << j;
	  }
	}
      }
      ymuint nn = timing_num(ipos, opos, kClibNegaUnate);
      s << nn;
      for (ymuint i = 0; i < nn; ++ i) {
	const ClibTiming* timing1 = timing(ipos, opos, kClibNegaUnate, i);
	for (ymuint j = 0; j < nt; ++ j) {
	  if ( timing(j) == timing1 ) {
	    s << j;
	  }
	}
      }
    }
  }
}

// @brief セルグループを設定する．
void
CiCell::set_group(const ClibCellGroup* group)
{
  mClibCellGroup = group;
}

END_NAMESPACE_YM_CLIB
