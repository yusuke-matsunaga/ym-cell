
/// @file TemplateHandler.cc
/// @brief TemplateHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/TemplateHandler.h"
#include "dotlib/VarTypeHandler.h"
#include "dotlib/IndexHandler.h"
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
  // パース関数の登録
  reg_func(AttrType::variable_1,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_vartype(mVar1, attr_type, attr_loc); });
  reg_func(AttrType::variable_2,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_vartype(mVar2, attr_type, attr_loc); });
  reg_func(AttrType::variable_3,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_vartype(mVar3, attr_type, attr_loc); });
  reg_func(AttrType::index_1,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex1, attr_type, attr_loc); });
  reg_func(AttrType::index_2,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex2, attr_type, attr_loc); });
  reg_func(AttrType::index_3,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex3, attr_type, attr_loc); });
  reg_func(AttrType::domain,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_domain(mDomain, attr_type, attr_loc); });
}

// @brief デストラクタ
TemplateHandler::~TemplateHandler()
{
}

// @breif 'lut_template' Group Statement の記述をパースする．
// @param[in] dst_list 読み込んだ値を格納するリスト
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TemplateHandler::parse_value(vector<const AstTemplate*>& dst_list)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst_list.push_back(mValue);
  }
  return stat;
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
  mDomain = nullptr;

  mValue = nullptr;
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
			      mVar1, mVar2, mVar3, mIndex1, mIndex2, mIndex3, mDomain);

  return true;
}

END_NAMESPACE_YM_DOTLIB
