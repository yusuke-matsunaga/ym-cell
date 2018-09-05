
/// @file ExprHandler.cc
/// @brief ExprHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ExprHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ExprHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
ExprHandler::ExprHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
ExprHandler::~ExprHandler()
{
}

// @brief int 値の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstExpr*
ExprHandler::parse_value()
{
  if ( !parser().expect(TokenType::COLON) ) {
    return nullptr;
  }

  AstExpr* value = parser().read_expr(TokenType::SEMI);
  if ( value != nullptr ) {
    if ( parser().expect_nl() ) {
      return value;
    }
  }

  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
