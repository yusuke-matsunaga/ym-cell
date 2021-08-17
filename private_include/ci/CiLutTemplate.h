#ifndef CILUTTEMPLATE_H
#define CILUTTEMPLATE_H

/// @file　CiLutTemplate.h
/// @brief CiLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLutTemplate.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate CiLutTemplate.h "CiLutTemplate.h"
/// @brief CiLutTemplateXXX の(擬似)基底クラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplate :
  public ClibLutTemplate
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiLutTemplate(
    ShString name ///< [in] 名前
  );

  /// @brief デストラクタ
  ~CiLutTemplate();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  int
  id() const override;

  /// @brief 名前の取得
  const char*
  name() const override;

  /// @brief 名前の取得
  ShString
  _name() const { return mName; }


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  int mId;

  // 名前
  ShString mName;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplateBad CiLutTemplate.h "CiLutTemplate.h"
/// @brief 不正なオブジェクトを表すクラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplateBad :
  public CiLutTemplate
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLutTemplateBad();

  /// @brief デストラクタ
  ~CiLutTemplateBad();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const override;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate1D CiLutTemplate.h "CiLutTemplate.h"
/// @brief 1次元のルックアップテーブルテンプレート
//////////////////////////////////////////////////////////////////////
class CiLutTemplate1D :
  public CiLutTemplate
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLutTemplate1D(
    ShString name,
    ClibVarType var_type,
    const vector<double>& index_array
  );

  /// @brief デストラクタ
  ~CiLutTemplate1D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLutTemplate2D(
    ShString name,                      ///< [in] 名前
    ClibVarType var1,                   ///< [in] 変数1の型
    const vector<double>& index_array1, ///< [in] インデックス1の配列
    ClibVarType var2,                   ///< [in] 変数2の型
    const vector<double>& index_array2  ///< [in] インデックス2の配列
  );

  /// @brief デストラクタ
  ~CiLutTemplate2D();


public:

  /// @brief 次元数の取得
  int
  dimension() const override;

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiLutTemplate3D(
    ShString name,                      ///< [in] 名前
    ClibVarType var1,                   ///< [in] 変数1の型
    const vector<double>& index_array1, ///< [in] インデックス1の配列
    ClibVarType var2,                   ///< [in] 変数2の型
    const vector<double>& index_array2, ///< [in] インデックス2の配列
    ClibVarType var3,                   ///< [in] 変数3の型
    const vector<double>& index_array3  ///< [in] インデックス3の配列
  );

  /// @brief デストラクタ
  ~CiLutTemplate3D();


public:

  /// @brief 次元数の取得
  int
  dimension() const override;

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

  /// @brief デフォルトインデックス値の取得
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
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
