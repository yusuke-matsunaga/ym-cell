
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"

#include "InputVoltageHandler.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibExpr.h"
#include "dotlib/DotlibAttr.h"
#include "dotlib/DotlibInputVoltage.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief input_voltage group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_input_voltage(DotlibParser& parser)
{
  return new InputVoltageHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  // simple attributes
  DotlibHandler* expr_handler = HandlerFactory::new_expr(parser);
  reg_handler(ATTR_VIL,   expr_handler);
  reg_handler(ATTR_VIH,   expr_handler);
  reg_handler(ATTR_VIMIN, expr_handler);
  reg_handler(ATTR_VIMAX, expr_handler);

  // complex attribute

  // group statements
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief 値を作る．
DotlibNode*
InputVoltageHandler::gen_value(const FileRegion& loc,
			       const DotlibString* name,
			       const vector<DotlibAttr*>& attr_list)
{
  const DotlibExpr* vil = nullptr;
  const DotlibExpr* vih = nullptr;
  const DotlibExpr* vimin = nullptr;
  const DotlibExpr* vimax = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == ATTR_VIL ) {
      if ( vil != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vil' defined more than once.");
	return nullptr;
      }
      vil = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vil != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VIH ) {
      if ( vih != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vih' defined more than once.");
	return nullptr;
      }
      vih = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vih != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VIMIN ) {
      if ( vimin != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vimin' defined more than once.");
	return nullptr;
      }
      vimin = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vimin != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VIMAX ) {
      if ( vimax != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vimax' defined more than once.");
	return nullptr;
      }
      vimax = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vimax != nullptr );
    }
  }
  return mgr()->new_input_voltage(loc, name, vil, vih, vimin, vimax);
}

END_NAMESPACE_YM_DOTLIB
