
/// @file DomainHandler.cc
/// @brief DomainHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DomainHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DomainHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DomainHandler::DomainHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
DomainHandler::~DomainHandler()
{
}

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

// @brief グループ記述の始まり
void
DomainHandler::begin_group()
{
}

#if 0
// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
DomainHandler::read_group_attr(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  case AttrType::calc_mode:        return parse_string(mCalcMode, attr_type, attr_loc);
  case AttrType::coefs:            return parse_str1complex(mCoefs, attr_type, attr_loc);
  case AttrType::orders:           return parse_str1complex(mOrders, attr_type, attr_loc);
  case AttrType::variable_1_range: return parse_vrange(mVar1Range, attr_type, attr_loc);
  case AttrType::variable_2_range: return parse_vrange(mVar2Range, attr_type, attr_loc);
  case AttrType::variable_3_range: return parse_vrange(mVar3Range, attr_type, attr_loc);

  default:
    break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
}
#endif

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DomainHandler::end_group(const FileRegion& group_loc)
{
  if ( mCoefs == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'coefs' is missing.");
    return false;
  }
  else if ( mOrders == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    group_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'orders' is missing.");
    return false;
  }
  else {
    mValue = mgr().new_domain(group_loc, header_value(),
			      mCalcMode, mCoefs, mOrders,
			      mVar1Range, mVar2Range, mVar3Range);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
