
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "OutputVoltageHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstOutputVoltage.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief output_voltage group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_output_voltage(DotlibParser& parser)
{
  return new OutputVoltageHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス OutputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
OutputVoltageHandler::OutputVoltageHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  // simple attributes
  DotlibHandler* expr_handler = HandlerFactory::new_expr(parser);
  reg_handler(AttrType::vol,   expr_handler);
  reg_handler(AttrType::voh,   expr_handler);
  reg_handler(AttrType::vomin, expr_handler);
  reg_handler(AttrType::vomax, expr_handler);

  // complex attribute

  // group statements
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @brief 値を作る．
const AstNode*
OutputVoltageHandler::gen_node(const FileRegion& loc,
			       const AstString* name,
			       const vector<const AstAttr*>& attr_list)
{
  const AstExpr* vol = nullptr;
  const AstExpr* voh = nullptr;
  const AstExpr* vomin = nullptr;
  const AstExpr* vomax = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::vol ) {
      if ( vol != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vol' defined more than once.");
	return nullptr;
      }
      vol = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vol != nullptr );
    }
    else if ( attr->attr_type() == AttrType::voh ) {
      if ( voh != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'voh' defined more than once.");
	return nullptr;
      }
      voh = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( voh != nullptr );
    }
    else if ( attr->attr_type() == AttrType::vomin ) {
      if ( vomin != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vomin' defined more than once.");
	return nullptr;
      }
      vomin = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vomin != nullptr );
    }
    else if ( attr->attr_type() == AttrType::vomax ) {
      if ( vomax != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'vomax' defined more than once.");
	return nullptr;
      }
      vomax = dynamic_cast<const AstExpr*>(attr->attr_value());
      ASSERT_COND ( vomax != nullptr );
    }
  }
  return mgr().new_output_voltage(loc, name, vol, voh, vomin, vomax);
}

END_NAMESPACE_YM_DOTLIB
