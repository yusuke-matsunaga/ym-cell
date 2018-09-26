
/// @file StrIntHandler.cc
/// @brief StrIntHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrIntHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrIntHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrIntHandler::StrIntHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
StrIntHandler::~StrIntHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
StrIntHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrIntHandler::read_value(int count)
{
  if ( count == 0 ) {
    return parser().read_string(mValue1);
  }
  else {
    return parser().read_int(mValue2);
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrIntHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
