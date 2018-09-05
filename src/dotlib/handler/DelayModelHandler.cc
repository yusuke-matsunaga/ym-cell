
/// @file DelayModelHandler.cc
/// @brief DelayModelHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "DelayModelHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DelayModelHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DelayModelHandler::DelayModelHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
DelayModelHandler::~DelayModelHandler()
{
}

// @brief int 値の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstDelayModel*
DelayModelHandler::parse_value()
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
DelayModelHandler::read_str_value(const char* str,
				  const FileRegion& value_loc)
{
  ClibDelayModel value;
  if ( strcmp(str, "generic_cmos") == 0 ) {
    value = kClibDelayGenericCmos;
  }
  else if ( strcmp(str, "table_lookup") == 0 ) {
    value = kClibDelayTableLookup;
  }
  else if ( strcmp(str, "piecewise_cmos") == 0 ) {
    value = kClibDelayPiecewiseCmos;
  }
  else if ( strcmp(str, "cmos2") == 0 ) {
    value = kClibDelayCmos2;
  }
  else if ( strcmp(str, "dcm") == 0 ) {
    value = kClibDelayDcm;
  }
  else {
    mValue = nullptr;
    ostringstream buf;
    buf << str << ": Illegal value for 'delay_model'."
	<< " 'generic_cmos', 'table_lookup', "
	<< "'piecewise_cmos', 'cmos2' or 'dcm' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  mValue = mgr().new_delay_model(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
