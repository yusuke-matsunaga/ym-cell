﻿
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ym/ClibCellLibrary.h"
#include "ym/NpnMapM.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellClass::CiCellClass() :
  mIdmapNum(0),
  mIdmapList(nullptr)
{
}

// @brief デストラクタ
CiCellClass::~CiCellClass()
{
  // mIdmapList, mGroupList は ClibMgr が管理している．
}

// @brief ID番号を返す．
// @note ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
int
CiCellClass::id() const
{
  return mId;
}

// @brief 同位体変換の個数を得る．
// @note 恒等変換は含まない．
int
CiCellClass::idmap_num() const
{
  return mIdmapNum;
}

// @brief 同位体変換を得る．
// @param[in] pos 位置番号 ( 0 <= pos < idmap_num() )
const NpnMapM&
CiCellClass::idmap(int pos) const
{
  ASSERT_COND( pos < mIdmapNum );
  return mIdmapList[pos];
}

// @brief セルグループのリストを返す．
const ClibCellGroupList&
CiCellClass::group_list() const
{
  return mGroupList;
}

// @brief 初期化する．
// @param[in] id 番号
// @param[in] idmap_list 同位体変換リスト
// @param[in] group_list グループのリスト
// @param[in] alloc メモリアロケータ
void
CiCellClass::init(int id,
		  const vector<NpnMapM>& idmap_list,
		  const vector<CiCellGroup*>& group_list,
		  Alloc& alloc)
{
  mId = id;

  mIdmapNum = idmap_list.size();
  if ( mIdmapNum > 0 ) {
    void* p = alloc.get_memory(sizeof(NpnMapM) * mIdmapNum);
    mIdmapList = new (p) NpnMapM[mIdmapNum];
  }
  else {
    mIdmapList = nullptr;
  }
  for ( int i = 0; i < mIdmapNum; ++ i ) {
    mIdmapList[i] = idmap_list[i];
  }

  mGroupList.init(group_list, alloc);
  for ( auto group: group_list ) {
    group->set_class(this);
  }
}

END_NAMESPACE_YM_CLIB
