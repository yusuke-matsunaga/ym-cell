
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "GroupHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstList.h"
#include "AstInt.h"
#include "AstString.h"
#include "AstAttr.h"
#include "AstGenGroup.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親がない場合のコンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
GroupHandler::~GroupHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return エラーが起きたら false を返す．
const AstNode*
GroupHandler::parse_attr_value(AttrType attr_type,
			       const FileRegion& attr_loc)
{
  FileRegion value_loc;
  vector<const AstNode*> value_list;
  if ( !parse_complex(false, value_loc, value_list) ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << ": (";
    for ( auto value: value_list ) {
      cout << " " << value;
    }
    cout << ")" << " {" << endl;
  }

  if ( !check_value(attr_type, attr_loc, value_loc, value_list) ) {
    return nullptr;
  }

  if ( !expect(TokenType::LCB) ) {
    return nullptr;
  }

  begin_group();

  FileRegion first_loc = parser().cur_loc();
  FileRegion last_loc;
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == TokenType::NL ) {
      continue;
    }
    if ( type == TokenType::RCB ) {
      last_loc = loc;
      break;
    }
    if ( type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return nullptr;
    }
    const char* name = parser().cur_string();
    AttrType name_type = parser().conv_to_attr(name);
    int r = parse_attr(name_type, loc);
    if ( r == 0 ) {
      // 見つからなかった
      ostringstream buf;
      buf << name << ": unknown keyword.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      buf.str());
      return nullptr;
    }
    else if ( r == 1 ) {
      // 正常に処理した．
      continue;
    }
    else if ( r == 2 ) {
      // エラーが起こった．
      return nullptr;
    }
  }

  if ( !expect(TokenType::NL) ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << "}" << endl;
  }

  return gen_node(FileRegion(first_loc, last_loc), value_list, mAttrList);
}

// @brief ハンドラの登録を行う．
// @param[in] attr_type 属性
// @param[in] handler 対応付けるハンドラ
void
GroupHandler::reg_handler(AttrType attr_type,
			  DotlibHandler* handler)
{
  mHandlerList.push_back(make_pair(attr_type, handler));
}

// @brief ハンドラを取り出す．
// @param[in] attr_type 属性
// @note なければ nullptr を返す．
DotlibHandler*
GroupHandler::find_handler(AttrType attr_type)
{
  for ( auto p: mHandlerList ) {
    if ( p.first == attr_type ) {
      return p.second;
    }
  }
  return nullptr;
}

// @brief グループ開始の処理を行う．
void
GroupHandler::begin_group()
{
  mAttrList.clear();
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval 0 処理しなかった．
// @retval 1 正常に処理した．
// @retval 2 処理中にエラーが起こった．
int
GroupHandler::parse_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  // デフォルトの処理を行う．
  DotlibHandler* handler = find_handler(attr_type);
  if ( handler == nullptr ) {
    return 0;
  }
  const AstNode* value = handler->parse_attr_value(attr_type, attr_loc);
  if ( value == nullptr ) {
    return 2;
  }
  AstAttr* attr = mgr().new_attr(attr_loc, attr_type, value);
  mAttrList.push_back(attr);
  return 1;
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_loc 値全体のファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
GroupHandler::check_value(AttrType attr_type,
			  const FileRegion& attr_loc,
			  const FileRegion& value_loc,
			  const vector<const AstNode*>& value_list)
{
  return true;
}

// @brief 値を作る．
const AstNode*
GroupHandler::gen_node(const FileRegion& loc,
		       const vector<const AstNode*>& value_list,
		       const vector<const AstAttr*>& attr_list)
{
  return mgr().new_gen_group(loc, value_list, attr_list);
}


//////////////////////////////////////////////////////////////////////
// クラス EmptyGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
EmptyGroupHandler::EmptyGroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
EmptyGroupHandler::~EmptyGroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_loc 値全体のファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
bool
EmptyGroupHandler::check_value(AttrType attr_type,
			       const FileRegion& attr_loc,
			       const FileRegion& value_loc,
			       const vector<const AstNode*>& value_list)
{
  int n = value_list.size();
  if ( n > 0 ) {
    ostringstream buf;
    buf << attr_type << " statement does not have parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  return true;
}

// @brief 値を作る．
// @param[in] loc 全体のファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] attr_list 属性のリスト
const AstNode*
EmptyGroupHandler::gen_node(const FileRegion& loc,
			    const vector<const AstNode*>& value_list,
			    const vector<const AstAttr*>& attr_list)
{
  ASSERT_COND( value_list.empty() );
  return gen_node(loc, attr_list);
}

// @brief 値を作る．
// @param[in] loc 全体のファイル上の位置
// @param[in] attr_list 属性のリスト
const AstNode*
EmptyGroupHandler::gen_node(const FileRegion& loc,
			    const vector<const AstAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス Str1GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親を持たないハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str1GroupHandler::Str1GroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str1GroupHandler::~Str1GroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_loc 値全体のファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
bool
Str1GroupHandler::check_value(AttrType attr_type,
			      const FileRegion& attr_loc,
			      const FileRegion& value_loc,
			      const vector<const AstNode*>& value_list)
{
  int n = value_list.size();
  if ( n == 0 ) {
    ostringstream buf;
    buf << attr_type << " statement requires a string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const AstNode* top = value_list[0];
  if ( n > 1 ) {
    const AstNode* second = value_list[1];
    FileRegion loc = second->loc();
    ostringstream buf;
    buf << attr_type << " statement has only one string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( dynamic_cast<const AstString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  return true;
}

// @brief 値を作る．
const AstNode*
Str1GroupHandler::gen_node(const FileRegion& loc,
			   const vector<const AstNode*>& value_list,
			   const vector<const AstAttr*>& attr_list)
{
  // check_group_value() でチェックしているので value_list は
  // 文字列のシングルトンのはず．
  ASSERT_COND( value_list.size() == 1 );
  const AstString* str_value = dynamic_cast<const AstString*>(value_list[0]);
  return gen_node(loc, str_value, attr_list);
}

// @brief 値を作る．
const AstNode*
Str1GroupHandler::gen_node(const FileRegion& loc,
			   const AstString* value,
			   const vector<const AstAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス Str2GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2GroupHandler::Str2GroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2GroupHandler::~Str2GroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_loc 値全体のファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
bool
Str2GroupHandler::check_value(AttrType attr_type,
			      const FileRegion& attr_loc,
			      const FileRegion& value_loc,
			      const vector<const AstNode*>& value_list)
{
  int n = value_list.size();
  if ( n < 2 ) {
    ostringstream buf;
    buf << attr_type << " statement requires two string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const AstNode* top = value_list[0];
  const AstNode* second = value_list[1];
  if ( n > 2 ) {
    const AstNode* third = value_list[2];
    FileRegion loc = third->loc();
    ostringstream buf;
    buf << attr_type << " statement has two string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( dynamic_cast<const AstString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const AstString*>(second) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  return true;
}

// @brief 値を作る．
const AstNode*
Str2GroupHandler::gen_node(const FileRegion& loc,
			   const vector<const AstNode*>& value_list,
			   const vector<const AstAttr*>& attr_list)
{
  ASSERT_COND( value_list.size() == 2 );
  auto value1 = dynamic_cast<const AstString*>(value_list[0]);
  auto value2 = dynamic_cast<const AstString*>(value_list[1]);
  return gen_node(loc, value1, value2, attr_list);
}

// @brief 値を作る．
const AstNode*
Str2GroupHandler::gen_node(const FileRegion& loc,
			   const AstString* value1,
			   const AstString* value2,
			   const vector<const AstAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス Str2IntGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2IntGroupHandler::Str2IntGroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2IntGroupHandler::~Str2IntGroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_loc 値全体のファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str2IntGroupHandler::check_value(AttrType attr_type,
				 const FileRegion& attr_loc,
				 const FileRegion& value_loc,
				 const vector<const AstNode*>& value_list)
{
  int n = value_list.size();
  if ( n < 3 ) {
    ostringstream buf;
    buf << attr_type
	<< " statement requires two string and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const AstNode* top = value_list[0];
  const AstNode* second = value_list[1];
  const AstNode* third = value_list[2];
  if ( n > 3 ) {
    const AstNode* forth = value_list[4];
    FileRegion loc = forth->loc();
    ostringstream buf;
    buf << attr_type << " statement has two string and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( dynamic_cast<const AstString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const AstString*>(second) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const AstInt*>(third) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "integer value is expected.");
    return false;
  }

  return true;
}

// @brief 値を作る．
const AstNode*
Str2IntGroupHandler::gen_node(const FileRegion& loc,
			      const vector<const AstNode*>& value_list,
			      const vector<const AstAttr*>& attr_list)
{
  ASSERT_COND( value_list.size() == 3 );
  auto value1 = dynamic_cast<const AstString*>(value_list[0]);
  auto value2 = dynamic_cast<const AstString*>(value_list[1]);
  auto value3 = dynamic_cast<const AstInt*>(value_list[2]);
  return gen_node(loc, value1, value2, value3, attr_list);
}

// @brief 値を作る．
const AstNode*
Str2IntGroupHandler::gen_node(const FileRegion& loc,
			      const AstString* value1,
			      const AstString* value2,
			      const AstInt* value3,
			      const vector<const AstAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
