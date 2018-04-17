
/// @file ComplexHandler.cc
/// @brief ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
ComplexHandler::ComplexHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
ComplexHandler::~ComplexHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
ComplexHandler::parse_attr_value(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( !parse_header() ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
