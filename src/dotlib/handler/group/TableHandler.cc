
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

// @breif timing group statement の記述をパースする．
// @return 読み込んだ値を返す．
const AstLut*
TableHandler::parse_value()
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
#if 0
  switch ( attr_type ) {
  case AttrType::index_1: return mIndex1.parse_attr_value();
  case AttrType::index_2: return mIndex2.parse_attr_value();
  case AttrType::index_3: return mIndex3.parse_attr_value();
  case AttrType::values:  return mValues.parse_attr_value();
  case AttrType::domain:
#warning "TODO: 未完";
    break;
  default:
    break;
  }
  syntax_error(attr_type, attr_loc);
  return false;
#endif
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TableHandler::end_group(const FileRegion& group_loc)
{
#warning "TODO: 未完"
  // mIndex1, mIndex2, mIndex3, mValues に値がセットされていることを確認して
  // AstLut を作る．
  return false;
}

END_NAMESPACE_YM_DOTLIB
