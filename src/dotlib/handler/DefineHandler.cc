﻿
/// @file DefineHandler.cc
/// @brief DefineHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DefineHandler.h"
#include "DotlibParserImpl.h"
#include "DotlibList.h"
#include "DotlibString.h"
#include "SimpleHandler.h"
#include "GroupHandler.h"
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
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら nullptr を返す．
DotlibNode*
DefineHandler::read_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  FileRegion dummy_loc;
  const DotlibList* value_list = parse_complex(false, dummy_loc);
  if ( value_list == nullptr ) {
    return nullptr;
  }

  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << " : " << value_list << endl;
  }

  const DotlibString* keyword = dynamic_cast<const DotlibString*>(value_list->list_elem(0));
  if ( keyword == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    keyword->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 1st argument.");
    return nullptr;
  }

  const DotlibString* group = dynamic_cast<const DotlibString*>(value_list->list_elem(1));
  if ( group == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 2nd argument.");
    return nullptr;
  }

  const DotlibString* type_token = dynamic_cast<const DotlibString*>(value_list->list_elem(2));
  if ( type_token == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    type_token->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected for 3rd argument.");
    return nullptr;
  }

  AttrType group_attr = parser().conv_to_attr(group->value());
  DotlibHandler* handler = parent()->find_handler(group_attr);
  if ( handler == nullptr ) {
    ostringstream buf;
    buf << group->value() << ": Unknown attribute. ignored.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgWarning,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  GroupHandler* g_handler = dynamic_cast<GroupHandler*>(handler);
  if ( g_handler == nullptr ) {
    ostringstream buf;
    buf << group->value() << ": is not a group statement.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    kMsgWarning,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  DotlibHandler* new_handler = nullptr;
  const char* type_str = type_token->value();
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
    return nullptr;
  }

#warning "TODO"
  // keyword->string_value() を新規の属性名として定義する．
  AttrType key_attr = parser().conv_to_attr(keyword->value());
  g_handler->reg_handler(key_attr, new_handler);

  return nullptr;
}

END_NAMESPACE_YM_DOTLIB