
/// @file StrStrStrHandler.cc
/// @brief StrStrStrHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrStrStrHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrStrStrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrStrStrHandler::StrStrStrHandler(DotlibParser& parser) :
  ElemHandler(parser, 3)
{
}

// @brief デストラクタ
StrStrStrHandler::~StrStrStrHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
StrStrStrHandler::initialize()
{
  mValue[0] = nullptr;
  mValue[1] = nullptr;
  mValue[2] = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrStrStrHandler::read_value(int count)
{
  ASSERT_COND( count >= 0 && count < 3);

  return parser().read_string(mValue[count]);
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrStrStrHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
