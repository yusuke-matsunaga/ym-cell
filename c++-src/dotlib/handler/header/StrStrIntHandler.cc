
/// @file StrStrIntHandler.cc
/// @brief StrStrIntHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrStrIntHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrStrIntHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
StrStrIntHandler::StrStrIntHandler(DotlibParser& parser) :
  ElemHandler(parser, 3)
{
}

// @brief デストラクタ
StrStrIntHandler::~StrStrIntHandler()
{
}


// @brief begin_header() 内で呼ばれる初期化関数
void
StrStrIntHandler::initialize()
{
  mValue[0] = nullptr;
  mValue[1] = nullptr;
  mValue3 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrStrIntHandler::read_value(int count)
{
  ASSERT_COND( count >= 0 && count < 3 );

  if ( count < 2 ) {
    return parser().read_string(mValue[count]);
  }
  else {
    return parser().read_int(mValue3);
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrStrIntHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
