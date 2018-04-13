
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
#include "dotlib/AstList.h"
#include "dotlib/AstAttr.h"
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
  Str1GroupHandler(parser)
{
  mIndexHandler = HandlerFactory::new_index(parser);
  mValuesHandler = HandlerFactory::new_values(parser);
  mGenGroupHandler = HandlerFactory::new_gen_group(parser);
}

// @brief デストラクタ
TableHandler::~TableHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
TableHandler::parse_attr_value(AttrType attr_type,
			       const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ AstLut を返す．
//
// エラーの場合には nullptr を返す．
const AstLut*
TableHandler::parse(AttrType attr_type,
		    const FileRegion& attr_loc)
{
  mIndex1 = nullptr;
  mIndex2 = nullptr;
  mIndex3 = nullptr;
  mValues = nullptr;

  const AstString* value;
  FileRegion value_loc;
  FileRegion end_loc;
  bool r = parse_common(attr_type, attr_loc, value, value_loc, end_loc);
  if ( !r ) {
    return nullptr;
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_lut(loc, value, mIndex1, mIndex2, mIndex3, mValues);
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
  case AttrType::index_1:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex1);

  case AttrType::index_2:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex2);

  case AttrType::index_3:
    return mIndexHandler->parse_and_assign(attr_type, attr_loc, mIndex3);

  case AttrType::values:
    return mValuesHandler->parse_and_assign(attr_type, attr_loc, mValues);

  case AttrType::domain:
    return mGenGroupHandler->parse(attr_type, attr_loc) != nullptr;
  }
  return false;
}

END_NAMESPACE_YM_DOTLIB
