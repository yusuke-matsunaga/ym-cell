
/// @file PowerHandler.cc
/// @brief PowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/PowerHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"

#error "Don't compile me"

BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PowerHandler::PowerHandler(Parser& parser) :
  Str1GroupHandler(parser)
{
  // パース関数の登録
  reg_func("index_1,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex1, attr_type, attr_loc); });
  reg_func("index_2,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex2, attr_type, attr_loc); });
  reg_func("index_3,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_index(mIndex3, attr_type, attr_loc); });
  reg_func("values,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_values(mValues, attr_type, attr_loc); });
  reg_func("coefs,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_str1complex(mCoefs, attr_type, attr_loc); });
  reg_func("orders,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_str1complex(mOrders, attr_type, attr_loc); });
  reg_func("domain,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_domain(mDomain, attr_type, attr_loc); });
}

// @brief デストラクタ
PowerHandler::~PowerHandler()
{
}

// @breif 'power' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PowerHandler::parse_value(const AstLut*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
PowerHandler::begin_group()
{
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;
  mValues = nullptr;
  mCoefs = nullptr;
  mOrders = nullptr;
  mDomain = nullptr;

  mValue = nullptr;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
PowerHandler::end_group(const FileRegion& group_loc)
{
  if ( mValues == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'values' is missing.");
    return false;
  }
  else {
    mValue = mgr().new_lut(group_loc, header_value(), mIndex1, mIndex2, mIndex3, mValues,
			   mCoefs, mOrders,
			   mDomain);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
