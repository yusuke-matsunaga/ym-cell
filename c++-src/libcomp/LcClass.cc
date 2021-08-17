
/// @file LcClass.cc
/// @brief LcClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/LcClass.h"
#include "lc/LcGroup.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcClass
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LcClass::LcClass(
  int id,
  const LcSignature& rep_sig
) : mId(id),
    mRepSig(rep_sig)
{
}

// @brief デストラクタ
LcClass::~LcClass()
{
}

// @brief グループを追加する．
void
LcClass::add_group(LcGroup* group,
		   const NpnMapM& map)
{
  mGroupList.push_back(group);
  group->mParent = this;
  group->mMap = map;
}

END_NAMESPACE_YM_CLIB_LIBCOMP
