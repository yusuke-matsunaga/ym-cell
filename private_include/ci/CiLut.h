#ifndef CILUT_H
#define CILUT_H

/// @file　CiLut.h
/// @brief CiLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibLut.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLut CiLut.h "CiLut.h"
/// @brief ルックアップテーブルの実装クラスの基底クラス
//////////////////////////////////////////////////////////////////////
class CiLut :
  public ClibLut
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiLut(const ClibLutTemplate* lut_template);

  /// @brief デストラクタ
  ~CiLut();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレートの取得
  const ClibLutTemplate&
  lut_template() const override;

  /// @brief テンプレート名の取得
  const char*
  template_name() const override;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  ClibVarType
  variable_type(int var) const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  void
  dump(ODO& s) const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief val に対応する区間を求める．
  static
  int
  search(double val,
	 const vector<double>& index_array);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート
  const ClibLutTemplate* mTemplate;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLut1D CiLut.h "CiLut.h"
/// @brief 1次元のルックアップテーブルを表すクラス
//////////////////////////////////////////////////////////////////////
class CiLut1D :
  public CiLut
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLut1D(const ClibLutTemplate* lut_template,
	  const vector<double>& value_array,
	  const vector<double>& index_array = vector<double>());

  /// @brief デストラクタ
  ~CiLut1D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief インデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;

  /// @brief 格子点の値の取得
  /// @param[in] pos_array 格子点座標
  /// @note pos_array のサイズは dimension() と同じ
  double
  grid_value(const vector<int>& pos_array) const override;

  /// @brief 値の取得
  /// @param[in] val_array 入力の値の配列
  /// @note val_array のサイズは dimension() と同じ
  double
  value(const vector<double>& val_array) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // インデックスの配列
  vector<double> mIndexArray;

  // インデックスの間隔の配列
  vector<double> mIndexWidthArray;

  // 格子点の値の配列
  vector<double> mValueArray;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLut2D CiLut.h "CiLut.h"
/// @brief 2次元のルックアップテーブルを表すクラス
//////////////////////////////////////////////////////////////////////
class CiLut2D :
  public CiLut
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLut2D(const ClibLutTemplate* lut_template,
	  const vector<double>& value_array,
	  const vector<double>& index_array1 = vector<double>(),
	  const vector<double>& index_array2 = vector<double>());

  /// @brief デストラクタ
  ~CiLut2D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief インデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;

  /// @brief 格子点の値の取得
  /// @param[in] pos_array 格子点座標
  /// @note pos_array のサイズは dimension() と同じ
  double
  grid_value(const vector<int>& pos_array) const override;

  /// @brief 値の取得
  /// @param[in] val_array 入力の値の配列
  /// @note val_array のサイズは dimension() と同じ
  double
  value(const vector<double>& val_array) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  /// @param[in] idx1 1番めのインデックス
  /// @param[in] idx2 2番めのインデックス
  int
  idx(int idx1,
      int idx2) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート
  const ClibLutTemplate* mTemplate;

  // インデックスの配列の配列
  vector<double> mIndexArray[2];

  // インデックスの間隔の配列
  vector<double> mIndexWidthArray[2];

  // 格子点の値の配列
  vector<double> mValueArray;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLut3D CiLut.h "CiLut.h"
/// @brief 3次元のルックアップテーブルを表すクラス
//////////////////////////////////////////////////////////////////////
class CiLut3D :
  public CiLut
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLut3D(const ClibLutTemplate* lut_template,
	  const vector<double>& value_array,
	  const vector<double>& index_array1 = vector<double>(),
	  const vector<double>& index_array2 = vector<double>(),
	  const vector<double>& index_array3 = vector<double>());

  /// @brief デストラクタ
  virtual
  ~CiLut3D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief インデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;

  /// @brief 格子点の値の取得
  /// @param[in] pos_array 格子点座標
  /// @note pos_array のサイズは dimension() と同じ
  double
  grid_value(const vector<int>& pos_array) const override;

  /// @brief 値の取得
  /// @param[in] val_array 入力の値の配列
  /// @note val_array のサイズは dimension() と同じ
  double
  value(const vector<double>& val_array) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  /// @param[in] idx1 1番めのインデックス
  /// @param[in] idx2 2番めのインデックス
  /// @param[in] idx3 3番めのインデックス
  int
  idx(int idx1,
      int idx2,
      int idx3) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート
  const ClibLutTemplate* mTemplate;

  // インデックスの配列の配列
  vector<double> mIndexArray[3];

  // インデックスの間隔の配列
  vector<double> mIndexWidthArray[3];

  // 格子点の値の配列
  vector<double> mValueArray;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief mValueArray のインデックスを計算する．
// @param[in] idx1 1番めのインデックス
// @param[in] idx2 2番めのインデックス
inline
int
CiLut2D::idx(int idx1,
	     int idx2) const
{
  return idx1 * index_num(1) + idx2;
}

// @brief mValueArray のインデックスを計算する．
// @param[in] idx1 1番めのインデックス
// @param[in] idx2 2番めのインデックス
// @param[in] idx3 3番めのインデックス
inline
int
CiLut3D::idx(int idx1,
	     int idx2,
	     int idx3) const
{
  return ((idx1 * index_num(1) + idx2) * index_num(2)) + idx3;
}

END_NAMESPACE_YM_CLIB

#endif // CILUT_H
