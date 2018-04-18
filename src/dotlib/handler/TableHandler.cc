
/// @file TableHandler.cc
/// @brief TableHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "TableHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstLut.h"
#include "dotlib/AstString.h"
#include "dotlib/AstFloatVector.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief table group 用のハンドラを作る．
// @param[in] parser パーサー
TableHandler*
HandlerFactory::new_table(DotlibParser& parser)
{
  return new TableHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TableHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TableHandler::TableHandler(DotlibParser& parser) :
  Str1GroupHandler(parser),
  mIndex1(parser),
  mIndex2(parser),
  mIndex3(parser),
  mValues(parser)
{
}

// @brief デストラクタ
TableHandler::~TableHandler()
{
}

// @brief 値をクリアする．
void
TableHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstLut*
TableHandler::value() const
{
  return mValue;
}

// @brief グループ記述の始まり
void
TableHandler::begin_group()
{
  mIndex1.clear_value();
  mIndex2.clear_value();
  mIndex3.clear_value();
  mValues.clear_value();
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
TableHandler::parse_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
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
