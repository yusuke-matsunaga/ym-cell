
/// @file CellHandler.cc
/// @brief CellHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/CellHandler.h"
#include "dotlib/BoolHandler.h"
#include "dotlib/ExprHandler.h"
#include "dotlib/FloatHandler.h"
#include "dotlib/PinHandler.h"
#include "dotlib/StringHandler.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] parser パーサー
CellHandler::CellHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
CellHandler::~CellHandler()
{
}

// @breif 'cell' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
CellHandler::parse_value(const AstCell*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
CellHandler::begin_group()
{
  mArea = nullptr;
  mAuxiliaryPadCell = nullptr;
  mBaseName = nullptr;
  mBusNamingStyle = nullptr;
  mCellLeakagePower = nullptr;
  mClockIntegratedCell = nullptr;
  mContentionCondition = nullptr;
  mDontFault = nullptr;
  mDontTouch = nullptr;
  mDriverType = nullptr;
  mEmTempDegradation = nullptr;
  mFpgaDomainStyle = nullptr;
  mGeometryPrint = nullptr;
  mHandleNegativeConstraint = nullptr;
  mInterfaceTiming = nullptr;
  mIoType = nullptr;
  mIsClockGating = nullptr;
  mMapOnly = nullptr;
  mPadCell = nullptr;
  mPowerCellType = nullptr;
  mPreferred = nullptr;
  mScalingFactors = nullptr;
  mSingleBitDegenerate = nullptr;
  mSlewType = nullptr;
  mTimingModelType = nullptr;
  mUseForSizeOnly = nullptr;
  mVhdlName = nullptr;
  mPinEqual = nullptr;
  mPinOpposite[0] = nullptr;
  mPinOpposite[1] = nullptr;
  mRailConnection[0] = nullptr;
  mRailConnection[1] = nullptr;
  mResourceUsageName = nullptr;
  mResourceUsageInt = nullptr;
  mBundleList.clear();
  mBusList.clear();
  mDynamicCurrentList.clear();
  mFF = nullptr;
  mFFBank = nullptr;
  mFunctionalYieldMetric = nullptr;
  mGeneratedClockList.clear();
  mIntrinsicParasiticList.clear();
  mLatch = nullptr;
  mLatchBank = nullptr;
  mLeakageCurrentList.clear();
  mLeakagePowerList.clear();
  mModeList.clear();
  mPinList.clear();
  mRoutingTrackList.clear();
  mStateTable = nullptr;
  mTestCell = nullptr;
  mTypeList.clear();

  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
CellHandler::read_group_attr(AttrType attr_type,
			     const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::area: return parse_float(mArea, attr_type, attr_loc);
  default:
    break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
CellHandler::end_group(const FileRegion& group_loc)
{
  return false;
}

END_NAMESPACE_YM_DOTLIB
