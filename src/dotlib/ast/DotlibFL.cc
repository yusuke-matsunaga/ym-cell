
/// @file DotlibFL.cc
/// @brief DotlibFL の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibFL.h"
//#include "DotlibAttr.h"
//#include "DotlibAttrMap.h"
//#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibFL
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
DotlibFL::DotlibFL(const FileRegion& loc,
		   const ShString var1,
		   const ShString var2,
		   const DotlibExpr* clear,
		   const DotlibExpr* preset,
		   int clear_preset_var1,
		   int clear_preset_var2) :
  DotlibNode(loc),
  mVar1(var1),
  mVar2(var2),
  mClear(clear),
  mPreset(preset),
  mClearPresetVar1(clear_preset_var1),
  mClearPresetVar2(clear_preset_var2)
{
}

// @brief デストラクタ
DotlibFL::~DotlibFL()
{
}

#if 0
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
#endif

END_NAMESPACE_YM_DOTLIB
