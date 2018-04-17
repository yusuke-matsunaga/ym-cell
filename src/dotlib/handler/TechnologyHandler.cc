
/// @file TechnologyHandler.cc
/// @brief TechnologyHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "TechnologyHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstTechnology.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'technology' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_technology(DotlibParser& parser)
{
  return new TechnologyHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TechnologyHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TechnologyHandler::TechnologyHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
TechnologyHandler::~TechnologyHandler()
{
}

// @brief 値をクリアする．
void
TechnologyHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstTechnology*
TechnologyHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TechnologyHandler::read_value(TokenType value_type,
			      const FileRegion& value_loc)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. technology value is expected.");
    return false;
  }

  const char* str = parser().cur_string();
  ClibTechnology value;
  if ( strcmp(str, "cmos") == 0 ) {
    value = kClibTechCmos;
  }
  else if ( strcmp(str, "fpga") == 0 ) {
    value = kClibTechFpga;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. only 'asic' or 'fpga' are allowed.");
    return false;
  }

  mValue = mgr().new_technology(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
