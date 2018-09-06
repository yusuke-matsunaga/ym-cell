﻿
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス SimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
SimpleHandler::SimpleHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
SimpleHandler::~SimpleHandler()
{
}

// @brief シンボルモードの値を返す．
//
// デフォルト実装では false を返す．
bool
SimpleHandler::symbol_mode()
{
  return false;
}

// @brief Simple Attribute を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
SimpleHandler::parse_simple_attribute()
{
  return parser().parse_simple_attribute(*this);
}

END_NAMESPACE_YM_DOTLIB