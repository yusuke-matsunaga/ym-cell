
/// @file DomainHandler.cc
/// @brief DomainHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DomainHandler.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DomainHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DomainHandler::DomainHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func("calc_mode,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("coefs,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_vector(attr_type, attr_loc); });
  reg_func("orders,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_vector(attr_type, attr_loc); });
  reg_func("variable_1_range,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func("variable_2_range,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func("variable_3_range,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
