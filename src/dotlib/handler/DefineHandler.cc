
/// @file DefineHandler.cc
/// @brief DefineHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DefineHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstList.h"
#include "dotlib/AstString.h"
#include "SimpleHandler.h"
#include "GroupHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DefineHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] parent 親のハンドラ
DefineHandler::DefineHandler(DotlibParser& parser,
			     GroupHandler* parent) :
  ComplexHandler(parser)
{
}

// @brief デストラクタ
DefineHandler::~DefineHandler()
{
}

// @brief 構文要素を処理する．
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら nullptr を返す．
bool
DefineHandler::parse_attr_value()
{
#if 0
  FileRegion value_loc;
  vector<const AstNode*> value_list;
  if ( !parse_complex(false, value_loc, value_list) ) {
    return nullptr;
  }

  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << " : (";
    for ( auto value: value_list ) {
      cout << " " << value;
    }
    cout << ")" << endl;
  }

  ASSERT_COND( value_list.size() == 3 );

  const AstString* keyword = dynamic_cast<const AstString*>(value_list[0]);
  if ( keyword == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    keyword->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected for 1st argument.");
    return nullptr;
  }

  const AstString* group = dynamic_cast<const AstString*>(value_list[1]);
  if ( group == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected for 2nd argument.");
    return nullptr;
  }

  const AstString* type_token = dynamic_cast<const AstString*>(value_list[2]);
  if ( type_token == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    type_token->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected for 3rd argument.");
    return nullptr;
  }

#if 0
  AttrType group_attr = parser().conv_to_attr(group->value());
  DotlibHandler* handler = mParent->find_handler(group_attr);
  if ( handler == nullptr ) {
    ostringstream buf;
    buf << group->value() << ": Unknown attribute. ignored.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group->loc(),
		    MsgType::Warning,
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
		    MsgType::Warning,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  DotlibHandler* new_handler = nullptr;
  const char* type_str = type_token->value();
  if ( strcmp(type_str, "int") == 0 ) {
    new_handler = new IntSimpleHandler(parser());
  }
  else if ( strcmp(type_str, "float") == 0 ) {
    new_handler = new FloatSimpleHandler(parser());
  }
  else if ( strcmp(type_str, "string") == 0 ) {
    new_handler = new StrSimpleHandler(parser(), false);
  }
  else {
    ostringstream buf;
    buf << "Unknown type: " << type_str << ".";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    type_token->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

#warning "TODO"
  // keyword->string_value() を新規の属性名として定義する．
  AttrType key_attr = parser().conv_to_attr(keyword->value());
  g_handler->reg_handler(key_attr, new_handler);
#endif
#warning "TODO: 未完"

  return nullptr;
#endif
  return false;
}

END_NAMESPACE_YM_DOTLIB
