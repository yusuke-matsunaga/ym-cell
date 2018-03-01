
/// @file LcGroup.cc
/// @brief LcGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcGroup.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] id ID番号
LcGroup::LcGroup(int id) :
  mId(id),
  mParent(nullptr),
  mCellGroup(nullptr)
{
}

// @brief デストラクタ
LcGroup::~LcGroup()
{
}

// @brief ID番号を返す．
int
LcGroup::id() const
{
  return mId;
}

// @brief 親の LcClass を返す．
LcClass*
LcGroup::parent() const
{
  return mParent;
}

// @brief 親のクラスに対する変換マップを返す．
const NpnMapM&
LcGroup::map() const
{
  return mMap;
}

// @brief 実体を返す．
ClibCellGroup*
LcGroup::cell_group() const
{
  return mCellGroup;
}

// @brief 属しているセルのリストを返す．
const vector<CiCell*>&
LcGroup::cell_list() const
{
  return mCellList;
}

// @brief セルを追加する．
// @param[in] cell セル
void
LcGroup::add_cell(CiCell* cell)
{
  mCellList.push_back(cell);
}

END_NAMESPACE_YM_CLIB_LIBCOMP
