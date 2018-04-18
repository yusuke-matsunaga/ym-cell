
/// @file ExprHandler.cc
/// @brief ExprHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ExprHandler.h"
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
  clear_value();
}

// @brief デストラクタ
ExprHandler::~ExprHandler()
{
}

// @brief 値をクリアする．
void
ExprHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstExpr*
ExprHandler::value() const
{
  return mValue;
}

// @brief 属性値を読み込む．
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
ExprHandler::parse_attr_value()
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  mValue = parser().read_expr(TokenType::SEMI);
  if ( mValue == nullptr ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
