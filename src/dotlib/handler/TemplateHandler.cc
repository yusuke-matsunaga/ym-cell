
/// @file TemplateHandler.cc
/// @brief TemplateHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "TemplateHandler.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibFloatVector.h"
#include "dotlib/DotlibVarType.h"
#include "dotlib/DotlibAttr.h"
#include "dotlib/DotlibTemplate.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief template group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_template(DotlibParser& parser)
{
  return new TemplateHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TemplateHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TemplateHandler::TemplateHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  DotlibHandler* var_type = HandlerFactory::new_var_type(parser);
  DotlibHandler* index_handler = HandlerFactory::new_index(parser);
  DotlibHandler* g_group = HandlerFactory::new_group(parser);

  // simple attributes
  reg_handler(AttrType::VARIABLE_1, var_type);
  reg_handler(AttrType::VARIABLE_2, var_type);
  reg_handler(AttrType::VARIABLE_3, var_type);

  // complex attribute
  reg_handler(AttrType::INDEX_1,    index_handler);
  reg_handler(AttrType::INDEX_2,    index_handler);
  reg_handler(AttrType::INDEX_3,    index_handler);

  // group statements
  reg_handler(AttrType::DOMAIN,     g_group);
}

// @brief デストラクタ
TemplateHandler::~TemplateHandler()
{
}

// @brief 値を作る．
DotlibNode*
TemplateHandler::gen_value(const FileRegion& loc,
			   const DotlibString* name,
			   const vector<DotlibAttr*>& attr_list)
{
  const DotlibVarType* var_1 = nullptr;
  const DotlibVarType* var_2 = nullptr;
  const DotlibVarType* var_3 = nullptr;
  const DotlibFloatVector* index_1 = nullptr;
  const DotlibFloatVector* index_2 = nullptr;
  const DotlibFloatVector* index_3 = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::VARIABLE_1 ) {
      if ( var_1 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'variable_1' defined more than once.");
	return nullptr;
      }
      var_1 = dynamic_cast<const DotlibVarType*>(attr->attr_value());
      ASSERT_COND ( var_1 != nullptr );
    }
    else if ( attr->attr_type() == AttrType::VARIABLE_2 ) {
      if ( var_2 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'variable_2' defined more than once.");
	return nullptr;
      }
      var_2 = dynamic_cast<const DotlibVarType*>(attr->attr_value());
      ASSERT_COND ( var_2 != nullptr );
    }
    else if ( attr->attr_type() == AttrType::VARIABLE_3 ) {
      if ( var_3 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'variable_3' defined more than once.");
	return nullptr;
      }
      var_3 = dynamic_cast<const DotlibVarType*>(attr->attr_value());
      ASSERT_COND ( var_3 != nullptr );
    }
    else if ( attr->attr_type() == AttrType::INDEX_1 ) {
      if ( index_1 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_1' defined more than once.");
	return nullptr;
      }
      index_1 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND ( index_1 != nullptr );
    }
    else if ( attr->attr_type() == AttrType::INDEX_2 ) {
      if ( index_2 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_2' defined more than once.");
	return nullptr;
      }
      index_2 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND ( index_2 != nullptr );
    }
    else if ( attr->attr_type() == AttrType::INDEX_3 ) {
      if ( index_3 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"'index_3' defined more than once.");
	return nullptr;
      }
      index_3 = dynamic_cast<const DotlibFloatVector*>(attr->attr_value());
      ASSERT_COND ( index_3 != nullptr );
    }
  }

  int dimension = 0;
  if ( var_1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_1'.");
    return nullptr;
  }
  if ( index_1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'index_1'.");
    return nullptr;
  }

  if ( var_2 == nullptr ) {
    dimension = 1;
    if ( var_3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'variable_2'.");
      return nullptr;
    }
    if ( index_2 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'index_2' while missing 'variable_2'.");
      return nullptr;
    }
  }
  else if ( var_3 == nullptr ) {
    dimension = 2;
    if ( index_2 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_2' while missing 'index_2'.");
      return nullptr;
    }
    if ( index_3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'index_3' while missing 'variable_3'.");
      return nullptr;
    }
  }
  else {
    dimension = 3;
    if ( index_3 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'index_3'.");
      return nullptr;
    }
  }

  return mgr()->new_template(loc, name, dimension,
			     var_1, var_2, var_3, index_1, index_2, index_3);
}

END_NAMESPACE_YM_DOTLIB
