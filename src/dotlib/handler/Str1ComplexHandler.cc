
/// @file Str1ComplexHandler.cc
/// @brief Str1ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "Str1ComplexHandler.h"
#include "dotlib/AstString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ダミーの complex ハンドラを作る．
DotlibHandler*
HandlerFactory::new_str1_complex(DotlibParser& parser)
{
  return new Str1ComplexHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス Str1ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str1ComplexHandler::Str1ComplexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
Str1ComplexHandler::~Str1ComplexHandler()
{
}

// @brief 値をクリアする．
void
Str1ComplexHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstString*
Str1ComplexHandler::value() const
{
  return mValue;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str1ComplexHandler::begin_header()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str1ComplexHandler::read_value(TokenType value_type,
			       const FileRegion& value_loc,
			       int count)
{
  if ( value_type == TokenType::SYMBOL && count == 0 ) {
    mValue = mgr().new_string(value_loc, ShString(parser().cur_string()));
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc attr_type のファイル上の位置
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str1ComplexHandler::end_header(AttrType attr_type,
			       const FileRegion& attr_loc,
			       const FileRegion& header_loc,
			       int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
