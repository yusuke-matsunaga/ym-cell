
/// @file CiLutTemplate.cc
/// @brief CiLutTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLutTemplate.h"
#include "CiLutTemplate_sub.h"


BEGIN_NAMESPACE_YM_CLIB

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
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType;
}

// @brief インデックス数の取得
SizeType
CiLutTemplate1D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray.size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate1D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray;
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
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate2D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate2D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var];
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
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate3D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate3D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var];
}

END_NAMESPACE_YM_CLIB
