
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

// @brief 次元数の取得
SizeType
ClibLut::dimension() const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  SizeType id = lut->lut_template();
  auto lut_templ = mLibrary->_lut_template(id);
  return lut_templ->dimension();
}

// @brief 変数型の取得
ClibVarType
ClibLut::variable_type(
  SizeType var
) const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  SizeType id = lut->lut_template();
  auto lut_templ = mLibrary->_lut_template(id);
  return lut_templ->variable_type(var);
}

// @brief インデックス数の取得
SizeType
ClibLut::index_num(
  SizeType var
) const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  return lut->index_num(var);
}

// @brief インデックス値の取得
double
ClibLut::index(
  SizeType var,
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  return lut->index(var, pos);
}

// @brief 格子点の値の取得
double
ClibLut::grid_value(
  const vector<SizeType>& pos_array
) const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  return lut->grid_value(pos_array);
}

// @brief 値の取得
double
ClibLut::value(
  const vector<double>& val_array
) const
{
  ASSERT_COND( is_valid() );
  auto lut = mLibrary->_lut(mId);
  return lut->value(val_array);
}

END_NAMESPACE_YM_CLIB
