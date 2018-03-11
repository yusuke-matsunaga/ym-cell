
/// @file DotlibCell.cc
/// @brief DotlibCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibCell.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] area 面積
// @param[in] bus_naming_style 'bus_naming_style' の値
// @param[in] pin_top ピンの先頭
// @param[in] bus_top バスの先頭
// @param[in] bundle_top バンドルの先頭
// @param[in] ff FFグループ
// @param[in] latch ラッチグループ
// @param[in] statetable StateTable グループ
DotlibCell::DotlibCell(const FileRegion& loc,
		       const DotlibString* name,
		       const DotlibFloat* area,
		       const DotlibString* bus_naming_style,
		       const DotlibPin* pin_top,
		       const DotlibBus* bus_top,
		       const DotlibBundle* bundle_top,
		       const DotlibFF* ff,
		       const DotlibLatch* latch,
		       const DotlibStateTable* statetable) :
  DotlibNode(loc),
  mName(name),
  mArea(area),
  mBusNamingStyle(bus_naming_style),
  mPinTop(pin_top),
  mBusTop(bus_top),
  mBundleTop(bundle_top),
  mFF(ff),
  mLatch(latch),
  mStateTable(statetable)
{
}

// @brief デストラクタ
DotlibCell::~DotlibCell()
{
}

#if 0
// @brief 内容を設定する．
bool
DotlibCell::set_data(const DotlibNode* node)
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
  DotlibAttrMap attr_map(node->attr_top());

  // 面積を得る．
  const DotlibNode* area_node;
  if ( !attr_map.expect_singleton(ATTR_AREA, node->loc(), area_node) ) {
    return false;
  }
  if ( !area_node->expect_float(mArea) ) {
    return false;
  }

  // ピングループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const DotlibNode*> pin_list;
  attr_map.get_value(ATTR_PIN, pin_list);
  DotlibPin* prev_pin = nullptr;
  for ( const DotlibNode* pin_node: pin_list ) {
    // ピン情報の読み出し
    DotlibPin* pin = new DotlibPin(pin_node);
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
  vector<const DotlibNode*> bus_list;
  attr_map.get_value(ATTR_BUS, bus_list);

  // バンドルグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const DotlibNode*> bundle_list;
  attr_map.get_value(ATTR_BUNDLE, bundle_list);

  // ff を取り出す．
  const DotlibNode* ff_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_FF, ff_node) ) {
    return false;
  }
  if ( ff_node != nullptr ) {
    mFF = new DotlibFF(ff_node);
    if ( mFF == nullptr ) {
      return false;
    }
  }

  // latch を取り出す．
  const DotlibNode* latch_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_LATCH, latch_node) ) {
    return false;
  }
  if ( latch_node != nullptr ) {
    mLatch = new DotlibLatch(latch_node);
    if ( mLatch == nullptr ) {
      return false;
    }
  }

  // statetable を取り出す．
  const DotlibNode* state_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_STATETABLE, state_node) ) {
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

END_NAMESPACE_YM_DOTLIB
