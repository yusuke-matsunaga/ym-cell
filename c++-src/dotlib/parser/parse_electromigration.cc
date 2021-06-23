
/// @file parse_electromigration.cc
/// @brief parse_electromigration() の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'electromigration' group statement のパースを行う．
AstAttrPtr
parse_electromigration(Parser& parser,
		       const AttrKwd& attr)
{
  static AttrHandlerDict handler_dict{};
  return parser.parse_group_statement(attr, Parser::sStrHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
