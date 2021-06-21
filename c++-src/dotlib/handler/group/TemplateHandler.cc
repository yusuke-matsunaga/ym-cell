
/// @file TemplateHandler.cc
/// @brief TemplateHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TemplateHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TemplateHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TemplateHandler::TemplateHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::variable_1,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_vartype(attr_type, attr_loc); });
  reg_func(AttrType::variable_2,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_vartype(attr_type, attr_loc); });
  reg_func(AttrType::variable_3,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_vartype(attr_type, attr_loc); });
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
  reg_func(AttrType::domain,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_domain(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
