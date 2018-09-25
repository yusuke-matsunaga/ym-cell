
/// @file IntVectorHandler.cc
/// @brief IntVectorHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntVectorHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntVectorHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntVectorHandler::IntVectorHandler(DotlibParser& parser) :
  Elem1Handler(parser)
{
}

// @brief デストラクタ
IntVectorHandler::~IntVectorHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
IntVectorHandler::initialize()
{
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntVectorHandler::read_header_value1(TokenType value_type,
				     const FileRegion& value_loc)
{
  mValue = new_int_vector(value_type, value_loc);
  return mValue != nullptr;
}

END_NAMESPACE_YM_DOTLIB
