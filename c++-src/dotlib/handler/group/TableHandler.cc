
/// @file TableHandler.cc
/// @brief TableHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/TableHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TableHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TableHandler::TableHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::index_1,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_vector(mIndex1, attr_type, attr_loc); });
  reg_func(AttrType::index_2,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_vector(mIndex2, attr_type, attr_loc); });
  reg_func(AttrType::index_3,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_vector(mIndex3, attr_type, attr_loc); });
  reg_func(AttrType::values,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_values(mValues, attr_type, attr_loc); });
  reg_func(AttrType::coefs,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_vector(mCoefs, attr_type, attr_loc); });
  reg_func(AttrType::orders,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int_vector(mOrders, attr_type, attr_loc); });
  reg_func(AttrType::variable_1_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_float(mVar1Range, attr_type, attr_loc); });
  reg_func(AttrType::variable_2_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_float(mVar2Range, attr_type, attr_loc); });
  reg_func(AttrType::variable_3_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_float(mVar3Range, attr_type, attr_loc); });
  reg_func(AttrType::domain,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_domain(mDomain, attr_type, attr_loc); });
}

// @brief デストラクタ
TableHandler::~TableHandler()
{
}

// @brief グループ記述の始まり
void
TableHandler::begin_group()
{
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;
  mValues = nullptr;
  mCoefs = nullptr;
  mOrders = nullptr;
  mVar1Range = nullptr;
  mVar2Range = nullptr;
  mVar3Range = nullptr;
  mDomain = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TableHandler::end_group()
{
  if ( mValues == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'values' is missing.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
