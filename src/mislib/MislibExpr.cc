
/// @file MislibExpr.cc
/// @brief MislibExpr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibExpr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
MislibExpr::MislibExpr(const FileRegion& loc) :
  MislibNode(loc)
{
}

// デストラクタ
MislibExpr::~MislibExpr()
{
}

// @brief 変数名を取り出す
//
// デフォルトの実装ではエラー(アボート)となる．
ShString
MislibExpr::varname() const
{
  ASSERT_NOT_REACHED;
  return ShString();
}

// 1番目の子供を取り出す．
// デフォルトの実装ではエラー(アボート)となる．
const MislibExpr*
MislibExpr::child1() const
{
  ASSERT_NOT_REACHED;
  return nullptr;
}

// 2番目の子供を取り出す．
// デフォルトの実装ではエラー(アボート)となる．
const MislibExpr*
MislibExpr::child2() const
{
  ASSERT_NOT_REACHED;
  return nullptr;
}

END_NAMESPACE_YM_MISLIB
