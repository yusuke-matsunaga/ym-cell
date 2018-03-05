
/// @file DefineHandler.cc
/// @brief DefineHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DefineHandler.h"
#include "DotlibParserImpl.h"
#include "SimpleHandler.h"
#include "GroupHandler.h"
#include "DotlibNodeImpl.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DefineHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
DefineHandler::DefineHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
DefineHandler::~DefineHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return エラーが起きたら false を返す．
bool
DefineHandler::read_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  FileRegion dummy_loc;
  const DotlibNode* value = parse_complex(false, dummy_loc);
  if ( value == nullptr ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  if ( debug() ) {
    cout << attr_type << " : " << value << endl;
  }

  const DotlibNode* keyword = value->list_elem(0);
  if ( keyword == nullptr || !keyword->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    keyword->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 1st argument.");
    return false;
  }

  const DotlibNode* group = value->list_elem(1);
  if ( group == nullptr || !group->is_attr() ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 2nd argument.");
    return false;
  }

  const DotlibNode* type_token = value->list_elem(2);
  if ( type_token == nullptr || !type_token->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    type_token->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 3rd argument.");
    return false;
  }

  DotlibHandler* handler = parent()->find_handler(group->attr_type());
  if ( handler == nullptr ) {
    ostringstream buf;
    buf << group->string_value() << ": Unknown attribute. ignored.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgWarning,
		    "DOTLIB_PARSER",
		    buf.str());
    return true;
  }

  GroupHandler* g_handler = dynamic_cast<GroupHandler*>(handler);
  if ( g_handler == nullptr ) {
    ostringstream buf;
    buf << group->string_value() << ": is not a group statement.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgWarning,
		    "DOTLIB_PARSER",
		    buf.str());
    return true;
  }

  DotlibHandler* new_handler = nullptr;
  const char* type_str = type_token->string_value();
  if ( strcmp(type_str, "int") == 0 ) {
    new_handler = new IntSimpleHandler(g_handler);
  }
  else if ( strcmp(type_str, "float") == 0 ) {
    new_handler = new FloatSimpleHandler(g_handler);
  }
  else if ( strcmp(type_str, "string") == 0 ) {
    new_handler = new StrSimpleHandler(g_handler, false);
  }
  else {
    ostringstream buf;
    buf << "Unknown type: " << type_str << ".";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    type_token->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  AttrType key_attr; // = keyword->string_value();
  g_handler->reg_handler(key_attr, new_handler);

  return true;
}

END_NAMESPACE_YM_DOTLIB
