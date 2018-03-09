
/// @file DotlibFL.cc
/// @brief DotlibFL の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFL.h"
#include "DotlibAttr.h"
#include "DotlibAttrMap.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibFL
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
DotlibFL(const FileRegion& loc) :
  DotlibBase(loc)
{
}

// @brief デストラクタ
DotlibFL::~DotlibFL()
{
}

// @brief データを持っている時に true を返す．
bool
DotlibFL::has_data() const
{
  return mHasData;
}

// @brief set_data() の下請け関数
bool
DotlibFL::set_data_sub(const DotlibNode* node,
		       const DotlibAttrMap& attr_map)
{
  mClear = nullptr;
  mPreset = nullptr;

  mClearPresetVar1 = 0;
  mClearPresetVar2 = 0;

  // 状態変数名を得る．
  if ( !node->group_value()->expect_string_pair(mVar1, mVar2) ) {
    return false;
  }

  // clear を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CLEAR, mClear) ) {
    return false;
  }

  // preset を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_PRESET, mPreset) ) {
    return false;
  }

  // clear_preset_var1 を取り出す．
  const DotlibNode* tmp_node1 = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_CLEAR_PRESET_VAR1, tmp_node1) ) {
    return false;
  }
  if ( tmp_node1 ) {
    if ( !tmp_node1->is_string() ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      tmp_node1->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "String value is expected.");
      return false;
    }
    const char* str = tmp_node1->string_value();
    if ( strcmp(str, "L") == 0 || strcmp(str, "l") == 0 ) {
      mClearPresetVar1 = 0;
    }
    else if ( strcmp(str, "H") == 0 || strcmp(str, "h") == 0 ) {
      mClearPresetVar1 = 1;
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      tmp_node1->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. \"L\" or \"H\" is expected.");
      return false;
    }
  }

  // clear_preset_var2 を取り出す．
  const DotlibNode* tmp_node2 = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_CLEAR_PRESET_VAR2, tmp_node2) ) {
    return false;
  }
  if ( tmp_node2 ) {
    if ( !tmp_node2->is_string() ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      tmp_node2->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "String value is expected.");
      return false;
    }
    const char* str = tmp_node2->string_value();
    if ( strcmp(str, "L") == 0 || strcmp(str, "l") == 0 ) {
      mClearPresetVar2 = 0;
    }
    else if ( strcmp(str, "H") == 0 || strcmp(str, "h") == 0 ) {
      mClearPresetVar2 = 1;
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      tmp_node2->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. \"L\" or \"H\" is expected.");
      return false;
    }
  }
  mHasData = true;

  return true;
}

// @brief var1 の名前を返す．
ShString
DotlibFL::var1_name() const
{
  return mVar1;
}

// @brief var2 の名前を返す．
ShString
DotlibFL::var2_name() const
{
  return mVar2;
}

// @brief "clear" を返す．
const DotlibNode*
DotlibFL::clear() const
{
  return mClear;
}

// @brief "preset" を返す．
const DotlibNode*
DotlibFL::preset() const
{
  return mPreset;
}

// @brief "clear_preset_var1" を返す．
int
DotlibFL::clear_preset_var1() const
{
  return mClearPresetVar1;
}

// @brief "clear_preset_var2" を返す．
int
DotlibFL::clear_preset_var2() const
{
  return mClearPresetVar2;
}

END_NAMESPACE_YM_DOTLIB
