
/// @file DotlibHandler.cc
/// @brief DotlibHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/SimpleHandler.h"
#include "dotlib/CGHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DotlibHandler::DotlibHandler(DotlibParser& parser) :
  mParser(parser)
{
}

// @brief デストラクタ
DotlibHandler::~DotlibHandler()
{
}

#if 0
// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibHandler::expect(TokenType type)
{
  return mParser.expect(type);
}

// @brief 行末まで読み込む．
bool
DotlibHandler::expect_nl()
{
  return mParser.expect_nl();
}

#endif


//////////////////////////////////////////////////////////////////////
// クラス CGHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser
CGHandler::CGHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
CGHandler::~CGHandler()
{
}

END_NAMESPACE_YM_DOTLIB
