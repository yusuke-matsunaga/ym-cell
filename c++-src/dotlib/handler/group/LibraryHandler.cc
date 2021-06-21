
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LibraryHandler.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::technology,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_technology(attr_type, attr_loc); });
  reg_func(AttrType::delay_model,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_delay_model(attr_type, attr_loc); });
  reg_func(AttrType::bus_naming_style,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::comment,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::date,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::revision,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::capacitive_load_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_string(attr_type, attr_loc); });
  reg_func(AttrType::current_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::leakage_power_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::pulling_resistance_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::time_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::voltage_unit,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::lu_table_template,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   { return parser.parse_template(attr_type, attr_loc); });
  reg_func(AttrType::cell,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   { return parser.parse_cell(attr_type, attr_loc); });

}

END_NAMESPACE_YM_DOTLIB
