
/// @file ClibLutTemplate.cc
/// @brief ClibLutTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLutTemplate.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
ClibLutTemplate::name() const
{
  ASSERT_COND( is_valid() );
  auto lu_temp = mLibrary->_lut_template(mId);
  return lu_temp->name();
}

// @brief 次元数の取得
SizeType
ClibLutTemplate::dimension() const
{
  ASSERT_COND( is_valid() );
  auto lu_temp = mLibrary->_lut_template(mId);
  return lu_temp->dimension();
}

// @brief 変数型の取得
ClibVarType
ClibLutTemplate::variable_type(
  SizeType var
) const
{
  ASSERT_COND( is_valid() );
  auto lu_temp = mLibrary->_lut_template(mId);
  return lu_temp->variable_type(var);
}

// @brief インデックス数の取得
SizeType
ClibLutTemplate::index_num(
  SizeType var
) const
{
  ASSERT_COND( is_valid() );
  auto lu_temp = mLibrary->_lut_template(mId);
  return lu_temp->index_num(var);
}

// @brief デフォルトインデックス値の取得
double
ClibLutTemplate::index(
  SizeType var,
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto lu_temp = mLibrary->_lut_template(mId);
  return lu_temp->index(var, pos);
}

END_NAMESPACE_YM_CLIB
