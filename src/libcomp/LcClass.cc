
/// @file LcClass.cc
/// @brief LcClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcClass.h"
#include "LcGroup.h"


BEGIN_NAMESPACE_YM_CELL_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcClass
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] id ID番号
// @param[in] rep_sig 代表シグネチャ
LcClass::LcClass(ymuint id,
		 const LcSignature& rep_sig) :
  mId(id),
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

END_NAMESPACE_YM_CELL_LIBCOMP
