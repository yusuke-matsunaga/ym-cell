
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "GroupHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibList.h"
#include "dotlib/DotlibInt.h"
#include "dotlib/DotlibString.h"
#include "dotlib/DotlibAttr.h"
#include "dotlib/DotlibGenGroup.h"
#include "dotlib/TokenType.h"
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
DotlibNode*
GroupHandler::read_attr(AttrType attr_type,
			const FileRegion& attr_loc)
{
  FileRegion value_loc;
  vector<DotlibNode*> value_list;
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

  FileRegion first_loc = parser().cur_loc();
  vector<DotlibAttr*> attr_list;
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
    DotlibHandler* handler = find_handler(name_type);
    if ( handler == nullptr ) {
      ostringstream buf;
      buf << name << ": unknown keyword.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      buf.str());
      return nullptr;
    }
    DotlibNode* value = handler->read_attr(name_type, loc);
    if ( value == nullptr ) {
      return nullptr;
    }
    DotlibAttr* attr = mgr()->new_attr(loc, name_type, value);
    attr_list.push_back(attr);
  }

  if ( !expect(TokenType::NL) ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << "}" << endl;
  }

  return gen_value(FileRegion(first_loc, last_loc), value_list, attr_list);
}

// @brief ハンドラの登録を行う．
// @param[in] attr_type 属性
// @param[in] handler 対応付けるハンドラ
// @note エラーが起きたら false を返す．
bool
GroupHandler::reg_handler(AttrType attr_type,
			  DotlibHandler* handler)
{
  mHandlerMap.add(attr_type, handler);
  return true;
}

// @brief ハンドラを取り出す．
// @param[in] attr_type 属性
// @note なければ nullptr を返す．
DotlibHandler*
GroupHandler::find_handler(AttrType attr_type)
{
  DotlibHandler* ans;
  if ( mHandlerMap.find(attr_type, ans) ) {
    return ans;
  }
  else {
    return nullptr;
  }
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
			  const vector<DotlibNode*>& value_list)
{
  return true;
}

// @brief 値を作る．
DotlibNode*
GroupHandler::gen_value(const FileRegion& loc,
			const vector<DotlibNode*>& value_list,
			const vector<DotlibAttr*>& attr_list)
{
  return mgr()->new_gen_group(loc, value_list, attr_list);
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
			       const vector<DotlibNode*>& value_list)
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
DotlibNode*
EmptyGroupHandler::gen_value(const FileRegion& loc,
			     const vector<DotlibNode*>& value_list,
			     const vector<DotlibAttr*>& attr_list)
{
  ASSERT_COND( value_list.empty() );
  return gen_value(loc, attr_list);
}

// @brief 値を作る．
// @param[in] loc 全体のファイル上の位置
// @param[in] attr_list 属性のリスト
DotlibNode*
EmptyGroupHandler::gen_value(const FileRegion& loc,
			     const vector<DotlibAttr*>& attr_list)
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
			      const vector<DotlibNode*>& value_list)
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

  const DotlibNode* top = value_list[0];
  if ( n > 1 ) {
    const DotlibNode* second = value_list[1];
    FileRegion loc = second->loc();
    ostringstream buf;
    buf << attr_type << " statement has only one string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  return true;
}

// @brief 値を作る．
DotlibNode*
Str1GroupHandler::gen_value(const FileRegion& loc,
			    const vector<DotlibNode*>& value_list,
			    const vector<DotlibAttr*>& attr_list)
{
  // check_group_value() でチェックしているので value_list は
  // 文字列のシングルトンのはず．
  ASSERT_COND( value_list.size() == 1 );
  const DotlibString* str_value = dynamic_cast<const DotlibString*>(value_list[0]);
  return gen_value(loc, str_value, attr_list);
}

// @brief 値を作る．
DotlibNode*
Str1GroupHandler::gen_value(const FileRegion& loc,
			    const DotlibString* value,
			    const vector<DotlibAttr*>& attr_list)
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
			      const vector<DotlibNode*>& value_list)
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

  const DotlibNode* top = value_list[0];
  const DotlibNode* second = value_list[1];
  if ( n > 2 ) {
    const DotlibNode* third = value_list[2];
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

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibString*>(second) == nullptr ) {
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
DotlibNode*
Str2GroupHandler::gen_value(const FileRegion& loc,
			    const vector<DotlibNode*>& value_list,
			    const vector<DotlibAttr*>& attr_list)
{
  ASSERT_COND( value_list.size() == 2 );
  auto value1 = dynamic_cast<const DotlibString*>(value_list[0]);
  auto value2 = dynamic_cast<const DotlibString*>(value_list[1]);
  return gen_value(loc, value1, value2, attr_list);
}

// @brief 値を作る．
DotlibNode*
Str2GroupHandler::gen_value(const FileRegion& loc,
			    const DotlibString* value1,
			    const DotlibString* value2,
			    const vector<DotlibAttr*>& attr_list)
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
				 const vector<DotlibNode*>& value_list)
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

  const DotlibNode* top = value_list[0];
  const DotlibNode* second = value_list[1];
  const DotlibNode* third = value_list[2];
  if ( n > 3 ) {
    const DotlibNode* forth = value_list[4];
    FileRegion loc = forth->loc();
    ostringstream buf;
    buf << attr_type << " statement has two string and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibString*>(second) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibInt*>(third) == nullptr ) {
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
DotlibNode*
Str2IntGroupHandler::gen_value(const FileRegion& loc,
			       const vector<DotlibNode*>& value_list,
			       const vector<DotlibAttr*>& attr_list)
{
  ASSERT_COND( value_list.size() == 3 );
  auto value1 = dynamic_cast<const DotlibString*>(value_list[0]);
  auto value2 = dynamic_cast<const DotlibString*>(value_list[1]);
  auto value3 = dynamic_cast<const DotlibInt*>(value_list[2]);
  return gen_value(loc, value1, value2, value3, attr_list);
}

// @brief 値を作る．
DotlibNode*
Str2IntGroupHandler::gen_value(const FileRegion& loc,
			       const DotlibString* value1,
			       const DotlibString* value2,
			       const DotlibInt* value3,
			       const vector<DotlibAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
