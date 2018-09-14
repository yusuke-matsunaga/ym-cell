
/// @file CompleHandler.cc
/// @brief CompleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
ComplexHandler::ComplexHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
ComplexHandler::~ComplexHandler()
{
}

// @brief Complex Attribute を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
ComplexHandler::parse_complex_attribute()
{
  return parser().parse_complex_attribute(*this);
}

END_NAMESPACE_YM_DOTLIB
