
/// @file PinDirectionHandler.cc
/// @brief PinDirectionHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "PinDirectionHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstPinDirection.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'direction' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_pin_direction(DotlibParser& parser)
{
  return new PinDirectionHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス PinDirectionHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinDirectionHandler::PinDirectionHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
PinDirectionHandler::~PinDirectionHandler()
{
}

// @brief 値を読み込む．
AstNode*
PinDirectionHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. direction value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibCellPinDirection value;
  if ( strcmp(str, "input") == 0 ) {
    value = kClibCellPinInput;
  }
  else if ( strcmp(str, "output") == 0 ) {
    value = kClibCellPinOutput;
  }
  else if ( strcmp(str, "inout") == 0 ) {
    value = kClibCellPinInout;
  }
  else if ( strcmp(str, "internal") == 0 ) {
    value = kClibCellPinInternal;
  }
  else {
    ostringstream buf;
    buf << value << ": Illegal value for 'direction'."
	<< " 'input', 'output', 'inout' or 'internal' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  return mgr().new_pin_direction(loc, value);
}

END_NAMESPACE_YM_DOTLIB
