
/// @file AstCell.cc
/// @brief AstCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstCell.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief セルを表す AstNode を生成する．
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
AstCell*
AstMgr::new_cell(const FileRegion& loc,
		 const AstString* name,
		 const AstFloat* area,
		 const AstString* bus_naming_style,
		 const vector<const AstPin*>& pin_list,
		 const vector<const AstBus*>& bus_list,
		 const vector<const AstBundle*>& bundle_list,
		 const AstFF* ff,
		 const AstLatch* latch,
		 const AstStateTable* statetable)
{
  void* p = mAlloc.get_memory(sizeof(AstCell));
  return new (p) AstCell(loc,name, area, bus_naming_style,
			 pin_list, bus_list, bundle_list,
			 ff, latch, statetable,
			 mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstCell
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
AstCell::AstCell(const FileRegion& loc,
		 const AstString* name,
		 const AstFloat* area,
		 const AstString* bus_naming_style,
		 const vector<const AstPin*>& pin_list,
		 const vector<const AstBus*>& bus_list,
		 const vector<const AstBundle*>& bundle_list,
		 const AstFF* ff,
		 const AstLatch* latch,
		 const AstStateTable* statetable,
		 Alloc& alloc) :
  AstNode(loc),
  mName(name),
  mArea(area),
  mBusNamingStyle(bus_naming_style),
  mPinNum(pin_list.size()),
  mPinList(alloc.get_array<const AstPin*>(mPinNum)),
  mBusNum(bus_list.size()),
  mBusList(alloc.get_array<const AstBus*>(mBusNum)),
  mBundleNum(bundle_list.size()),
  mBundleList(alloc.get_array<const AstBundle*>(mBundleNum)),
  mFF(ff),
  mLatch(latch),
  mStateTable(statetable)
{
  for ( auto i: Range(mPinNum) ) {
    mPinList[i] = pin_list[i];
  }
  for ( auto i: Range(mBusNum) ) {
    mBusList[i] = bus_list[i];
  }
  for ( auto i: Range(mBundleNum) ) {
    mBundleList[i] = bundle_list[i];
  }
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
  if ( !attr_map.expect_singleton(ATTR_AREA, node->loc(), area_node) ) {
    return false;
  }
  if ( !area_node->expect_float(mArea) ) {
    return false;
  }

  // ピングループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const AstNode*> pin_list;
  attr_map.get_value(ATTR_PIN, pin_list);
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
  attr_map.get_value(ATTR_BUS, bus_list);

  // バンドルグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  vector<const AstNode*> bundle_list;
  attr_map.get_value(ATTR_BUNDLE, bundle_list);

  // ff を取り出す．
  const AstNode* ff_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_FF, ff_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_LATCH, latch_node) ) {
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
