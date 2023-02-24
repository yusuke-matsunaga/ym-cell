#ifndef CILUTTEMPLATE_H
#define CILUTTEMPLATE_H

/// @file　CiLutTemplate.h
/// @brief CiLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLutTemplate.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate CiLutTemplate.h "CiLutTemplate.h"
/// @brief CiLutTemplateXXX の(擬似)基底クラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplate
{
public:

  /// @brief コンストラクタ
  CiLutTemplate(
    SizeType id,  ///< [in] ID番号
    ShString name ///< [in] 名前
  ) : mId{id},
      mName{name}
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

  /// @brief 名前の取得
  string
  name() const
  {
    return mName;
  }

  /// @brief 名前の取得
  ShString
  _name() const
  {
    return mName;
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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  SizeType mId;

  // 名前
  ShString mName;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate1D CiLutTemplate.h "CiLutTemplate.h"
/// @brief 1次元のルックアップテーブルテンプレート
//////////////////////////////////////////////////////////////////////
class CiLutTemplate1D :
  public CiLutTemplate
{
public:

  /// @brief コンストラクタ
  CiLutTemplate1D(
    SizeType id,
    ShString name,
    ClibVarType var_type,
    const vector<double>& index_array
  ) : CiLutTemplate{id, name},
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

  /// @brief コンストラクタ
  CiLutTemplate2D(
    SizeType id,
    ShString name,
    ClibVarType var1,
    const vector<double>& index_array1,
    ClibVarType var2,
    const vector<double>& index_array2
  ) : CiLutTemplate{id, name},
      mVarType{var1, var2},
      mIndexArray{index_array1, index_array2}
  {
  }

  /// @brief デストラクタ
  ~CiLutTemplate2D() = default;


public:

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

  /// @brief コンストラクタ
  CiLutTemplate3D(
    SizeType id,
    ShString name,
    ClibVarType var1,
    const vector<double>& index_array1,
    ClibVarType var2,
    const vector<double>& index_array2,
    ClibVarType var3,
    const vector<double>& index_array3
  ) : CiLutTemplate{id, name},
      mVarType{var1, var2, var3},
      mIndexArray{index_array1, index_array2, index_array3}
  {
  }

  /// @brief デストラクタ
  ~CiLutTemplate3D() = default;


public:

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
