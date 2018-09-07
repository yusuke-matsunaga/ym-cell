
/// @file PowerHandler.cc
/// @brief PowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/PowerHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"



BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PowerHandler::PowerHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
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
  // 下の gen_node() のコードを参考にチェックを行い．
  // AstLut を作って mValue にセットする．
  return false;
}

#if 0
// @brief 値を作る．
const AstNode*
PowerHandler::gen_node(const FileRegion& loc,
		       const AstString* name,
		       const vector<const AstAttr*>& attr_list)
{
  const AstFloatVector* index_1 = nullptr;
  const AstFloatVector* index_2 = nullptr;
  const AstFloatVector* index_3 = nullptr;
  const AstFloatVector* values = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::index_1 ) {
      if ( index_1 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_1' defined more than once.");
	return nullptr;
      }
      index_1 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      ASSERT_COND( index_1 != nullptr );
    }
    if ( attr->attr_type() == AttrType::index_2 ) {
      if ( index_2 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_2' defined more than once.");
	return nullptr;
      }
      index_2 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      ASSERT_COND( index_2 != nullptr );
    }
    if ( attr->attr_type() == AttrType::index_3 ) {
      if ( index_3 != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'index_3' defined more than once.");
	return nullptr;
      }
      index_3 = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      ASSERT_COND ( index_3 != nullptr );
    }
    if ( attr->attr_type() == AttrType::valueS ) {
      if ( values != nullptr ) {
	// エラー
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr->attr_value()->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"'values' defined more than once.");
	return nullptr;
      }
      values = dynamic_cast<const AstFloatVector*>(attr->attr_value());
      ASSERT_COND ( values != nullptr );
    }
  }
  return mgr().new_lut(loc, name, index_1, index_2, index_3, values);
}
#endif

END_NAMESPACE_YM_DOTLIB
