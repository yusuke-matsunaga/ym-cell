
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/InputVoltageHandler.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::vil,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::vih,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::vimin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::vimax,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
