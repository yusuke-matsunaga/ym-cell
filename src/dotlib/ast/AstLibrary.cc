
/// @file AstLibrary.cc
/// @brief AstLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstLibrary.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ライブラリを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] name
// @param[in] technology
// @param[in] delay_model
// @param[in] bus_naming_style
// @param[in] comment
// @param[in] date
// @param[in] revision
// @param[in] capacitive_load_unit
// @param[in] current_unit
// @param[in] leakage_power_unit
// @param[in] pulling_resistance_unit
// @param[in] time_unit
// @param[in] voltage_unit
// @param[in] lut_template_list
// @param[in] cell_list
AstLibrary*
AstMgr::new_library(const FileRegion& loc,
		    const AstString* name,
		    const AstTechnology* technology,
		    const AstDelayModel* delay_model,
		    const AstString* bus_naming_style,
		    const AstString* comment,
		    const AstString* date,
		    const AstString* revision,
		    const AstUnit* capacitive_load_unit,
		    const AstString* current_unit,
		    const AstString* leakage_power_unit,
		    const AstString* pulling_resistance_unit,
		    const AstString* time_unit,
		    const AstString* voltage_unit,
		    const vector<const AstTemplate*>& lut_template_list,
		    const vector<const AstCell*>& cell_list)
{
  void* p = mAlloc.get_memory(sizeof(AstLibrary));
  return new (p) AstLibrary(loc, name, technology, delay_model, bus_naming_style,
			    comment, date, revision,
			    capacitive_load_unit, current_unit,
			    leakage_power_unit, pulling_resistance_unit,
			    time_unit, voltage_unit,
			    lut_template_list, cell_list,
			    mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
AstLibrary::AstLibrary(const FileRegion& loc,
		       const AstString* name,
		       const AstTechnology* technology,
		       const AstDelayModel* delay_model,
		       const AstString* bus_naming_style,
		       const AstString* comment,
		       const AstString* date,
		       const AstString* revision,
		       const AstUnit* capacitive_load_unit,
		       const AstString* current_unit,
		       const AstString* leakage_power_unit,
		       const AstString* pulling_resistance_unit,
		       const AstString* time_unit,
		       const AstString* voltage_unit,
		       const vector<const AstTemplate*>& lut_template_list,
		       const vector<const AstCell*>& cell_list,
		       Alloc& alloc) :
  AstNode(loc),
  mName(name),
  mTechnology(technology),
  mDelayModel(delay_model),
  mBusNamingStyle(bus_naming_style),
  mComment(comment),
  mDate(date),
  mRevision(revision),
  mCapacitiveLoadUnit(capacitive_load_unit),
  mCurrentUnit(current_unit),
  mLeakagePowerUnit(leakage_power_unit),
  mPullingResistanceUnit(pulling_resistance_unit),
  mTimeUnit(time_unit),
  mVoltageUnit(voltage_unit),
  mLutTemplateNum(lut_template_list.size()),
  mLutTemplateList(alloc.get_array<const AstTemplate*>(mLutTemplateNum)),
  mCellNum(cell_list.size()),
  mCellList(alloc.get_array<const AstCell*>(mCellNum))
{
  for ( auto i: Range(mLutTemplateNum) ) {
    mLutTemplateList[i] = lut_template_list[i];
  }
  for ( auto i: Range(mCellNum) ) {
    mCellList[i] = cell_list[i];
  }
}

// @brief デストラクタ
AstLibrary::~AstLibrary()
{
}

#if 0
// @brief 内容を初期化する．
bool
AstLibrary::set_data(const AstNode* node)
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
  AstAttrMap attr_map(node->attr_top());

  // 'technology' を取り出す．
  const AstNode* tech_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_technology, tech_node) ) {
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
  const AstNode* dm_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_delay_model, dm_node) ) {
    return false;
  }
  ASSERT_COND( dm_node->type() == AstNode::kDelayModel );
  mDelayModel = dm_node->delay_model();

  // 'bus_naming_style' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_bus_naming_style, mBusNamingStyle) ) {
    return false;
  }

  // 'comment' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_comment, mComment) ) {
    return false;
  }

  // 'date' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_date, mDate) ) {
    return false;
  }

  // 'revision' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_revision, mRevision) ) {
    return false;
  }

  // 'current_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_current_unit, mCurrentUnit) ) {
    return false;
  }

  // 'leakage_power_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_leakage_power_unit, mLeakagePowerUnit) ) {
    return false;
  }

  // 'pulling_resistance_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_pulling_resistance_unit,
				 mPullingResistanceUnit) ) {
    return false;
  }

  // 'capacitive_load_unit' を取り出す．
  const AstNode* clu = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_capacitive_load_unit, clu) ) {
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
    const AstNode* top = clu->list_elem(0);
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
    const AstNode* next = clu->list_elem(1);
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
  if ( !attr_map.expect_singleton_or_null(ATTR_time_unit, mTimeUnit) ) {
    return false;
  }

  // 'voltage_unit' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_volTAGE_UNIT, mVoltageUnit) ) {
    return false;
  }

  attr_map.get_value(ATTR_lu_table_template, mLutTemplateList);
  attr_map.get_value(ATTR_cell, mCellList);
  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLibrary::dump(ostream& s,
		 int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
