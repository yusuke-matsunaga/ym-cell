
/// @file ComplexHandler.cc
/// @brief ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"
//#include "DotlibParserImpl.h"
//#include "DotlibList.h"
//#include "DotlibInt.h"
//#include "DotlibFloat.h"
//#include "DotlibFloatVector.h"
//#include "DotlibString.h"
//#include "GroupHandler.h"
//#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] vector_mode ベクターモードで読み込むとき true にするフラグ
ComplexHandler::ComplexHandler(DotlibParser& parser,
			       bool vector_mode) :
  DotlibHandler(parser),
  mVectorMode(vector_mode)
{
}

// @brief デストラクタ
ComplexHandler::~ComplexHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら nullptr を返す．
DotlibNode*
ComplexHandler::read_attr(AttrType attr_type,
			  const FileRegion& attr_loc)
{
  FileRegion end_loc;
  DotlibList* value_list = parse_complex(mVectorMode, end_loc);
  if ( value_list == nullptr ) {
    return nullptr;
  }

  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << value_list << endl;
  }

  return gen_value(value_list);
}

END_NAMESPACE_YM_DOTLIB
