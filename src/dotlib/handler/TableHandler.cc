
/// @file TableHandler.cc
/// @brief TableHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "TableHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstLut.h"
#include "dotlib/AstString.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstList.h"
#include "dotlib/AstAttr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief table group 用のハンドラを作る．
// @param[in] parser パーサー
TableHandler*
HandlerFactory::new_table(DotlibParser& parser)
{
  return new TableHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TableHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TableHandler::TableHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  DotlibHandler* index_handler = HandlerFactory::new_index(parser);
  DotlibHandler* values_handler = HandlerFactory::new_values(parser);
  DotlibHandler* dummy_handler = new GroupHandler(parser);

  // simple attributes

  // complex attribute
  reg_handler(AttrType::index_1, index_handler);
  reg_handler(AttrType::index_2, index_handler);
  reg_handler(AttrType::index_3, index_handler);
  reg_handler(AttrType::valueS,  values_handler);

  // group statements
  reg_handler(AttrType::domain,  dummy_handler);
}

// @brief デストラクタ
TableHandler::~TableHandler()
{
}

/// @brief 値を作る．
const AstNode*
TableHandler::gen_node(const FileRegion& loc,
		       const AstString* name,
		       const vector<const AstAttr*>& attr_list)
{
  const AstFloatVector* index_1 = nullptr;
  const AstFloatVector* index_2 = nullptr;
  const AstFloatVector* index_3 = nullptr;
  const AstFloatVector* values = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::index_1 ) {
      if ( index_1 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_1' defined more than once.");
	return nullptr;
      }
      index_1 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      if ( index_1 == nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error, vector type expected.");
	return nullptr;
      }
    }
    if ( attr->attr_type() == AttrType::index_2 ) {
      if ( index_2 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_2' defined more than once.");
	return nullptr;
      }
      index_2 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      if ( index_2 == nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error, vector type expected.");
	return nullptr;
      }
    }
    if ( attr->attr_type() == AttrType::index_3 ) {
      if ( index_3 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_3' defined more than once.");
	return nullptr;
      }
      index_3 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      if ( index_3 == nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error, vector type expected.");
	return nullptr;
      }
    }
    if ( attr->attr_type() == AttrType::valueS ) {
      if ( values != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'values' defined more than once.");
	return nullptr;
      }
      values = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      if ( values == nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error, list type expected.");
	return nullptr;
      }
    }
  }
  return mgr().new_lut(loc, name, index_1, index_2, index_3, values);
}

END_NAMESPACE_YM_DOTLIB
