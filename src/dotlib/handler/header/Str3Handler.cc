﻿
/// @file Str3Handler.cc
/// @brief Str3Handler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str3Handler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str3Handler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str3Handler::Str3Handler(DotlibParser& parser) :
  Elem3Handler(parser)
{
}

// @brief デストラクタ
Str3Handler::~Str3Handler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
Str3Handler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
  mValue3 = nullptr;
}

// @brief 1つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
Str3Handler::read_header_value1(TokenType value_type,
				const FileRegion& value_loc)
{
  mValue1 = new_string(value_type, value_loc);
  return mValue1 != nullptr;
}

// @brief 2つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
Str3Handler::read_header_value2(TokenType value_type,
				const FileRegion& value_loc)
{
  mValue2 = new_string(value_type, value_loc);
  return mValue2 != nullptr;
}

// @brief 3つめのヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
Str3Handler::read_header_value3(TokenType value_type,
				const FileRegion& value_loc)
{
  mValue3 = new_string(value_type, value_loc);
  return mValue3 != nullptr;
}

END_NAMESPACE_YM_DOTLIB
