
/// @file StrStrHandler.cc
/// @brief StrStrHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrStrHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrStrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrStrHandler::StrStrHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
StrStrHandler::~StrStrHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
StrStrHandler::initialize()
{
  mValue[0] = nullptr;
  mValue[0] = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrStrHandler::read_value(int count)
{
  ASSERT_COND( count == 0 || count == 1 );

  return parser().read_string(mValue[count]);
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrStrHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
