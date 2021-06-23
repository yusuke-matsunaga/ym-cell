
/// @file parse_ff.cc
/// @brief parse_ff() の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

static AttrHandlerDict handler_dict{};

END_NONAMESPACE

// @brief 'ff' group statement のパースを行う．
AstAttrPtr
parse_ff(Parser& parser,
	 const AttrKwd& attr)
{
  return parser.parse_group_statement(attr, Parser::sStrStrHeader, handler_dict);
}

// @brief 'ff_bank' group statement のパースを行う．
AstAttrPtr
parse_ff_bank(Parser& parser,
	      const AttrKwd& attr)
{
  // ヘッダが異なるだけで本体は 'ff' group と同じ
  return parser.parse_group_statement(attr, Parser::sStrStrIntHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
