
/// @file CiBundle.cc
/// @brief CiBundle の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiBundle.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiBundle::CiBundle()
{
}

// @brief デストラクタ
CiBundle::~CiBundle()
{
  // メモリ管理は他のクラスがやる．
}

// @brief 名前の取得
string
CiBundle::name() const
{
  return mName;
}

// @brief ピン数の取得
int
CiBundle::pin_num() const
{
  return mPinList.num();
}

// @brief ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
const ClibCellPin*
CiBundle::pin(int pos) const
{
  return mPinList[pos];
}

// @brief 内容を初期化する．
void
CiBundle::init(const ShString& name,
	       const vector<CiCellPin*>& pin_list,
	       Alloc& alloc)
{
  mName = name;
  mPinList.init(pin_list, alloc);
}

END_NAMESPACE_YM_CLIB
