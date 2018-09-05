
/// @file TemplateHandler.cc
/// @brief TemplateHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "TemplateHandler.h"
#include "VarTypeHandler.h"
#include "IndexHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TemplateHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TemplateHandler::TemplateHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
TemplateHandler::~TemplateHandler()
{
}

// @breif lut_template group statement の記述をパースする．
// @return 読み込んだ値を返す．
const AstTemplate*
TemplateHandler::parse_value()
{
  bool stat = parse_group_statement();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief グループ記述の始まり
void
TemplateHandler::begin_group()
{
  mVar1 = nullptr;
  mVar2 = nullptr;
  mVar3 = nullptr;
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;

  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TemplateHandler::read_group_attr(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::variable_1: return parse_vartype(mVar1, attr_type, attr_loc);
  case AttrType::variable_2: return parse_vartype(mVar2, attr_type, attr_loc);
  case AttrType::variable_3: return parse_vartype(mVar3, attr_type, attr_loc);
  case AttrType::index_1:    return parse_index(mIndex1, attr_type, attr_loc);
  case AttrType::index_2:    return parse_index(mIndex2, attr_type, attr_loc);
  case AttrType::index_3:    return parse_index(mIndex3, attr_type, attr_loc);
  case AttrType::domain:
    {
      // 未完
    }
    //return mGenGroupHandler->parse(attr_type, attr_loc) != nullptr;
    return false;
  default:
    break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
}

// @brief VarType に共通の処理を行う．
bool
TemplateHandler::parse_vartype(const AstVarType*& dst,
			       AttrType attr_type,
			       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    ostringstream buf;
    buf << attr_type << " appear more than once.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
  }
  else {
    VarTypeHandler handler(parser());
    dst = handler.parse_value();
    if ( dst != nullptr ) {
      return true;
    }
  }
  return false;
}

// @brief Index に共通の処理を行う．
bool
TemplateHandler::parse_index(const AstFloatVector*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    ostringstream buf;
    buf << attr_type << " appear more than once.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
  }
  else {
    IndexHandler handler(parser());
    dst = handler.parse_value();
    if ( dst != nullptr ) {
      return true;
    }
  }
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TemplateHandler::end_group(const FileRegion& group_loc)
{
  int dimension = 0;
  if ( mVar1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_1'.");
    return false;
  }
  if ( mIndex1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'mIndex1'.");
    return false;
  }

  if ( mVar2 == nullptr ) {
    dimension = 1;
    if ( mVar3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      group_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'variable_2'.");
      return false;
    }
    if ( mIndex2 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      group_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'mIndex2' while missing 'variable_2'.");
      return false;
    }
  }
  else if ( mVar3 == nullptr ) {
    dimension = 2;
    if ( mIndex2 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      group_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_2' while missing 'index_2'.");
      return false;
    }
    if ( mIndex3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      group_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'index_3' while missing 'variable_3'.");
      return false;
    }
  }
  else {
    dimension = 3;
    if ( mIndex3 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      group_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'index_3'.");
      return false;
    }
  }

  mValue = mgr().new_template(group_loc, header_value(), dimension,
			      mVar1, mVar2, mVar3, mIndex1, mIndex2, mIndex3);

  return true;
}

#if 0
// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ AstTemplate を返す．
//
// エラーの場合には nullptr を返す．
const AstTemplate*
TemplateHandler::parse(AttrType attr_type,
		       const FileRegion& attr_loc)
{
  mVar1 = nullptr;
  mVar2 = nullptr;
  mVar3 = nullptr;
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;

  const AstString* value;
  FileRegion value_loc;
  FileRegion end_loc;
  bool r = parse_common(attr_type, attr_loc, value, value_loc, end_loc);
  if ( !r ) {
    return nullptr;
  }

  int dimension = 0;
  if ( mVar1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_1'.");
    return nullptr;
  }
  if ( mIndex1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'mIndex1'.");
    return nullptr;
  }

  if ( mVar2 == nullptr ) {
    dimension = 1;
    if ( mVar3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'variable_2'.");
      return nullptr;
    }
    if ( mIndex2 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'mIndex2' while missing 'variable_2'.");
      return nullptr;
    }
  }
  else if ( mVar3 == nullptr ) {
    dimension = 2;
    if ( mIndex2 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_2' while missing 'index_2'.");
      return nullptr;
    }
    if ( mIndex3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'index_3' while missing 'variable_3'.");
      return nullptr;
    }
  }
  else {
    dimension = 3;
    if ( mIndex3 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'index_3'.");
      return nullptr;
    }
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_template(loc, value, dimension,
			    mVar1, mVar2, mVar3, mIndex1, mIndex2, mIndex3);
}
#endif

END_NAMESPACE_YM_DOTLIB
