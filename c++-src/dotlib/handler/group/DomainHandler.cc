
/// @file DomainHandler.cc
/// @brief DomainHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DomainHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DomainHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DomainHandler::DomainHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::calc_mode,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::coefs,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_float_vector(mCoefs, attr_type, attr_loc); });
  reg_func(AttrType::orders,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_int_vector(mOrders, attr_type, attr_loc); });
  reg_func(AttrType::variable_1_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_float_float(mVar1Range, attr_type, attr_loc); });
  reg_func(AttrType::variable_2_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_float_float(mVar2Range, attr_type, attr_loc); });
  reg_func(AttrType::variable_3_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> const AstSimple*
	   { return parser.parse_float_float(mVar3Range, attr_type, attr_loc); });
}

// @brief デストラクタ
DomainHandler::~DomainHandler()
{
}

#if 0
// @breif 'domain' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
DomainHandler::parse_value(const AstDomain*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}
#endif

// @brief グループ記述の始まり
void
DomainHandler::begin_group()
{
  mStrList.clear();

  mCoefs = nullptr;
  mOrders = nullptr;
  mVar1Range = nullptr;
  mVar2Range = nullptr;
  mVar3Range = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DomainHandler::end_group()
{
#if 0
  if ( mCalcMode == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'calc_mode' is missing.");
    return false;
  }
  else
#endif
  if ( mCoefs == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'coefs' is missing.");
    return false;
  }
  else if ( mOrders == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'orders' is missing.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
