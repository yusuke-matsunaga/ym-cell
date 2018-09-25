
/// @file FloatStrHandler.cc
/// @brief FloatStrHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FloatStrHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatStrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatStrHandler::FloatStrHandler(DotlibParser& parser) :
  Elem2Handler(parser)
{
}

// @brief デストラクタ
FloatStrHandler::~FloatStrHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
FloatStrHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief 1つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatStrHandler::read_header_value1(TokenType value_type,
				    const FileRegion& value_loc)
{
  mValue1 = new_float(value_type, value_loc);
  return mValue1 != nullptr;
}

// @brief 2つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatStrHandler::read_header_value2(TokenType value_type,
				    const FileRegion& value_loc)
{
  mValue2 = new_string(value_type, value_loc);
  return mValue2 != nullptr;
}

END_NAMESPACE_YM_DOTLIB
