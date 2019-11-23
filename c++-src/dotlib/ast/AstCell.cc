
/// @file AstCell.cc
/// @brief AstCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstCell.h"
#include "dotlib/StrHandler.h"
#include "dotlib/CellHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief セルを表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstCell*
AstMgr::new_cell(const FileRegion& attr_loc,
		 const StrHandler& header,
		 const CellHandler& group)
{
  void* p = mAlloc.get_memory(sizeof(AstCell));
  return new (p) AstCell(attr_loc, header, group, mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
// @param[in] alloc メモリアロケータ
AstCell::AstCell(const FileRegion& attr_loc,
		 const StrHandler& header,
		 const CellHandler& group,
		 Alloc& alloc) :
  AstNameNode{FileRegion{attr_loc, group.group_loc()}, header},
  mArea{group.mArea},
  mBusNamingStyle{group.mBusNamingStyle},
  mPinList{group.mPinList, alloc},
  mBusList{group.mBusList, alloc},
  mBundleList{group.mBundleList, alloc},
  mFF{group.mFF},
  mLatch{group.mLatch},
  mStateTable{group.mStateTable}
{
}

// @brief デストラクタ
AstCell::~AstCell()
{
}

#if 0
// @brief 内容を設定する．
bool
AstCell::set_data(const AstNode* node)
{
  mArea = 0.0;
  mBusNamingStyle = nullptr;
  mPinTop = nullptr;
  mBusTop = nullptr;
  mBundleTop = nullptr;
  mFF = nullptr;
  mLatch = nullptr;
  mStateTable = nullptr;

  // セル名を得る．
  mName = node->group_value()->get_string_from_value_list();

  // 属性のリストを作る．
  AstAttrMap attr_map(node->attr_top());

  // 面積を得る．
  const AstNode* area_node;
  if ( !attr_map.expect_singleton(ATTR_area, node->loc(), area_node) ) {
    return false;
  }
  if ( !area_node->expect_float(mArea) ) {
    return false;
  }

  // ピングループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const AstNode*> pin_list;
  attr_map.get_value(ATTR_pin, pin_list);
  AstPin* prev_pin = nullptr;
  for ( const AstNode* pin_node: pin_list ) {
    // ピン情報の読み出し
    AstPin* pin = new AstPin(pin_node);
    if ( pin == nullptr ) {
      return false;
    }
    if ( mPinTop == nullptr ) {
      mPinTop = pin;
    }
    else {
      ASSERT_COND( prev_pin != nullptr );
      prev_pin->set_next(pin);
    }
    prev_pin = pin;
  }

  // バスグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const AstNode*> bus_list;
  attr_map.get_value(ATTR_bus, bus_list);

  // バンドルグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const AstNode*> bundle_list;
  attr_map.get_value(ATTR_bundle, bundle_list);

  // ff を取り出す．
  const AstNode* ff_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_ff, ff_node) ) {
    return false;
  }
  if ( ff_node != nullptr ) {
    mFF = new AstFF(ff_node);
    if ( mFF == nullptr ) {
      return false;
    }
  }

  // latch を取り出す．
  const AstNode* latch_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_latch, latch_node) ) {
    return false;
  }
  if ( latch_node != nullptr ) {
    mLatch = new AstLatch(latch_node);
    if ( mLatch == nullptr ) {
      return false;
    }
  }

  // statetable を取り出す．
  const AstNode* state_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_statetable, state_node) ) {
    return false;
  }

  // ff と latch と statetable は排他的
  {
    const char* first_name = nullptr;
    const char* last_name = nullptr;
    FileRegion first_loc;
    FileRegion last_loc;
    if ( mFF && mLatch ) {
      FileRegion ff_loc = mFF->loc();
      FileRegion latch_loc = mLatch->loc();
      if ( ff_loc.start_line() < latch_loc.start_line() ) {
	first_name = "ff";
	first_loc = ff_loc;
	last_name = "latch";
	last_loc = latch_loc;
      }
      else {
	first_name = "latch";
	first_loc = latch_loc;
	last_name = "ff";
	last_loc = ff_loc;
      }
    }
    else if ( mFF && mStateTable ) {
      FileRegion ff_loc = mFF->loc();
      FileRegion st_loc = mStateTable->loc();
      if ( ff_loc.start_line() < st_loc.start_line() ) {
	first_name = "ff";
	first_loc = ff_loc;
	last_name = "statetable";
	last_loc = st_loc;
      }
      else {
	first_name = "statetable";
	first_loc = st_loc;
	last_name = "ff";
	last_loc = ff_loc;
      }
    }
    else if ( mLatch && mStateTable ) {
      FileRegion latch_loc = mLatch->loc();
      FileRegion st_loc = mStateTable->loc();
      if ( latch_loc.start_line() < st_loc.start_line() ) {
	first_name = "latch";
	first_loc = latch_loc;
	last_name = "statetable";
	last_loc = st_loc;
      }
      else {
	first_name = "statetable";
	first_loc = st_loc;
	last_name = "latch";
	last_loc = latch_loc;
      }
    }
    if ( first_name ) {
      ostringstream buf;
      buf << "'" << last_name << "' group cannot be used with '"
	  << first_name << "' group at "
	  << first_loc << ".";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      last_loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      buf.str());
      return false;
    }
  }
  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstCell::dump(ostream& s,
	      int indent) const
{
  #warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
