
/// @file Str1Handler.cc
/// @brief Str1Handler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str1Handler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str1Handler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str1Handler::Str1Handler(DotlibParser& parser) :
  Elem1Handler(parser)
{
}

// @brief デストラクタ
Str1Handler::~Str1Handler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
Str1Handler::initialize()
{
  mValue = nullptr;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
Str1Handler::read_header_value1(TokenType value_type,
				const FileRegion& value_loc)
{
  mValue = new_string(value_type, value_loc);
  return mValue != nullptr;
}

END_NAMESPACE_YM_DOTLIB
