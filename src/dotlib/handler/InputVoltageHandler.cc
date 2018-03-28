
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"

#include "InputVoltageHandler.h"
#include "AstMgr.h"
#include "AstExpr.h"
#include "AstAttr.h"
#include "AstInputVoltage.h"
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
  reg_handler(AttrType::vil,   expr_handler);
  reg_handler(AttrType::vih,   expr_handler);
  reg_handler(AttrType::vimin, expr_handler);
  reg_handler(AttrType::vimax, expr_handler);

  // complex attribute

  // group statements
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief 値を作る．
AstNode*
InputVoltageHandler::gen_node(const FileRegion& loc,
			      const AstString* name,
			      const vector<AstAttr*>& attr_list)
{
  const AstExpr* vil = nullptr;
  const AstExpr* vih = nullptr;
  const AstExpr* vimin = nullptr;
  const AstExpr* vimax = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::vil ) {
      if ( vil != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vil' defined more than once.");
	return nullptr;
      }
      vil = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vil != nullptr );
    }
    else if ( attr->attr_type() == AttrType::vih ) {
      if ( vih != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vih' defined more than once.");
	return nullptr;
      }
      vih = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vih != nullptr );
    }
    else if ( attr->attr_type() == AttrType::vimin ) {
      if ( vimin != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vimin' defined more than once.");
	return nullptr;
      }
      vimin = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vimin != nullptr );
    }
    else if ( attr->attr_type() == AttrType::vimax ) {
      if ( vimax != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vimax' defined more than once.");
	return nullptr;
      }
      vimax = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vimax != nullptr );
    }
  }
  return mgr().new_input_voltage(loc, name, vil, vih, vimin, vimax);
}

END_NAMESPACE_YM_DOTLIB
