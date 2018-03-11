
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"

#include "OutputVoltageHandler.h"
#include "ExprHandler.h"


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
  DotlibHandler* expr_handler = new ExprHandler(handler);
  reg_handler(ATTR_VOL,   expr_handler);
  reg_handler(ATTR_VOH,   expr_handler);
  reg_handler(ATTR_VOMIN, expr_handler);
  reg_handler(ATTR_VOMAX, expr_handler);

  // complex attribute

  // group statements
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @brief 値を作る．
DotlibNode*
OutputVoltageHandler::gen_value(const DotlibList* value_list,
				const DotlibAttr* attr_top)
{
  const DotlibString* name = value_list->get_string_from_value_list();
  const DotlibExpr* vol = nullptr;
  const DotlibExpr* voh = nullptr;
  const DotlibExpr* vomin = nullptr;
  const DotlibExpr* vomax = nullptr;
  for ( auto attr = attr_top; attr != nullptr; attr = attr->next() ) {
    if ( attr->attr_type() == ATTR_VOL ) {
      if ( vol != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vol' defined more than once.");
	return nullptr;
      }
      vol = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vol != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VOH ) {
      if ( voh != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'voh' defined more than once.");
	return nullptr;
      }
      voh = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( voh != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VOMIN ) {
      if ( vomin != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vomin' defined more than once.");
	return nullptr;
      }
      vomin = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vomin != nullptr );
    }
    else if ( attr->attr_type() == ATTR_VOMAX ) {
      if ( vomax != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'vomax' defined more than once.");
	return nullptr;
      }
      vomax = dynamic_cast<const DotlibExpr*>(attr->attr_value());
      ASSERT_COND ( vomax != nullptr );
    }
  }
  return mgr()->new_output_voltage(loc, name, vol, voh, vomin, vomax);
}

END_NAMESPACE_YM_DOTLIB
