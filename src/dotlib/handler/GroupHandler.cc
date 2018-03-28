
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

#if 0 // obsoleted, 参照のため残している．
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
#endif

// @brief 共通の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] value_list 値を表すトークンのリスト
// @param[out] value_loc 値全体のファイル上の位置
// @param[out] end_loc グループ末尾の '}' の位置
// @retval true パーズが成功した．
// @retval false パーズが失敗した．
bool
GroupHandler::parse_common(AttrType attr_type,
			   const FileRegion& attr_loc,
			   vector<const AstNode*>& value_list,
			   FileRegion& value_loc,
			   FileRegion& end_loc)
{
  if ( !parse_complex(false, value_loc, value_list) ) {
    return false;
  }

  if ( debug() ) {
    cout << attr_type << ": (";
    for ( auto value: value_list ) {
      cout << " " << value;
    }
    cout << ")" << " {" << endl;
  }

  if ( !expect(TokenType::LCB) ) {
    return false;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == TokenType::NL ) {
      continue;
    }
    if ( type == TokenType::RCB ) {
      end_loc = loc;
      break;
    }
    if ( type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    const char* name = parser().cur_string();
    AttrType name_type = parser().conv_to_attr(name);
    if ( name_type == AttrType::none ) {
      ostringstream buf;
      buf << name << ": syntax error.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      buf.str());
      return false;
    }
    bool r = parse_attr(name_type, loc);
    if ( !r ) {
      return false;
    }
  }

  if ( !expect(TokenType::NL) ) {
    return false;
  }

  if ( debug() ) {
    cout << "}" << endl;
  }

  return true;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
GroupHandler::parse_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  // ここでは常にエラーとなる．
  ostringstream buf;
  buf << attr_type << ": unexpected attribute.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  attr_loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  buf.str());
  return false;
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

// @brief 共通の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] end_loc グループ末尾の '}' の位置
// @retval true パーズが成功した．
// @retval false パーズが失敗した．
bool
EmptyGroupHandler::parse_common(AttrType attr_type,
				const FileRegion& attr_loc,
				FileRegion& end_loc)
{
  vector<const AstNode*> value_list;
  FileRegion value_loc;
  bool r = GroupHandler::parse_common(attr_type, attr_loc, value_list, value_loc, end_loc);
  if ( !r ) {
    return false;
  }

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

// @brief 共通の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] value 値を表すトークン
// @param[out] value_loc 値のファイル上の位置
// @param[out] end_loc グループ末尾の '}' の位置
// @retval true パーズが成功した．
// @retval false パーズが失敗した．
bool
Str1GroupHandler::parse_common(AttrType attr_type,
			       const FileRegion& attr_loc,
			       const AstString*& value,
			       FileRegion& value_loc,
			       FileRegion& end_loc)
{
  vector<const AstNode*> value_list;
  FileRegion value_loc;
  bool r = GroupHandler::parse_common(attr_type, attr_loc, value_list, value_loc, end_loc);
  if ( !r ) {
    return false;
  }

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
  if ( n > 1 ) {
    ostringstream buf;
    buf << attr_type << " statement has only one string parameter.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  value = dynamic_cast<const AstString*>(value_list[0]);
  if ( value == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(),
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

// @brief 共通の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] value1, value2 値を表すトークン
// @param[out] value_loc 値全体のファイル上の位置
// @param[out] end_loc グループ末尾の '}' の位置
// @retval true パーズが成功した．
// @retval false パーズが失敗した．
bool
Str2GroupHandler::parse_common(AttrType attr_type,
			       const FileRegion& attr_loc,
			       const AstString* value1,
			       const AstString* value2,
			       FileRegion& value_loc,
			       FileRegion& end_loc)
{
  vector<const AstNode*> value_list;
  FileRegion value_loc;
  bool r = GroupHandler::parse_common(attr_type, attr_loc, value_list, value_loc, end_loc);
  if ( !r ) {
    return false;
  }

  int n = value_list.size();
  if ( n < 2 ) {
    ostringstream buf;
    buf << attr_type << " statement requires a pair of string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  if ( n > 2 ) {
    ostringstream buf;
    buf << attr_type << " statement has only two string parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  value1 = dynamic_cast<const AstString*>(value_list[0]);
  if ( value1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  value2 = dynamic_cast<const AstString*>(value_list[1]);
  if ( value2 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[1]->loc(),
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

// @brief 共通の処理を行う．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] value1, value2, value3 値を表すトークン
// @param[out] value_loc 値全体のファイル上の位置
// @param[out] end_loc グループ末尾の '}' の位置
// @retval true パーズが成功した．
// @retval false パーズが失敗した．
bool
Str2IntGroupHandler::parse_common(AttrType attr_type,
				  const FileRegion& attr_loc,
				  const AstString* value1,
				  const AstString* value2,
				  const AstInt* value3,
				  FileRegion& value_loc,
				  FileRegion& end_loc)
{
  vector<const AstNode*> value_list;
  FileRegion value_loc;
  bool r = GroupHandler::parse_common(attr_type, attr_loc, value_list, value_loc, end_loc);
  if ( !r ) {
    return false;
  }

  int n = value_list.size();
  if ( n < 3 ) {
    ostringstream buf;
    buf << attr_type
	<< " statement requires a pair of strings and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  if ( n > 3 ) {
    ostringstream buf;
    buf << attr_type << " statement should have only a pair of strings and an integer parameters.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  value1 = dynamic_cast<const AstString*>(value_list[0]);
  if ( value1== nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  value2 = dynamic_cast<const AstString*>(value_list[1]);
  if ( value2 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[1]->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }

  value3 = dynamic_cast<const AstInt*>(value_list[2]);
  if ( value3 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[2]->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "integer value is expected.");
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
