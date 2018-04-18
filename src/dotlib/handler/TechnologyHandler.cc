
/// @file TechnologyHandler.cc
/// @brief TechnologyHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "TechnologyHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstTechnology.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TechnologyHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TechnologyHandler::TechnologyHandler(DotlibParser& parser) :
  StrBaseHandler(parser, false)
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

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TechnologyHandler::read_str_value(const char* str,
				  const FileRegion& value_loc)
{
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
