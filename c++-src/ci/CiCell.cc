
/// @file CiCell.cc
/// @brief CiCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiPin.h"
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
  CiCellGroup* group,
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
    mGroup{group},
    mName{name},
    mArea{area},
    mInputNum{input_list.size()},
    mOutputNum{output_list.size()},
    mInOutNum{inout_list.size()}
{
  mPinList.reserve(mInputNum + mOutputNum + mInOutNum + internal_list.size());

  // 入力ピン
  mInputList.reserve(mInputNum + mInOutNum);
  for ( auto pin: input_list ) {
    auto pin_id = mPinList.size();
    auto iid = mInputList.size();
    pin->mInputId = iid;

    mPinList.push_back(unique_ptr<CiPin>{pin});
    mInputList.push_back(pin);
    mLibrary->reg_pin(this, pin->_name(), pin_id);
  }

  // 出力ピン
  mOutputList.reserve(mOutputNum + mInOutNum);
  for ( auto pin: output_list ) {
    auto pin_id = mPinList.size();
    auto oid = mOutputList.size();
    pin->mOutputId = oid;

    mPinList.push_back(unique_ptr<CiPin>{pin});
    mOutputList.push_back(pin);
    mLibrary->reg_pin(this, pin->_name(), pin_id);
  }

  // 入出力ピン
  for ( auto pin: inout_list ) {
    auto pin_id = mPinList.size();
    auto iid = mInputList.size();
    auto oid = mOutputList.size();
    pin->mInputId = iid;
    pin->mOutputId = oid;

    mPinList.push_back(unique_ptr<CiPin>{pin});
    mInputList.push_back(pin);
    mOutputList.push_back(pin);
    mLibrary->reg_pin(this, pin->_name(), pin_id);
  }

  // 内部ピン
  mInternalList.reserve(internal_list.size());
  for ( auto pin: internal_list ) {
    auto pin_id = mPinList.size();
    auto id = mInternalList.size();
    pin->mInternalId = id;

    mPinList.push_back(unique_ptr<CiPin>{pin});
    mInternalList.push_back(pin);
    mLibrary->reg_pin(this, pin->_name(), pin_id);
  }

  // bus
  mBusList.reserve(bus_list.size());
  for ( auto bus: bus_list ) {
    auto id = mBusList.size();
    mBusList.push_back(unique_ptr<CiBus>{bus});
    mLibrary->reg_bus(this, bus->_name(), id);
  }

  // bundle
  mBundleList.reserve(bundle_list.size());
  for ( auto bundle: bundle_list ) {
    auto id = mBusList.size();
    mBundleList.push_back(unique_ptr<CiBundle>{bundle});
    mLibrary->reg_bundle(this, bundle->_name(), id);
  }

  // タイミングリスト
  mTimingList.reserve(timing_list.size());
  for ( auto timing: timing_list ) {
    auto id = mTimingList.size();
    timing->mId = id;
    mTimingList.push_back(unique_ptr<CiTiming>{timing});
  }

  auto ni2 = mInputNum + mInOutNum;
  auto no2 = mOutputNum + mInOutNum;
  if ( ni2 > 0 && no2 > 0 ) {
    auto n = ni2 * no2 * 2;
    mTimingMap.resize(n);
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
  return mLibrary->get_bus_id(this, ShString(name));
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
  return mLibrary->get_bundle_id(this, ShString(name));
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

// @brief セルグループを返す．
const ClibCellGroup&
CiCell::cgroup() const
{
  ASSERT_COND( mGroup != nullptr );
  return *mGroup;
}

END_NAMESPACE_YM_CLIB
