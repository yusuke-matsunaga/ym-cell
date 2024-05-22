
/// @file CiFLCell.cc
/// @brief CiLFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiFLCell.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFLCell
//////////////////////////////////////////////////////////////////////

// @brief 内部変数1の名前を返す．
string
CiFLCell::qvar1() const
{
  return mVar1;
}

// @brief 内部変数2の名前を返す．
string
CiFLCell::qvar2() const
{
  return mVar2;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
Expr
CiFLCell::clear_expr() const
{
  return mClear;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
Expr
CiFLCell::preset_expr() const
{
  return mPreset;
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
CiFLCell::clear_preset_var1() const
{
  return mCpv1;
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
CiFLCell::clear_preset_var2() const
{
  return mCpv2;
}

// @brief 内容をバイナリダンプする．
void
CiFLCell::dump_FL(
  Serializer& s
) const
{
  dump_common(s);
  s.out() << mVar1
	  << mVar2;
  mClear.dump(s.out());
  mPreset.dump(s.out());
  s.out() << mCpv1
	  << mCpv2;
}

// @brief 内容を読み込む．
void
CiFLCell::restore_FL(
  Deserializer& s
)
{
  CiCell::_restore(s);
  s.in() >> mVar1
	 >> mVar2;
  mClear.restore(s.in());
  mPreset.restore(s.in());
  s.in() >> mCpv1
	 >> mCpv2;
}

END_NAMESPACE_YM_CLIB
