﻿
/// @file CiLut.cc
/// @brief CiLut の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiLut.h"
#include "ci/CiLutTemplate.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLut::CiLut(const ClibLutTemplate* lut_template) :
  mTemplate(lut_template)
{
}

// @brief デストラクタ
CiLut::~CiLut()
{
}

// @brief テンプレートの取得
const ClibLutTemplate&
CiLut::lut_template() const
{
  return *mTemplate;
}

// @brief テンプレート番号の取得
int
CiLut::template_id() const
{
  return lut_template().id();
}

// @brief 変数型の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
ClibVarType
CiLut::variable_type(int var) const
{
  return lut_template().variable_type(var);
}

// @brief インデックス数の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
int
CiLut::index_num(int var) const
{
  return lut_template().index_num(var);
}

// @brief val に対応する区間を求める．
int
CiLut::search(double val,
	      const vector<double>& index_array)
{
  int n = index_array.size();

  if ( val <= index_array[0] ) {
    // 値が小さすぎる時は [0, 1] を返す．
    return 0;
  }
  if ( val >= index_array[n - 1] ) {
    // 値が大きすぎる時は [n - 2, n - 1] を返す．
    return n - 2;
  }
  // 単純な線形探索を行う．
  for ( int i: Range(n - 1) ) {
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
CiLut1D::CiLut1D(const ClibLutTemplate* lut_template,
		 const vector<double>& value_array,
		 const vector<double>& index_array) :
  CiLut(lut_template)
{
  int n = 0;
  if ( index_array.empty() ) {
    n = lut_template->index_num(0);
    mIndexArray.resize(n);
    for ( int i: Range(n) ) {
      mIndexArray[i] = lut_template->index(0, i);
    }
  }
  else {
    n = index_array.size();
    mIndexArray.resize(n);
    for ( int i: Range(n) ) {
      mIndexArray[i] = index_array[i];
    }
  }
  ASSERT_COND( n != 0 );
  mIndexWidthArray.resize(n - 1);
  for ( int i: Range(n - 1) ) {
    mIndexWidthArray[i] = mIndexArray[i + 1] - mIndexArray[i];
  }

  ASSERT_COND( value_array.size() == n );
  mValueArray.resize(n);
  for ( int i: Range(n) ) {
    mValueArray[i] = value_array[i];
  }
}

// @brief デストラクタ
CiLut1D::~CiLut1D()
{
}

// @brief 次元数の取得
int
CiLut1D::dimension() const
{
  return 1;
}

// @brief インデックス数の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
int
CiLut1D::index_num(int var) const
{
  ASSERT_COND( var < 1  );
  return mIndexArray.size();
}

// @brief インデックス値の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
double
CiLut1D::index(int var,
	       int pos) const
{
  ASSERT_COND( var < 1  );
  ASSERT_COND( pos < index_num(var)  );
  return mIndexArray[pos];
}

// @brief 格子点の値の取得
// @param[in] pos_array 格子点座標
// @note pos_array のサイズは dimension() と同じ
double
CiLut1D::grid_value(const vector<int>& pos_array) const
{
  ASSERT_COND( pos_array.size() == 1 );
  int pos1 = pos_array[0];
  ASSERT_COND( pos1 < index_num(0) );
  return mValueArray[pos1];
}

// @brief 値の取得
// @param[in] val_array 入力の値の配列
// @note val_array のサイズは dimension() と同じ
double
CiLut1D::value(const vector<double>& val_array) const
{
  ASSERT_COND( val_array.size() == 1 );

  double val = val_array[0];

  int idx_a = search(val, mIndexArray);
  int idx_b = idx_a + 1;
  double x0 = mIndexArray[idx_a];
  double x1 = mIndexArray[idx_b];
  double w  = mIndexWidthArray[idx_a];
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
CiLut2D::CiLut2D(const ClibLutTemplate* lut_template,
		 const vector<double>& value_array,
		 const vector<double>& index_array1,
		 const vector<double>& index_array2) :
  CiLut(lut_template)
{
  int n1 = 0;
  if ( index_array1.empty() ) {
    n1 = lut_template->index_num(0);
    mIndexArray[0].resize(n1);
    for ( int i: Range(n1) ) {
      mIndexArray[0][i] = lut_template->index(0, i);
    }
  }
  else {
    n1 = index_array1.size();
    mIndexArray[0].resize(n1);
    for ( int i: Range(n1) ) {
      mIndexArray[0][i] = index_array1[i];
    }
  }
  ASSERT_COND( n1 != 0 );
  mIndexWidthArray[0].resize(n1 - 1);
  for ( int i: Range(n1 - 1) ) {
    mIndexWidthArray[0][i] = mIndexArray[0][i + 1] - mIndexArray[0][i];
  }

  int n2 = 0;
  if ( index_array2.empty() ) {
    n2 = lut_template->index_num(1);
    mIndexArray[1].resize(n2);
    for ( int i: Range(n2) ) {
      mIndexArray[1][i] = lut_template->index(1, i);
    }
  }
  else {
    n2 = index_array2.size();
    mIndexArray[1].resize(n2);
    for ( int i: Range(n2) ) {
      mIndexArray[1][i] = index_array2[i];
    }
  }
  ASSERT_COND( n2 != 0 );
  mIndexWidthArray[1].resize(n2 - 1);
  for ( int i: Range(n2 - 1) ) {
    mIndexWidthArray[1][i] = mIndexArray[1][i + 1] - mIndexArray[1][i];
  }

  int n = n1 * n2;
  ASSERT_COND( value_array.size() == n );
  mValueArray.resize(n);
  for ( int i: Range(n) ) {
    mValueArray[i] = value_array[i];
  }
}

// @brief デストラクタ
CiLut2D::~CiLut2D()
{
}

// @brief 次元数の取得
int
CiLut2D::dimension() const
{
  return 2;
}

// @brief インデックス数の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
int
CiLut2D::index_num(int var) const
{
  ASSERT_COND( var < 2 );
  return mIndexArray[var].size();
}

// @brief インデックス値の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
double
CiLut2D::index(int var,
	       int pos) const
{
  ASSERT_COND( var < 2 );
  ASSERT_COND( pos < index_num(var) );
  return mIndexArray[var][pos];
}

// @brief 格子点の値の取得
// @param[in] pos_array 格子点座標
// @note pos_array のサイズは dimension() と同じ
double
CiLut2D::grid_value(const vector<int>& pos_array) const
{
  ASSERT_COND( pos_array.size() == 2 );
  int pos1 = pos_array[0];
  int pos2 = pos_array[1];
  ASSERT_COND( pos1 < index_num(0) );
  ASSERT_COND( pos2 < index_num(1) );
  return mValueArray[idx(pos1, pos2)];
}

// @brief 値の取得
// @param[in] val_array 入力の値の配列
// @note val_array のサイズは dimension() と同じ
double
CiLut2D::value(const vector<double>& val_array) const
{
  ASSERT_COND( val_array.size() == 2 );

  double val1 = val_array[0];
  int idx1_a = search(val1, mIndexArray[0]);
  int idx1_b = idx1_a + 1;
  double x0 = mIndexArray[0][idx1_a];
  double x1 = mIndexArray[0][idx1_b];

  double val2 = val_array[1];
  int idx2_a = search(val2, mIndexArray[1]);
  int idx2_b = idx2_a + 1;
  double y0 = mIndexArray[1][idx2_a];
  double y1 = mIndexArray[1][idx2_b];

  // 単純な線形補間
  double wx  = mIndexWidthArray[0][idx1_a];
  double dx0 = (val1 - x0) / wx;
  double dx1 = (x1 - val1) / wx;
  double wy  = mIndexWidthArray[1][idx2_a];
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
CiLut3D::CiLut3D(const ClibLutTemplate* lut_template,
		 const vector<double>& value_array,
		 const vector<double>& index_array1,
		 const vector<double>& index_array2,
		 const vector<double>& index_array3) :
  CiLut(lut_template)
{
  int n1 = 0;
  if ( index_array1.empty() ) {
    n1 = lut_template->index_num(0);
    mIndexArray[0].resize(n1);
    for ( int i: Range(n1) ) {
      mIndexArray[0][i] = lut_template->index(0, i);
    }
  }
  else {
    n1 = index_array1.size();
    mIndexArray[0].resize(n1);
    for ( int i: Range(n1) ) {
      mIndexArray[0][i] = index_array1[i];
    }
  }
  ASSERT_COND( n1 != 0 );
  mIndexWidthArray[0].resize(n1 - 1);
  for ( int i: Range(n1 - 1) ) {
    mIndexWidthArray[0][i] = mIndexArray[0][i + 1] - mIndexArray[0][i];
  }

  int n2 = 0;
  if ( index_array2.empty() ) {
    n2 = lut_template->index_num(1);
    mIndexArray[1].resize(n2);
    for ( int i: Range(n2) ) {
      mIndexArray[1][i] = lut_template->index(1, i);
    }
  }
  else {
    n2 = index_array2.size();
    mIndexArray[1].resize(n2);
    for ( int i: Range(n2) ) {
      mIndexArray[1][i] = index_array2[i];
    }
  }
  ASSERT_COND( n2 != 0 );
  mIndexWidthArray[1].resize(n2 - 1);
  for ( int i: Range(n2 - 1) ) {
    mIndexWidthArray[1][i] = mIndexArray[1][i + 1] - mIndexArray[1][i];
  }

  int n3 = 0;
  if ( index_array3.empty() ) {
    n3 = lut_template->index_num(2);
    mIndexArray[2].resize(n3);
    for ( int i: Range(n3) ) {
      mIndexArray[2][i] = lut_template->index(2, i);
    }
  }
  else {
    n3 = index_array3.size();
    mIndexArray[2].resize(n3);
    for ( int i: Range(n3) ) {
      mIndexArray[2][i] = index_array3[i];
    }
  }
  ASSERT_COND( n3 != 0 );
  mIndexWidthArray[2].resize(n3 - 1);
  for ( int i: Range(n3 - 1) ) {
    mIndexWidthArray[2][i] = mIndexArray[2][i + 1] - mIndexArray[2][i];
  }

  int n = n1 * n2 * n3;
  ASSERT_COND( value_array.size() == n );
  mValueArray.resize(n);
  for ( int i: Range(n) ) {
    mValueArray[i] = value_array[i];
  }
}

// @brief デストラクタ
CiLut3D::~CiLut3D()
{
}

// @brief 次元数の取得
int
CiLut3D::dimension() const
{
  return 3;
}

// @brief インデックス数の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
int
CiLut3D::index_num(int var) const
{
  ASSERT_COND( var < 3 );
  return mIndexArray[var].size();
}

// @brief インデックス値の取得
// @param[in] var 変数番号 ( 0 <= var < dimension() )
// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
double
CiLut3D::index(int var,
	       int pos) const
{
  ASSERT_COND( var < 3 );
  ASSERT_COND( pos < index_num(var) );
  return mIndexArray[var][pos];
}

// @brief 格子点の値の取得
// @param[in] pos_array 格子点座標
// @note pos_array のサイズは dimension() と同じ
double
CiLut3D::grid_value(const vector<int>& pos_array) const
{
  ASSERT_COND( pos_array.size() == 3 );
  int pos1 = pos_array[0];
  int pos2 = pos_array[1];
  int pos3 = pos_array[2];
  ASSERT_COND( pos1 < index_num(0) );
  ASSERT_COND( pos2 < index_num(1) );
  ASSERT_COND( pos3 < index_num(2) );
  return mValueArray[idx(pos1, pos2, pos3)];
}

// @brief 値の取得
// @param[in] val_array 入力の値の配列
// @note val_array のサイズは dimension() と同じ
double
CiLut3D::value(const vector<double>& val_array) const
{
  ASSERT_COND( val_array.size() == 3 );
  double val1 = val_array[0];
  int idx1_a = search(val1, mIndexArray[0]);
  int idx1_b = idx1_a + 1;
  double x0 = mIndexArray[0][idx1_a];
  double x1 = mIndexArray[0][idx1_b];

  double val2 = val_array[1];
  int idx2_a = search(val2, mIndexArray[1]);
  int idx2_b = idx2_a + 1;
  double y0 = mIndexArray[1][idx2_a];
  double y1 = mIndexArray[1][idx2_b];

  double val3 = val_array[2];
  int idx3_a = search(val3, mIndexArray[2]);
  int idx3_b = idx3_a + 1;
  double z0 = mIndexArray[2][idx3_a];
  double z1 = mIndexArray[2][idx3_b];

  // 単純な線形補間
  double wx  = mIndexWidthArray[0][idx1_a];
  double dx0 = (val1 - x0) / wx;
  double dx1 = (x1 - val1) / wx;
  double wy  = mIndexWidthArray[1][idx2_a];
  double dy0 = (val2 - y0) / wy;
  double dy1 = (y1 - val2) / wy;
  double wz  = mIndexWidthArray[2][idx3_a];
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
