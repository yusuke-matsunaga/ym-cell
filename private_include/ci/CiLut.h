#ifndef CILUT_H
#define CILUT_H

/// @file　CiLut.h
/// @brief CiLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
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
  CiLut(
    const ClibLutTemplate* lut_template ///< [in] テンプレート
  );

  /// @brief デストラクタ
  ~CiLut();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレートの取得
  const ClibLutTemplate&
  lut_template() const override;

  /// @brief テンプレート番号の取得
  int
  template_id() const override;

  /// @brief 変数型の取得
  ClibVarType
  variable_type(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス数の取得
  int
  index_num(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief val に対応する区間を求める．
  static
  int
  search(
    double val,
    const vector<double>& index_array
  );


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
  CiLut1D(
    const ClibLutTemplate* lut_template,                 ///< [in] テンプレート
    const vector<double>& value_array,                   ///< [in] 値のリスト
    const vector<double>& index_array = vector<double>() ///< [in] インデックスのリスト
  );

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
  int
  index_num(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  double
  grid_value(
    const vector<int>& pos_array ///< [in] 格子点座標
  ) const override;

  /// @brief 値の取得
  ///
  /// val_array のサイズは dimension() と同じ
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
  ) const override;


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
  CiLut2D(
    const ClibLutTemplate* lut_template,                   ///< [in] テンプレート
    const vector<double>& value_array,                     ///< [in] 値の配列
    const vector<double>& index_array1 = vector<double>{}, ///< [in] インデックス1の配列
    const vector<double>& index_array2 = vector<double>{}  ///< [in] インデックス2の配列
  );

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
  int
  index_num(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  double
  grid_value(
    const vector<int>& pos_array ///< [in] 格子点座標
  ) const override;

  /// @brief 値の取得
  ///
  /// val_array のサイズは dimension() と同じ
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  int
  idx(
    int idx1, ///< [in] 1番めのインデックス
    int idx2  ///< [in] 2番めのインデックス
  ) const
  {
    return idx1 * index_num(1) + idx2;
  }


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
  CiLut3D(
    const ClibLutTemplate* lut_template,                   ///< [in] テンプレート
    const vector<double>& value_array,                     ///< [in] 値の配列
    const vector<double>& index_array1 = vector<double>{}, ///< [in] インデックス1の配列
    const vector<double>& index_array2 = vector<double>{}, ///< [in] インデックス2の配列
    const vector<double>& index_array3 = vector<double>{}  ///< [in] インデックス3の配列
  );

  /// @brief デストラクタ
  ~CiLut3D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief インデックス数の取得
  int
  index_num(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  double
  grid_value(
    const vector<int>& pos_array ///< [in] 格子点座標
  ) const override;

  /// @brief 値の取得
  ///
  /// val_array のサイズは dimension() と同じ
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  int
  idx(
    int idx1, ///< [in] 1番めのインデックス
    int idx2, ///< [in] 2番めのインデックス
    int idx3  ///< [in] 3番めのインデックス
  ) const
  {
    return ((idx1 * index_num(1) + idx2) * index_num(2)) + idx3;
  }


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

END_NAMESPACE_YM_CLIB

#endif // CILUT_H
