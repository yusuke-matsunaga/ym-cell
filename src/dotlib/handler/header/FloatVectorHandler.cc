
/// @file FloatVectorHandler.cc
/// @brief FloatVectorHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FloatVectorHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatVectorHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatVectorHandler::FloatVectorHandler(DotlibParser& parser) :
  Elem1Handler(parser)
{
}

// @brief デストラクタ
FloatVectorHandler::~FloatVectorHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
FloatVectorHandler::initialize()
{
  mValueList.clear();
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatVectorHandler::read_header_value1(TokenType value_type,
				       const FileRegion& value_loc)
{
  return read_float_vector(value_type, value_loc, mValueList);
}

END_NAMESPACE_YM_DOTLIB
