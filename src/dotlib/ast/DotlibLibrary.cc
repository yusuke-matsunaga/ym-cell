
/// @file DotlibLibrary.cc
/// @brief DotlibLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibLibrary.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
DotlibLibrary::DotlibLibrary(const FileRegion& loc) :
  DotlibNode(loc)
{
}

// @brief デストラクタ
DotlibLibrary::~DotlibLibrary()
{
}

#if 0
// @brief 内容を初期化する．
bool
DotlibLibrary::set_data(const DotlibNode* node)
{
  mTechnology = kClibTechCmos;
  mDelayModel = kClibDelayGenericCmos;
  mBusNamingStyle = nullptr;
  mComment = nullptr;
  mDate = nullptr;
  mRevision = nullptr;
  mCapacitiveLoadUnit = 0.0;
  mCurrentUnit = nullptr;
  mLeakagePowerUnit = nullptr;
  mPullingResistanceUnit = nullptr;
  mTimeUnit = nullptr;
  mVoltageUnit = nullptr;

  mLutTemplateList.clear();
  mCellList.clear();

  // ライブラリ名をを得る．
  mName = node->group_value()->get_string_from_value_list();

  // 属性のリストを作る．
  DotlibAttrMap attr_map(node->attr_top());

  // 'technology' を取り出す．
  const DotlibNode* tech_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_TECHNOLOGY, tech_node) ) {
    return false;
  }
  if ( tech_node ) {
    const char* str = tech_node->get_string_from_value_list();
    if ( strcmp(str, "cmos") == 0 ) {
      mTechnology = kClibTechCmos;
    }
    else if ( strcmp(str, "fpga") == 0 ) {
      mTechnology = kClibTechFpga;
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      tech_node->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. only 'asic' or 'fpga' are allowed.");
      return false;
    }
  }

  // 'delay_model' を取り出す．
  const DotlibNode* dm_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_DELAY_MODEL, dm_node) ) {
    return false;
  }
  ASSERT_COND( dm_node->type() == DotlibNode::kDelayModel );
  mDelayModel = dm_node->delay_model();

  // 'bus_naming_style' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_BUS_NAMING_STYLE, mBusNamingStyle) ) {
    return false;
  }

  // 'comment' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_COMMENT, mComment) ) {
    return false;
  }

  // 'date' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_DATE, mDate) ) {
    return false;
  }

  // 'revision' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_REVISION, mRevision) ) {
    return false;
  }

  // 'current_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CURRENT_UNIT, mCurrentUnit) ) {
    return false;
  }

  // 'leakage_power_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_LEAKAGE_POWER_UNIT, mLeakagePowerUnit) ) {
    return false;
  }

  // 'pulling_resistance_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_PULLING_RESISTANCE_UNIT,
				 mPullingResistanceUnit) ) {
    return false;
  }

  // 'capacitive_load_unit' を取り出す．
  const DotlibNode* clu = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_CAPACITIVE_LOAD_UNIT, clu) ) {
    return false;
  }
  if ( clu ) {
    // clu は ComplexHandler で読んでいるからリストのはず．
    ASSERT_COND( clu->is_list() );
    if ( clu->list_size() != 2 ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      clu->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error");
      return false;
    }
    const DotlibNode* top = clu->list_elem(0);
    if ( top->is_int() ) {
      mCapacitiveLoadUnit = top->int_value();
    }
    else if ( top->is_float() ) {
      mCapacitiveLoadUnit = top->float_value();
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      top->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error, a number expected");
      return false;
    }
    const DotlibNode* next = clu->list_elem(1);
    if ( !next->is_string() ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      next->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error, a string expected");
      return false;
    }
    mCapacitiveLoadUnitStr = next->string_value();
  }

  // 'time_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_TIME_UNIT, mTimeUnit) ) {
    return false;
  }

  // 'voltage_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_VOLTAGE_UNIT, mVoltageUnit) ) {
    return false;
  }

  attr_map.get_value(ATTR_LU_TABLE_TEMPLATE, mLutTemplateList);
  attr_map.get_value(ATTR_CELL, mCellList);
  return true;
}
#endif

END_NAMESPACE_YM_DOTLIB
