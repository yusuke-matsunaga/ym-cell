
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief ID番号を返す．
SizeType
CiCellClass::id() const
{
  return mId;
}

// @brief 同位体変換の個数を得る．
// @note 恒等変換は含まない．
SizeType
CiCellClass::idmap_num() const
{
  return mIdmapList.size();
}

// @brief 同位体変換を得る．
// @param[in] pos 位置番号 ( 0 <= pos < idmap_num() )
const NpnMapM&
CiCellClass::idmap(
  SizeType pos
) const
{
  ASSERT_COND( pos >= 0 && pos < idmap_num() );
  return mIdmapList[pos];
}

// @brief グループ数を返す．
SizeType
CiCellClass::cell_group_num() const
{
  return mGroupList.size();
}

// @brief グループを返す．
const ClibCellGroup&
CiCellClass::cell_group(
  SizeType pos ///< [in] インデックス ( 0 <= pos < cell_group_num() )
) const
{
  ASSERT_COND( 0 <= pos && pos < cell_group_num() );
  return *mGroupList[pos];
}

END_NAMESPACE_YM_CLIB
