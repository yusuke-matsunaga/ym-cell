
/// @file TableHandler.cc
/// @brief TableHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/TableHandler.h"
#include "dotlib/IndexHandler.h"
#include "dotlib/ValuesHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TableHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TableHandler::TableHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
TableHandler::~TableHandler()
{
}

// @breif look-up table Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TableHandler::parse_value(const AstLut*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
TableHandler::begin_group()
{
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;
  mValues = nullptr;

  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
TableHandler::read_group_attr(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::index_1: return parse_index(mIndex1,  attr_type, attr_loc);
  case AttrType::index_2: return parse_index(mIndex2,  attr_type, attr_loc);
  case AttrType::index_3: return parse_index(mIndex3,  attr_type, attr_loc);
  case AttrType::values:  return parse_values(mValues, attr_type, attr_loc);
  case AttrType::domain:  return parse_domain(mDomain, attr_type, attr_loc);
  default:
    break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TableHandler::end_group(const FileRegion& group_loc)
{
  if ( mValues == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "values is missing.");
    return false;
  }
  else {
    mValue = mgr().new_lut(group_loc, header_value(),
			   mIndex1, mIndex2, mIndex3, mValues, mDomain);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB