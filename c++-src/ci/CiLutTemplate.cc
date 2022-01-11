
/// @file CiLutTemplate.cc
/// @brief CiLutTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLutTemplate.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief ID番号の取得
SizeType
CiLutTemplate::id() const
{
  return mId;
}

// @brief 名前の取得
string
CiLutTemplate::name() const
{
  return _name();
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplateBad
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplateBad::dimension() const
{
  return 0;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplateBad::variable_type(
  SizeType var
) const
{
  return ClibVarType::none;
}

// @brief インデックス数の取得
SizeType
CiLutTemplateBad::index_num(
  SizeType var
) const
{
  return 0;
}

// @brief デフォルトインデックス値の取得
double
CiLutTemplateBad::index(
  SizeType var,
  SizeType pos
) const
{
  return 0.0;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate1D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate1D::dimension() const
{
  return 1;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate1D::variable_type(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mVarType;
}

// @brief インデックス数の取得
SizeType
CiLutTemplate1D::index_num(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mIndexArray.size();
}

// @brief デフォルトインデックス値の取得
double
CiLutTemplate1D::index(
  SizeType var,
  SizeType pos
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  ASSERT_COND( 0 <= pos && pos < index_num(0) );
  return mIndexArray[pos];
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate2D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate2D::dimension() const
{
  return 2;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate2D::variable_type(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate2D::index_num(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mIndexArray[var].size();
}

// @brief デフォルトインデックス値の取得
double
CiLutTemplate2D::index(
  SizeType var,
  SizeType pos
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  ASSERT_COND( 0 <= pos && pos < index_num(var) );
  return mIndexArray[var][pos];
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate3D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate3D::dimension() const
{
  return 3;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate3D::variable_type(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate3D::index_num(
  SizeType var
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  return mIndexArray[var].size();
}

// @brief デフォルトインデックス値の取得
double
CiLutTemplate3D::index(
  SizeType var,
  SizeType pos
) const
{
  ASSERT_COND( 0 <= var && var < dimension() );
  ASSERT_COND( 0 <= pos && pos < index_num(var) );
  return mIndexArray[var][pos];
}

END_NAMESPACE_YM_CLIB
