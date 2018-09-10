
/// @file CellDegradationHandler.cc
/// @brief CellDegradationHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/CellDegradationHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス CellDegradationHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CellDegradationHandler::CellDegradationHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::calc_mode,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mCalcMode, attr_type, attr_loc); });
  reg_func(AttrType::index_1,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex1, attr_type, attr_loc); });
  reg_func(AttrType::values,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_values(mValues, attr_type, attr_loc); });
  reg_func(AttrType::coefs,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_coefs(mCoefs, attr_type, attr_loc); });
  reg_func(AttrType::orders,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_orders(mOrders, attr_type, attr_loc); });
  reg_func(AttrType::variable_1_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_variable_range(mVar1Range, attr_type, attr_loc); });
  reg_func(AttrType::domain,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_domain(mDomain, attr_type, attr_loc); });
}

// @brief デストラクタ
CellDegradationHandler::~CellDegradationHandler()
{
}

// @breif 'cell_degradation' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
CellDegradationHandler::parse_value(const AstCellDegradation*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
CellDegradationHandler::begin_group()
{
  mCalcMode = nullptr;
  mIndex1 = nullptr;
  mValues = nullptr;
  mVar1Range = nullptr;
  mCoefs = nullptr;
  mOrders = nullptr;
  mDomain = nullptr;

  mValue = nullptr;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
CellDegradationHandler::end_group(const FileRegion& group_loc)
{
  if ( mValues == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'values' is missing.");
    return false;
  }
  else if ( mCoefs == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'coefs' is missing.");
    return false;
  }
  else if ( mOrders == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'orders' is missing.");
    return false;
  }
  else {
    mValue = mgr().new_cell_degradation(group_loc, header_value(),
					mCalcMode, mIndex1, mValues,
					mCoefs, mOrders, mVar1Range, mDomain);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
