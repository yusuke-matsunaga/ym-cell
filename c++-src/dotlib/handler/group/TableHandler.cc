
/// @file TableHandler.cc
/// @brief TableHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TableHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TableHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TableHandler::TableHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::index_1,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_vector(attr_type, attr_loc); });
  reg_func(AttrType::index_2,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_vector(attr_type, attr_loc); });
  reg_func(AttrType::index_3,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_vector(attr_type, attr_loc); });
  reg_func(AttrType::values,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_values(attr_type, attr_loc); });
  reg_func(AttrType::coefs,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_vector(attr_type, attr_loc); });
  reg_func(AttrType::orders,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_vector(attr_type, attr_loc); });
  reg_func(AttrType::variable_1_range,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func(AttrType::variable_2_range,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func(AttrType::variable_3_range,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func(AttrType::domain,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_domain(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
