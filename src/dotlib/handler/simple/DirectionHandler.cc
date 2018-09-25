
/// @file DirectionHandler.cc
/// @brief DirectionHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DirectionHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DirectionHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DirectionHandler::DirectionHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
DirectionHandler::~DirectionHandler()
{
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
DirectionHandler::read_str_value(const char* str,
				 const FileRegion& value_loc)
{
  ClibDirection value;
  if ( strcmp(str, "input") == 0 ) {
    value = ClibDirection::Input;
  }
  else if ( strcmp(str, "output") == 0 ) {
    value = ClibDirection::Output;
  }
  else if ( strcmp(str, "inout") == 0 ) {
    value = ClibDirection::Inout;
  }
  else if ( strcmp(str, "internal") == 0 ) {
    value = ClibDirection::Internal;
  }
  else {
    mValue = nullptr;
    ostringstream buf;
    buf << str << ": Illegal value for 'direction'."
	<< " 'input', 'output', 'inout' or 'internal' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  mValue = mgr().new_direction(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
