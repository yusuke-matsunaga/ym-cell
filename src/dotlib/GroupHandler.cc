
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "GroupHandler.h"
#include "DotlibParserImpl.h"
#include "DotlibMgrImpl.h"
#include "DotlibNodeImpl.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親がない場合のコンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParserImpl& parser) :
  DotlibHandler(parser)
{
}

// @brief 親を持つハンドラ用のコンストラクタ
// @param[in] parent 親のハンドラ
GroupHandler::GroupHandler(GroupHandler* parent) :
  DotlibHandler(parent)
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
bool
GroupHandler::read_attr(AttrType attr_type,
			const FileRegion& attr_loc)
{
  FileRegion dummy_loc;
  DotlibNodeImpl* value = parse_complex(false, dummy_loc);
  if ( value == nullptr ) {
    return false;
  }

  if ( debug() ) {
    cout << attr_type << value << " {" << endl;
  }

  if ( !begin_group(attr_type, attr_loc, value) ) {
    return false;
  }

  if ( !expect(LCB) ) {
    return false;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == NL ) {
      continue;
    }
    if ( type == RCB ) {
      if ( !end_group(attr_type, attr_loc, loc) ) {
	return false;
      }
      break;
    }
    if ( type != SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
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
      return false;
    }
    if ( !handler->read_attr(name_type, loc) ) {
      return false;
    }
  }

  if ( !expect(NL) ) {
    return false;
  }

  if ( debug() ) {
    cout << "}" << endl;
  }

  return true;
}

// @brief attribute を設定する．
// @param[in] attr_type 属性
// @param[in] value 値
// @param[in] loc ファイル上の位置
// @return 設定が失敗したら false を返す．
// @note デフォルトの実装はエラーとなる．
bool
GroupHandler::add_attr(AttrType attr_type,
		       DotlibNodeImpl* value,
		       const FileRegion& loc)
{
  DotlibAttr* attr = mgr()->new_attr(attr_type, value, loc);
  mGroup->add_attr(attr);
  return true;
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

// @brief group statement の最初に呼ばれる関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
bool
GroupHandler::begin_group(AttrType attr_type,
			  const FileRegion& attr_loc,
			  DotlibNodeImpl* value_list)
{
  if ( !check_group_value(attr_type, attr_loc, value_list) ) {
    return false;
  }

  mGroup = mgr()->new_group(value_list, attr_loc);
  return true;
}

// @brief group statement の最後に呼ばれる関数
// @param[in] attr_type 属性
// @param[in] attr_loc attr_name のファイル上の位置
// @param[in] end_loc 閉じ括弧のファイル上の位置
bool
GroupHandler::end_group(AttrType attr_type,
			const FileRegion& attr_loc,
			const FileRegion& end_loc)
{
  FileRegion loc(attr_loc, end_loc);
  if ( attr_type == ATTR_LIBRARY ) {
    mgr()->set_root_node(mNode);
  }
  else {
    parent()->add_attr(attr_type, mGroup, loc);
  }
  mGroup = nullptr;
  return true;
}

// @brief 対応するノードを得る．
const DotlibGroup*
GroupHandler::node()
{
  return mGroup;
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
GroupHandler::check_group_value(AttrType attr_type,
				const FileRegion& attr_loc,
				DotlibNodeImpl* value)
{
  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス EmptyGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
EmptyGroupHandler::EmptyGroupHandler(GroupHandler* parent) :
  GroupHandler(parent)
{
}

// @brief デストラクタ
EmptyGroupHandler::~EmptyGroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
EmptyGroupHandler::check_group_value(AttrType attr_type,
				     const FileRegion& attr_loc,
				     DotlibNodeImpl* value_list)
{
  int n = value_list->list_size();
  if ( n > 0 ) {
    const DotlibNode* top = value_list->list_elem(0);
    FileRegion loc = top->loc();
    ostringstream buf;
    buf << attr_type << " statement does not have parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス Str1GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親を持たないハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str1GroupHandler::Str1GroupHandler(DotlibParserImpl& parser) :
  GroupHandler(parser)
{
}

// @brief 親を持つハンドラ用のコンストラクタ
// @param[in] parent 親のハンドラ
Str1GroupHandler::Str1GroupHandler(GroupHandler* parent) :
  GroupHandler(parent)
{
}

// @brief デストラクタ
Str1GroupHandler::~Str1GroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str1GroupHandler::check_group_value(AttrType attr_type,
				    const FileRegion& attr_loc,
				    DotlibNodeImpl* value_list)
{
  int n = value_list->list_size();
  if ( n == 0 ) {
    ostringstream buf;
    buf << attr_type << " statement requires a string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__, attr_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const DotlibNode* top = value_list->list_elem(0);
  if ( n > 1 ) {
    const DotlibNode* second = value_list->list_elem(1);
    FileRegion loc = second->loc();
    ostringstream buf;
    buf << attr_type << " statement has only one string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( !top->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス Str2GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parent 親のハンドラ
Str2GroupHandler::Str2GroupHandler(GroupHandler* parent) :
  GroupHandler(parent)
{
}

// @brief デストラクタ
Str2GroupHandler::~Str2GroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str2GroupHandler::check_group_value(AttrType attr_type,
				    const FileRegion& attr_loc,
				    DotlibNodeImpl* value_list)
{
  int n = value_list->list_size();
  if ( n < 2 ) {
    ostringstream buf;
    buf << attr_type << " statement requires two string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, attr_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const DotlibNode* top = value_list->list_elem(0);
  const DotlibNode* second = value_list->list_elem(1);
  if ( n > 2 ) {
    const DotlibNode* third = value_list->list_elem(2);
    FileRegion loc = third->loc();
    ostringstream buf;
    buf << attr_type << " statement has two string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( !top->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( !second->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス Str2IntGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parent 親のハンドラ
Str2IntGroupHandler::Str2IntGroupHandler(GroupHandler* parent) :
  GroupHandler(parent)
{
}

// @brief デストラクタ
Str2IntGroupHandler::~Str2IntGroupHandler()
{
}

// @brief group statement の引数のチェックを行う仮想関数
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str2IntGroupHandler::check_group_value(AttrType attr_type,
				       const FileRegion& attr_loc,
				       DotlibNodeImpl* value_list)
{
  int n = value_list->list_size();
  if ( n < 3 ) {
    ostringstream buf;
    buf << attr_type
	<< " statement requires two string and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, attr_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  const DotlibNode* top = value_list->list_elem(0);
  const DotlibNode* second = value_list->list_elem(1);
  const DotlibNode* third = value_list->list_elem(2);
  if ( n > 3 ) {
    const DotlibNode* forth = value_list->list_elem(3);
    FileRegion loc = forth->loc();
    ostringstream buf;
    buf << attr_type << " statement has two string and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__, loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  if ( !top->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( !second->is_string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( !third->is_int() ) {
    MsgMgr::put_msg(__FILE__, __LINE__, second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "integer value is expected.");
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
