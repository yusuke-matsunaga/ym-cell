
/// @file CiLibObj.cc
/// @brief CiLibObj の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLibObj.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLibObj
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLibObj::CiLibObj(
  CiCellLibrary* lib
) : mParent{lib}
{
  inc_ref();
}

// @brief デストラクタ
CiLibObj::~CiLibObj()
{
  dec_ref();
}

// @brief 参照数を増やす
void
CiLibObj::inc_ref() const
{
  mParent->inc_ref();
}

// @brief 参照数を減らす
void
CiLibObj::dec_ref() const
{
  mParent->inc_ref();
}

END_NAMESPACE_YM_CLIB
