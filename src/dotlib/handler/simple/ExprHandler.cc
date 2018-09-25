
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

// @brief 式の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
ExprHandler::parse_value(const AstExpr*& dst)
{
  if ( !parser().expect(TokenType::COLON) ) {
    return false;
  }

  const AstExpr* value = parser().read_expr(TokenType::SEMI);
  if ( value != nullptr ) {
    if ( parser().expect_nl() ) {
      dst = value;
      return true;
    }
  }

  return false;
}

END_NAMESPACE_YM_DOTLIB
