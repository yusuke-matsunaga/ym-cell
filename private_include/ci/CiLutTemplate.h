#ifndef CILUTTEMPLATE_H
#define CILUTTEMPLATE_H

/// @file　CiLutTemplate.h
/// @brief CiLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate CiLutTemplate.h "CiLutTemplate.h"
/// @brief CiLutTemplateXXX の(擬似)基底クラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplate
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLutTemplate() = default;

  /// @brief コンストラクタ
  CiLutTemplate(
    SizeType id ///< [in] ID番号
  ) : mId{id}
  {
  }

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  SizeType
  id() const
  {
    return mId;
  }

  /// @brief 次元数の取得
  virtual
  SizeType
  dimension() const = 0;

  /// @brief 変数型の取得
  virtual
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief インデックス数の取得
  virtual
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief デフォルトインデックス値の取得
  virtual
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  ) const;

  /// @brief 内容を読み込む．
  virtual
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1つの変数の情報をバイナリダンプする．
  static
  void
  dump_var(
    BinEnc& s,                        ///< [in] 出力先のストリーム
    ClibVarType var_type,             ///< [in] 変数のタイプ
    const vector<double>& index_array ///< [in] インデックスの配列
  );

  /// @brief 内容を読み込む．
  void
  restore_common(
    BinDec& s ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  SizeType mId;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate1D CiLutTemplate.h "CiLutTemplate.h"
/// @brief 1次元のルックアップテーブルテンプレート
//////////////////////////////////////////////////////////////////////
class CiLutTemplate1D :
  public CiLutTemplate
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLutTemplate1D() = default;

  /// @brief コンストラクタ
  CiLutTemplate1D(
    SizeType id,
    ClibVarType var_type,
    const vector<double>& index_array
  ) : CiLutTemplate{id/*, name*/},
      mVarType{var_type},
      mIndexArray{index_array}
  {
  }

  /// @brief デストラクタ
  ~CiLutTemplate1D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数の型
  ClibVarType mVarType;

  // デフォルトインデックス値の配列
  vector<double> mIndexArray;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate2D CiLutTemplate.h "CiLutTemplate.h"
/// @brief 2次元のルックアップテーブルテンプレート
//////////////////////////////////////////////////////////////////////
class CiLutTemplate2D :
  public CiLutTemplate
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLutTemplate2D() = default;

  /// @brief コンストラクタ
  CiLutTemplate2D(
    SizeType id,
    ClibVarType var1,
    const vector<double>& index_array1,
    ClibVarType var2,
    const vector<double>& index_array2
  ) : CiLutTemplate{id/*, name*/},
      mVarType{var1, var2},
      mIndexArray{index_array1, index_array2}
  {
  }

  /// @brief デストラクタ
  ~CiLutTemplate2D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数の型
  ClibVarType mVarType[2];

  // デフォルトインデックス値の配列
  vector<double> mIndexArray[2];

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate3D CiLutTemplate.h "CiLutTemplate.h"
/// @brief 3次元のルックアップテーブルテンプレート
//////////////////////////////////////////////////////////////////////
class CiLutTemplate3D :
  public CiLutTemplate
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiLutTemplate3D() = default;

  /// @brief コンストラクタ
  CiLutTemplate3D(
    SizeType id,
    ClibVarType var1,
    const vector<double>& index_array1,
    ClibVarType var2,
    const vector<double>& index_array2,
    ClibVarType var3,
    const vector<double>& index_array3
  ) : CiLutTemplate{id/*, name*/},
      mVarType{var1, var2, var3},
      mIndexArray{index_array1, index_array2, index_array3}
  {
  }

  /// @brief デストラクタ
  ~CiLutTemplate3D() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数の型
  ClibVarType mVarType[3];

  // デフォルトインデックス値の配列
  vector<double> mIndexArray[3];

};

END_NAMESPACE_YM_CLIB

#endif // CILUTTEMPLATE_H
