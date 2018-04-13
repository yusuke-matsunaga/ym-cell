
/// @file ComplexHandler.cc
/// @brief ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ダミーの complex ハンドラを作る．
DotlibHandler*
HandlerFactory::new_complex(DotlibParser& parser)
{
  return new ComplexHandler(parser, false);
}


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
const AstNode*
ComplexHandler::parse_attr_value(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  FileRegion value_loc;
  vector<const AstNode*> value_list;
  if ( !parse_complex(mVectorMode, value_loc, value_list) ) {
    return nullptr;
  }

  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << "(";
    for ( auto value: value_list ) {
      cout << " " << value;
    }
    cout << ")" << endl;
  }

  return gen_node(value_loc, value_list);
}

// @brief 値を表すノードを作る．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
// @return value_list に対応した AstNode を返す．
const AstNode*
ComplexHandler::gen_node(const FileRegion& loc,
			 const vector<const AstNode*>& value_list)
{
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
