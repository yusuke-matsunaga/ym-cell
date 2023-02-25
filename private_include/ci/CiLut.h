#ifndef CILUT_H
#define CILUT_H

/// @file　CiLut.h
/// @brief CiLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/BinEnc.h"
#include "ym/BinDec.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLut CiLut.h "CiLut.h"
/// @brief ルックアップテーブルの実装クラスの基底クラス
//////////////////////////////////////////////////////////////////////
class CiLut
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLut() = default;

  /// @brief コンストラクタ
  CiLut(
    SizeType lut_template ///< [in] テンプレート番号
  ) : mTemplate{lut_template}
  {
  }

  /// @brief デストラクタ
  virtual
  ~CiLut() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレート番号の取得
  SizeType
  lut_template() const
  {
    return mTemplate;
  }

  /// @brief インデックス数の取得
  virtual
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief インデックス値の取得
  virtual
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const = 0;

  /// @brief 格子点の値の取得
  virtual
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] 格子点座標
                                      ///< サイズは dimension() と同じ
  ) const = 0;

  /// @brief 値の取得
  virtual
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
                                    ///< サイズは dimension() と同じ
  ) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const = 0;

  /// @brief 内容を読み込む．
  virtual
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 実際のダンプを行う関数
  void
  dump_common(
    BinEnc& s, ///< [in] 出力先のストリーム
    ymuint8 d  ///< [in] 次元数
  ) const;

  /// @brief 内容を読み込む．
  void
  restore_common(
    BinDec& s ///< [in] 入力元のストリーム
  )
  {
    s >> mTemplate;
  }

  /// @brief mIndexWidthArray を初期化する．
  static
  void
  init(
    const vector<double>& index_array,
    vector<double>& index_width_array
  );

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

  // テンプレート番号
  SizeType mTemplate{CLIB_NULLID};

};


//////////////////////////////////////////////////////////////////////
/// @class CiLut1D CiLut.h "CiLut.h"
/// @brief 1次元のルックアップテーブルを表すクラス
//////////////////////////////////////////////////////////////////////
class CiLut1D :
  public CiLut
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLut1D() = default;

  /// @brief コンストラクタ
  CiLut1D(
    SizeType lut_template,             ///< [in] テンプレート番号
    const vector<double>& value_array, ///< [in] 値の配列
    const vector<double>& index_array  ///< [in] インデックスの配列
  );

  /// @brief デストラクタ
  ~CiLut1D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

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


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mIndexWidthArray を初期化する．
  void
  init()
  {
    CiLut::init(mIndexArray, mIndexWidthArray);
  }


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
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLut2D() = default;

  /// @brief コンストラクタ
  CiLut2D(
    SizeType lut_template,              ///< [in] テンプレート番号
    const vector<double>& value_array,  ///< [in] 値の配列
    const vector<double>& index_array1, ///< [in] 変数1のインデックスの配列
    const vector<double>& index_array2  ///< [in] 変数2のインデックスの配列
  );

  /// @brief デストラクタ
  ~CiLut2D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

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


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mIndexWidthArray を初期化する．
  void
  init()
  {
    for ( SizeType i = 0; i < 2; ++ i ) {
      CiLut::init(mIndexArray[i], mIndexWidthArray[i]);
    }
  }

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
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLut3D() = default;

  /// @brief コンストラクタ
  CiLut3D(
    SizeType lut_template,              ///< [in] テンプレート番号
    const vector<double>& value_array,  ///< [in] 値の配列
    const vector<double>& index_array1, ///< [in] 変数1のインデックスの配列
    const vector<double>& index_array2, ///< [in] 変数1のインデックスの配列
    const vector<double>& index_array3  ///< [in] 変数1のインデックスの配列
  );

  /// @brief デストラクタ
  ~CiLut3D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

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


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mIndexWidthArray を初期化する．
  void
  init()
  {
    for ( SizeType i = 0; i < 3; ++ i ) {
      CiLut::init(mIndexArray[i], mIndexWidthArray[i]);
    }
  }

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

  // インデックスの配列の配列
  vector<double> mIndexArray[3];

  // インデックスの間隔の配列
  vector<double> mIndexWidthArray[3];

  // 格子点の値の配列
  vector<double> mValueArray;

};

END_NAMESPACE_YM_CLIB

#endif // CILUT_H
