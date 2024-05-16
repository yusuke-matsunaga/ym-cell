
/// @file CiLut.cc
/// @brief CiLut の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLut.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief val に対応する区間を求める．
SizeType
CiLut::search(
  double val,
  const vector<double>& index_array
)
{
  auto n = index_array.size();
  if ( val <= index_array[0] ) {
    // 値が小さすぎる時は [0, 1] を返す．
    return 0;
  }
  if ( val >= index_array[n - 1] ) {
    // 値が大きすぎる時は [n - 2, n - 1] を返す．
    return n - 2;
  }
  // 単純な線形探索を行う．
  for ( auto i: Range(n - 1) ) {
    if ( val < index_array[i + 1] ) {
      return i;
    }
  }
  ASSERT_NOT_REACHED;
  return 0;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLut1D::CiLut1D(
  const CiCellLibrary* lib,
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array
) : CiLut{lib, lut_template},
    mValueArray{value_array},
    mIndexArray{index_array}
{
  if ( value_array.size() != index_array.size() ) {
    throw std::invalid_argument{"value_array.size() != index_array.size()"};
  }
}

// @brief インデックス数の取得
SizeType
CiLut1D::index_num(
  SizeType var
) const
{
  if ( var != 0 ) {
    throw std::out_of_range{"var should be 0"};
  }
  return mIndexArray.size();
}

// @brief インデックス値の取得
double
CiLut1D::index(
  SizeType var,
  SizeType pos
) const
{
  if ( var != 0 ) {
    throw std::out_of_range{"var should be 0"};
  }
  if ( pos < 0 || index_num(var) <= pos ) {
    throw std::out_of_range{"pos is out of range"};
  }
  return mIndexArray[pos];
}

// @brief 格子点の値の取得
double
CiLut1D::grid_value(
  const vector<SizeType>& pos_array
) const
{
  if ( pos_array.size() != 1 ) {
    throw std::invalid_argument{"pos_array.size() should be 1"};
  }
  auto pos1 = pos_array[0];
  if ( pos1 < 0 || mValueArray.size() <= pos1 ) {
    throw std::out_of_range{"pos_array[0] is out of range"};
  }
  return mValueArray[pos1];
}

// @brief 値の取得
double
CiLut1D::value(
  const vector<double>& val_array
) const
{
  if ( val_array.size() != 1 ) {
    throw std::invalid_argument{"val_array.size() should be 1"};
  }

  double val = val_array[0];

  auto idx_a = search(val, mIndexArray);
  auto idx_b = idx_a + 1;
  double x0 = mIndexArray[idx_a];
  double x1 = mIndexArray[idx_b];
  double w  = x1 - x0;
  double dx0 = (val - x0) / w;
  double dx1 = (x1 - val) / w;
  double val_0 = mValueArray[idx_a];
  double val_1 = mValueArray[idx_b];
  return val_0 * dx1 + val_1 * dx0;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLut2D::CiLut2D(
  const CiCellLibrary* lib,
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2
) : CiLut{lib, lut_template},
    mValueArray{value_array},
    mIndexArray{index_array1, index_array2}
{
  SizeType n = mIndexArray[0].size() * mIndexArray[1].size();
  if ( value_array.size() != n ) {
    throw std::invalid_argument{"value_array.size() is not consistent with index_array1.size() and index_arary2.size()"};
  }
}

// @brief インデックス数の取得
SizeType
CiLut2D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::invalid_argument{"var should 0 or 1"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス値の取得
double
CiLut2D::index(
  SizeType var,
  SizeType pos
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::invalid_argument{"var should 0 or 1"};
  }
  if ( pos < 0 || index_num(var) <= pos ) {
    throw std::out_of_range{"pos is out of range"};
  }
  return mIndexArray[var][pos];
}

// @brief 格子点の値の取得
double
CiLut2D::grid_value(
  const vector<SizeType>& pos_array
) const
{
  if ( pos_array.size() != 2 ) {
    throw std::invalid_argument{"pos_array.size() should be 2"};
  }
  auto pos1 = pos_array[0];
  auto pos2 = pos_array[1];
  if ( pos1 < 0 || index_num(0) <= pos1 ) {
    throw std::out_of_range{"pos_array[0] is out of range"};
  }
  if ( pos2 < 0 || index_num(1) <= pos2 ) {
    throw std::out_of_range{"pos_array[1] is out of range"};
  }
  return mValueArray[idx(pos1, pos2)];
}

// @brief 値の取得
double
CiLut2D::value(
  const vector<double>& val_array
) const
{
  if ( val_array.size() != 2 ) {
    throw std::invalid_argument{"val_array.size() should be 2"};
  }

  double val1 = val_array[0];
  auto idx1_a = search(val1, mIndexArray[0]);
  auto idx1_b = idx1_a + 1;
  double x0 = mIndexArray[0][idx1_a];
  double x1 = mIndexArray[0][idx1_b];

  double val2 = val_array[1];
  auto idx2_a = search(val2, mIndexArray[1]);
  auto idx2_b = idx2_a + 1;
  double y0 = mIndexArray[1][idx2_a];
  double y1 = mIndexArray[1][idx2_b];

  // 単純な線形補間
  double wx  = x1 - x0;
  double dx0 = (val1 - x0) / wx;
  double dx1 = (x1 - val1) / wx;
  double wy  = y1 - y0;
  double dy0 = (val2 - y0) / wy;
  double dy1 = (y1 - val2) / wy;
  double val_00 = mValueArray[idx(idx1_a, idx2_a)];
  double val_01 = mValueArray[idx(idx1_a, idx2_b)];
  double val_10 = mValueArray[idx(idx1_b, idx2_a)];
  double val_11 = mValueArray[idx(idx1_b, idx2_b)];

  return dx1 * (dy1 * val_00 + dy0 * val_01) +
         dx0 * (dy1 * val_10 + dy0 * val_11);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLut3D::CiLut3D(
  const CiCellLibrary* lib,
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
) : CiLut{lib, lut_template},
    mValueArray{value_array},
    mIndexArray{index_array1, index_array2, index_array3}
{
  SizeType n = mIndexArray[0].size() * mIndexArray[1].size() * mIndexArray[2].size();;
  if ( value_array.size() != n ) {
    throw std::invalid_argument{"value_array.size() is not consistent with index1_array.size(), index2_array.size() and index3_array.size()"};
  }
}

// @brief インデックス数の取得
SizeType
CiLut3D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::invalid_argument{"var should be 0, 1, or 2"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス値の取得
double
CiLut3D::index(
  SizeType var,
  SizeType pos
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::invalid_argument{"var should be 0, 1, or 2"};
  }
  if ( pos < 0 || index_num(var) <= pos ) {
    throw std::out_of_range{"pos is out of range"};
  }
  return mIndexArray[var][pos];
}

// @brief 格子点の値の取得
double
CiLut3D::grid_value(
  const vector<SizeType>& pos_array
) const
{
  if ( pos_array.size() != 3 ) {
    throw std::invalid_argument{"pos_array.size() should be 3"};
  }
  auto pos1 = pos_array[0];
  auto pos2 = pos_array[1];
  auto pos3 = pos_array[2];
  if ( pos1 < 0 || index_num(0) <= pos1 ) {
    throw std::out_of_range{"pos1 is out of range"};
  }
  if ( pos2 < 0 || index_num(1) <= pos2 ) {
    throw std::out_of_range{"pos2 is out of range"};
  }
  if ( pos3 < 0 || index_num(2) <= pos3 ) {
    throw std::out_of_range{"pos3 is out of range"};
  }
  return mValueArray[idx(pos1, pos2, pos3)];
}

// @brief 値の取得
double
CiLut3D::value(
  const vector<double>& val_array
) const
{
  if ( val_array.size() != 3 ) {
    throw std::invalid_argument{"val_array.size() should be 3"};
  }
  double val1 = val_array[0];
  auto idx1_a = search(val1, mIndexArray[0]);
  auto idx1_b = idx1_a + 1;
  double x0 = mIndexArray[0][idx1_a];
  double x1 = mIndexArray[0][idx1_b];

  double val2 = val_array[1];
  auto idx2_a = search(val2, mIndexArray[1]);
  auto idx2_b = idx2_a + 1;
  double y0 = mIndexArray[1][idx2_a];
  double y1 = mIndexArray[1][idx2_b];

  double val3 = val_array[2];
  auto idx3_a = search(val3, mIndexArray[2]);
  auto idx3_b = idx3_a + 1;
  double z0 = mIndexArray[2][idx3_a];
  double z1 = mIndexArray[2][idx3_b];

  // 単純な線形補間
  double wx  = x1 - x0;
  double dx0 = (val1 - x0) / wx;
  double dx1 = (x1 - val1) / wx;
  double wy  = y1 - y0;
  double dy0 = (val2 - y0) / wy;
  double dy1 = (y1 - val2) / wy;
  double wz  = z1 - z0;
  double dz0 = (val3 - z0) / wz;
  double dz1 = (z1 - val3) / wz;
  double val_000 = mValueArray[idx(idx1_a, idx2_a, idx3_a)];
  double val_001 = mValueArray[idx(idx1_a, idx2_a, idx3_b)];
  double val_010 = mValueArray[idx(idx1_a, idx2_b, idx3_a)];
  double val_011 = mValueArray[idx(idx1_a, idx2_b, idx3_b)];
  double val_100 = mValueArray[idx(idx1_b, idx2_a, idx3_a)];
  double val_101 = mValueArray[idx(idx1_b, idx2_a, idx3_b)];
  double val_110 = mValueArray[idx(idx1_b, idx2_b, idx3_a)];
  double val_111 = mValueArray[idx(idx1_b, idx2_b, idx3_b)];

  return dx1 * (dy1 * (dz1 * val_000 + dz0 * val_001) +
		dy0 * (dz1 * val_010 + dz0 * val_011)) +
         dx0 * (dy1 * (dz1 * val_100 + dz0 * val_101) +
		dy0 * (dz1 * val_110 + dz0 * val_111));
}

END_NAMESPACE_YM_CLIB
