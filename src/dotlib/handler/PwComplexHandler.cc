
/// @file PwComplexHandler.cc
/// @brief PwComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "PwComplexHandler.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief piece wise 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_piece_wise(DotlibParser& parser)
{
  return new PwComplexHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス PwComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PwComplexHandler::PwComplexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
PwComplexHandler::~PwComplexHandler()
{
}

// @brief 値をクリアする．
void
PwComplexHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstPieceWise*
PwComplexHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
PwComplexHandler::read_value(TokenType value_type,
			     const FileRegion& value_loc,
			     int count)
{
  if ( count == 0 ) {
    if ( value_type != TokenType::INT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, first element should be an integer number.");
      return false;
    }
    else {
      mVal1 = mgr().new_int(value_loc, parser().cur_int());
      return true;
    }
  }
  else if ( count == 1 ) {
    if ( value_type != TokenType::INT_NUM && value_type != TokenType::FLOAT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, second element should be a float number.");
      return false;
    }
    else {
      mVal2 = mgr().new_float(value_loc, parser().cur_float());
      return true;
    }
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
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
PwComplexHandler::end_header(AttrType attr_type,
			     const FileRegion& attr_loc,
			     const FileRegion& header_loc,
			     int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return false;
  }
  else {
    mValue = mgr().new_piecewise(mVal1, mVal2);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
