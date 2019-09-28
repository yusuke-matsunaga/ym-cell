
/// @file AstLibrary.cc
/// @brief AstLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstLibrary.h"
#include "dotlib/StrHandler.h"
#include "dotlib/LibraryHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ライブラリを表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstLibrary*
AstMgr::new_library(const FileRegion& attr_loc,
		    const StrHandler& header,
		    const LibraryHandler& group)
{
  void* p = mAlloc.get_memory(sizeof(AstLibrary));
  return new (p) AstLibrary(attr_loc, header, group, mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLibrary
//////////////////////////////////////////////////////////////////////

// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
// @param[in] alloc メモリアロケータ
AstLibrary::AstLibrary(const FileRegion& attr_loc,
		       const StrHandler& header,
		       const LibraryHandler& group,
		       Alloc& alloc) :
  AstNode(FileRegion{attr_loc, group.group_loc()}),
  mName{header.value()},
  mTechnology{group.mTechnology},
  mDelayModel{group.mDelayModel},
  mBusNamingStyle{group.mBusNamingStyle},
  mComment{group.mComment},
  mDate{group.mDate},
  mRevision{group.mRevision},
  mCapacitiveLoadUnit{group.mCapacitiveLoadUnit},
  mCurrentUnit{group.mCurrentUnit},
  mLeakagePowerUnit{group.mLeakagePowerUnit},
  mPullingResistanceUnit{group.mPullingResistanceUnit},
  mTimeUnit{group.mTimeUnit},
  mVoltageUnit{group.mVoltageUnit},
  mLutTemplateList{group.mLutTemplateList, alloc},
  mCellList{group.mCellList, alloc}
{
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
