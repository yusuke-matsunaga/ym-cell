
/// @file IntHandler.cc
/// @brief IntHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/IntHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntHandler::IntHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
}

// @brief デストラクタ
IntHandler::~IntHandler()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntHandler::read_value(TokenType value_type,
		       const FileRegion& value_loc)
{
  mValue = new_int(value_type, value_loc);
  return mValue != nullptr;
}

END_NAMESPACE_YM_DOTLIB
