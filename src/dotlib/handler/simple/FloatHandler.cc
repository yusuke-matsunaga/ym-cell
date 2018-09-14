﻿
/// @file FloatHandler.cc
/// @brief FloatHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FloatHandler.h"
//#include "dotlib/DotlibParser.h"
//#include "dotlib/TokenType.h"
//#include "dotlib/AstMgr.h"
//#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatHandler::FloatHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
}

// @brief デストラクタ
FloatHandler::~FloatHandler()
{
}

// @brief float 値の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
FloatHandler::parse_value(const AstFloat*& dst)
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatHandler::read_value(TokenType value_type,
			 const FileRegion& value_loc)
{
  mValue = new_float(value_type, value_loc);
  return mValue != nullptr;
}

END_NAMESPACE_YM_DOTLIB
