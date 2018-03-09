
/// @file DotlibCell.cc
/// @brief DotlibCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibCell.h"
#include "DotlibNode.h"
#include "DotlibAttr.h"
#include "DotlibAttrMap.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibCell::DotlibCell()
{
}

// @brief デストラクタ
DotlibCell::~DotlibCell()
{
}

// @brief 内容を設定する．
bool
DotlibCell::set_data(const DotlibNode* node)
{
  mArea = 0.0;
  mBusNamingStyle = nullptr;
  mFF = nullptr;
  mLatch = nullptr;
  mStateTable = nullptr;

  mPinList.clear();
  mBusList.clear();
  mBundleList.clear();

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
  const vector<const DotlibNode*> pin_list;
  attr_map.get_value(ATTR_PIN, pin_list);
  int npg = dt_pin_list.size();
  mPinInfoArray.resize(npg);
  {
    int i = 0;
    bool error = false;
    for ( const DotlibNode* pin_node: pin_list ) {
      // ピン情報の読み出し
      DotlibPin& pin_info = mPinInfoArray[i]; ++ i;
      if ( !pin_info.set_data(pin_node) ) {
	return false;
      }
    }
    if ( error ) {
      continue;
    }
    ASSERT_COND( i == npg );
  }

  // バスグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  attr_map.get_value(ATTR_BUS, mBusList);

  // バンドルグループを取り出す．
  // 定義されていなくてもエラーにはならない．
  attr_map.get_value(ATTR_BUNDLE, mBundleList);

  // ff を取り出す．
  const DotlibNode* ff_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_FF, ff_node) ) {
    return false;
  }
  if ( ff_node != nullptr ) {
    if ( !mFF.set_data(ff_node) ) {
      return false;
    }
  }

  // latch を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_LATCH, mLatch) ) {
    return false;
  }

  // statetable を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_STATETABLE, mStateTable) ) {
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

// @brief 名前を返す．
ShString
DotlibCell::name() const
{
  return mName;
}

// @brief 面積を返す．
double
DotlibCell::area() const
{
  return mArea;
}

// @brief ピングループのリストを返す．
const vector<const DotlibNode*>&
DotlibCell::pin_list() const
{
  return mPinList;
}

// @brief バスグループのリストを返す．
const vector<const DotlibNode*>&
DotlibCell::bus_list() const
{
  return mBusList;
}

// @brief バンドルグループのリストを返す．
const vector<const DotlibNode*>&
DotlibCell::bundle_list() const
{
  return mBundleList;
}

// @brief ff グループを返す．
// @note なければ nullptr を返す．
const DotlibNode*
DotlibCell::ff() const
{
  return mFF;
}

// @brief latch グループを返す．
// @note なければ nullptr を返す．
const DotlibNode*
DotlibCell::latch() const
{
  return mLatch;
}

// @brief statetable グループを返す．
// @note なければ nullptr を返す．
const DotlibNode*
DotlibCell::statetable() const
{
  return mStateTable;
}

END_NAMESPACE_YM_DOTLIB
