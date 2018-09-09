
/// @file CPTypeHandler.cc
/// @brief CPTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/CPTypeHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス CPTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CPTypeHandler::CPTypeHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
CPTypeHandler::~CPTypeHandler()
{
}

// @brief clear_preset_var の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
CPTypeHandler::parse_value(const AstCPType*& dst)
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
CPTypeHandler::read_str_value(const char* str,
			      const FileRegion& value_loc)
{
  AstCPType::Type value;
  if ( strcmp(str, "L") == 0 ) {
    value = AstCPType::kL;
  }
  else if ( strcmp(str, "H") == 0 ) {
    value = AstCPType::kH;
  }
  else if ( strcmp(str, "N") == 0 ) {
    value = AstCPType::kN;
  }
  else if ( strcmp(str, "T") == 0 ) {
    value = AstCPType::kT;
  }
  else if ( strcmp(str, "X") == 0 ) {
    value = AstCPType::kX;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. only 'L', 'H', 'N', 'T', or 'X' are allowed.");
    return false;
  }

  mValue = mgr().new_cptype(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
