
/// @file PinDirectionHandler.cc
/// @brief PinDirectionHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "PinDirectionHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstPinDirection.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PinDirectionHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinDirectionHandler::PinDirectionHandler(DotlibParser& parser) :
  StrBaseHandler(parser, false)
{
  clear_value();
}

// @brief デストラクタ
PinDirectionHandler::~PinDirectionHandler()
{
}

// @brief 値をクリアする．
void
PinDirectionHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstPinDirection*
PinDirectionHandler::value() const
{
  return mValue;
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PinDirectionHandler::read_str_value(const char* str,
				    const FileRegion& value_loc)
{
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
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  mValue = mgr().new_pin_direction(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
