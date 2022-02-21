#ifndef CILUT_H
#define CILUT_H

/// @file　CiLut.h
/// @brief CiLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLut.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLutBad CiLutBad.h "CiLutBad.h"
/// @brief エラー状態を表す CiLut の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLutBad :
  public ClibLut
{
public:

  /// @brief コンストラクタ
  CiLutBad() = default;

  /// @brief デストラクタ
  ~CiLutBad() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレートの取得
  const ClibLutTemplate&
  lut_template() const override;

  /// @brief 次元数の取得
  SizeType
  dimension() const override;

  /// @brief 変数型の取得
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] pos_array 格子点座標
  ) const override;

  /// @brief 値の取得
  ///
  /// @note val_array のサイズは dimension() と同じ
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;


};


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
  ) : mTemplate{lut_template}
  {
  }

public:

  /// @brief デストラクタ
  ~CiLut() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレートの取得
  const ClibLutTemplate&
  lut_template() const override;

  /// @brief 変数型の取得
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief val に対応する区間を求める．
  static
  SizeType
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
    const ClibLutTemplate* lut_template, ///< [in] テンプレート
    const vector<double>& value_array,   ///< [in] 値の配列
    const vector<double>& index_array    ///< [in] インデックスの配列
    = vector<double>{}
  );

  /// @brief デストラクタ
  ~CiLut1D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  SizeType
  dimension() const override;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] 格子点座標
                                      ///< サイズは dimension() と同じ
  ) const override;

  /// @brief 値の取得
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
                                    ///< サイズは dimension() と同じ
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
    const ClibLutTemplate* lut_template, ///< [in] テンプレート
    const vector<double>& value_array,   ///< [in] 値の配列
    const vector<double>& index_array1   ///< [in] 変数1のインデックスの配列
    = vector<double>{},
    const vector<double>& index_array2   ///< [in] 変数2のインデックスの配列
    = vector<double>{}
  );

  /// @brief デストラクタ
  ~CiLut2D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  SizeType
  dimension() const override;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] 格子点座標
                                      ///< サイズは dimension() と同じ
  ) const override;

  /// @brief 値の取得
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
                                    ///< サイズは dimension() と同じ
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  SizeType
  idx(
    SizeType idx1, ///< [in] 1番めのインデックス
    SizeType idx2  ///< [in] 2番めのインデックス
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
    const ClibLutTemplate* lut_template, ///< [in] テンプレート
    const vector<double>& value_array,   ///< [in] 値の配列
    const vector<double>& index_array1   ///< [in] 変数1のインデックスの配列
    = vector<double>{},
    const vector<double>& index_array2   ///< [in] 変数1のインデックスの配列
    = vector<double>{},
    const vector<double>& index_array3   ///< [in] 変数1のインデックスの配列
    = vector<double>{}
  );

  /// @brief デストラクタ
  ~CiLut3D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  SizeType
  dimension() const override;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const override;

  /// @brief インデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

  /// @brief 格子点の値の取得
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] 格子点座標
                                      ///< サイズは dimension() と同じ
  ) const override;

  /// @brief 値の取得
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
                                    ///< サイズは dimension() と同じ
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mValueArray のインデックスを計算する．
  SizeType
  idx(
    SizeType idx1, ///< [in] 1番めのインデックス
    SizeType idx2, ///< [in] 2番めのインデックス
    SizeType idx3  ///< [in] 3番めのインデックス
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
