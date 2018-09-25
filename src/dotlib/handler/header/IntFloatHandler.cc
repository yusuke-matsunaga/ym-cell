
/// @file IntFloatHandler.cc
/// @brief IntFloatHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntFloatHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntFloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntFloatHandler::IntFloatHandler(DotlibParser& parser) :
  Elem2Handler(parser)
{
}

// @brief デストラクタ
IntFloatHandler::~IntFloatHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
IntFloatHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief 1つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntFloatHandler::read_header_value1(TokenType value_type,
				    const FileRegion& value_loc)
{
  mValue1 = new_int(value_type, value_loc);
  return mValue1 != nullptr;
}

// @brief 2つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntFloatHandler::read_header_value2(TokenType value_type,
				    const FileRegion& value_loc)
{
  mValue2 = new_float(value_type, value_loc);
  return mValue2 != nullptr;
}

END_NAMESPACE_YM_DOTLIB
