
/// @file UnitHandler.cc
/// @brief UnitHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "UnitHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstUnit.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief unit 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_unit(DotlibParser& parser)
{
  return new UnitHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス UnitHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
UnitHandler::UnitHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
UnitHandler::~UnitHandler()
{
}

// @brief 値をクリアする．
void
UnitHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstUnit*
UnitHandler::value() const
{
  return mValue;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
UnitHandler::begin_header()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
UnitHandler::read_value(TokenType value_type,
			       const FileRegion& value_loc,
			       int count)
{
  if ( count == 0 ) {
    if ( value_type != TokenType::INT_NUM && value_type != TokenType::FLOAT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, first element should be a number.");
      return false;
    }
    else {
      mUnitVal = parser().cur_float();
      return true;
    }
  }
  else if ( count == 1 ) {
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, second element should be a string.");
      return false;
    }
    else {
      mUnitStr = ShString(parser().cur_string());
      return true;
    }
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
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
UnitHandler::end_header(AttrType attr_type,
			const FileRegion& attr_loc,
			const FileRegion& header_loc,
			int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
    return false;
  }
  else {
    mValue = mgr().new_unit(header_loc, unit_val, unit_str);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
