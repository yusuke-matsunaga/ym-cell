﻿
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "GroupHandler.h"
#include "DotlibParserImpl.h"
#include "DotlibMgrImpl.h"
#include "DotlibList.h"
#include "DotlibInt.h"
#include "DotlibString.h"
#include "DotlibAttr.h"
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
  FileRegion dummy_loc;
  DotlibList* value_list = parse_complex(false, dummy_loc);
  if ( value_list == nullptr ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << value_list << " {" << endl;
  }

  if ( !check_group_value(attr_type, attr_loc, value_list) ) {
    return nullptr;
  }

  mAttrTop = nullptr;
  mAttrTail = nullptr;

  if ( !expect(LCB) ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == NL ) {
      continue;
    }
    if ( type == RCB ) {
      break;
    }
    if ( type != SYMBOL ) {
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
    if ( mAttrTop == nullptr ) {
      mAttrTop = attr;
    }
    else {
      mAttrTail->mNext = attr;
    }
    mAttrTail = attr;
  }

  if ( !expect(NL) ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << "}" << endl;
  }

  return gen_value(loc, value_list, mAttrTop);
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
// @param[in] value 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
GroupHandler::check_group_value(AttrType attr_type,
				const FileRegion& attr_loc,
				DotlibList* value_list)
{
  return true;
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
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
EmptyGroupHandler::check_group_value(AttrType attr_type,
				     const FileRegion& attr_loc,
				     DotlibList* value_list)
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
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str1GroupHandler::check_group_value(AttrType attr_type,
				    const FileRegion& attr_loc,
				    DotlibList* value_list)
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

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
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
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str2GroupHandler::check_group_value(AttrType attr_type,
				    const FileRegion& attr_loc,
				    DotlibList* value_list)
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

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibString*>(second) == nullptr ) {
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
// @param[in] value_list 値を表すトークンのリスト
// @note begin_group() の中で呼ばれる．
// @note デフォルトの実装はなにもしないで true を返す．
bool
Str2IntGroupHandler::check_group_value(AttrType attr_type,
				       const FileRegion& attr_loc,
				       DotlibList* value_list)
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

  if ( dynamic_cast<const DotlibString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibString*>(second) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  if ( dynamic_cast<const DotlibInt*>(third) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__, second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "integer value is expected.");
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB