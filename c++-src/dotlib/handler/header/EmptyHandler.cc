
/// @file EmptyHandler.cc
/// @brief EmptyHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/EmptyHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス EmptyHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
EmptyHandler::EmptyHandler(DotlibParser& parser) :
  ElemHandler(parser, 0)
{
}

// @brief デストラクタ
EmptyHandler::~EmptyHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
EmptyHandler::initialize()
{
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
EmptyHandler::read_value(int count)
{
  // この関数が呼ばれることはない．
  return false;
}

// @brief end_header() 内で呼ばれる終了処理関数
void
EmptyHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
