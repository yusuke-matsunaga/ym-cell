
/// @file ClibLut.cc
/// @brief ClibLut の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLut.h"
#include "ci/CiLut.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibLut
//////////////////////////////////////////////////////////////////////

// @brief 内容を指定したコンストラクタ
ClibLut::ClibLut(
  const CiLut* impl
) : mImpl{impl}
{
  if ( mImpl != nullptr ) {
    mImpl->inc_ref();
  }
}

// @brief デストラクタ
ClibLut::~ClibLut()
{
  if ( mImpl != nullptr ) {
    mImpl->dec_ref();
  }
}

// @brief 次元数の取得
SizeType
ClibLut::dimension() const
{
  _check_valid();
  auto lut_templ = mImpl->lut_template();
  return lut_templ->dimension();
}

// @brief 変数型の取得
ClibVarType
ClibLut::variable_type(
  SizeType var
) const
{
  _check_valid();
  auto lut_templ = mImpl->lut_template();
  return lut_templ->variable_type(var);
}

// @brief インデックス数の取得
SizeType
ClibLut::index_num(
  SizeType var
) const
{
  _check_valid();
  return mImpl->index_num(var);
}

// @brief インデックス値の取得
double
ClibLut::index(
  SizeType var,
  SizeType pos
) const
{
  _check_valid();
  return mImpl->index(var, pos);
}

// @brief 格子点の値の取得
double
ClibLut::grid_value(
  const vector<SizeType>& pos_array
) const
{
  _check_valid();
  return mImpl->grid_value(pos_array);
}

// @brief 値の取得
double
ClibLut::value(
  const vector<double>& val_array
) const
{
  _check_valid();
  return mImpl->value(val_array);
}

END_NAMESPACE_YM_CLIB
