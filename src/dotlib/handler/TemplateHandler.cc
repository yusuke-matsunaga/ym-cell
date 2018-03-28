
/// @file TemplateHandler.cc
/// @brief TemplateHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"
#include "TemplateHandler.h"
#include "AstMgr.h"
#include "AstFloatVector.h"
#include "AstVarType.h"
#include "AstAttr.h"
#include "AstTemplate.h"
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
  mVarTypeHandler = HandlerFactory::new_var_type(parser);
  mIndexHandler = HandlerFactory::new_index(parser);
  mGenGroupHandler = HandlerFactory::new_group(parser);
}

// @brief デストラクタ
TemplateHandler::~TemplateHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
TemplateHandler::parse_attr_value(AttrType attr_type,
				  const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

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
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_1'.");
    return nullptr;
  }
  if ( mIndex1 == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'mIndex1'.");
    return nullptr;
  }

  if ( mVar2 == nullptr ) {
    dimension = 1;
    if ( mVar3 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'variable_2'.");
      return nullptr;
    }
    if ( mIndex2 != nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
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
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_2' while missing 'index_2'.");
      return nullptr;
    }
    if ( mIndex3 != nullptr ) {
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
    if ( mIndex3 == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. having 'variable_3' while missing 'index_3'.");
      return nullptr;
    }
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_template(loc, value, dimension,
			    mVar1, mVar2, mVar3, mIndex1, mIndex2, mIndex3);
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
TemplateHandler::parse_attr(AttrType attr_type,
			    const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::variable_1:
    return mVarTypeHandler->parse_ans_assign(attr_type, attr_loc, mVar1);

  case AttrType::variable_2:
    return mVarTypeHandler->parse_ans_assign(attr_type, attr_loc, mVar2);

  case AttrType::variable_3:
    return mVarTypeHandler->parse_ans_assign(attr_type, attr_loc, mVar3);

  case AttrType::index_1:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex1);

  case AttrType::index_2:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex2);

  case AttrType::index_3:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex3);

  case AttrType::domain:
    return mGenGroupHandler->parse(attr_type, attr_loc) != nullptr;
  }
  return false;
}

END_NAMESPACE_YM_DOTLIB
