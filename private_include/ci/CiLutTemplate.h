#ifndef CILUTTEMPLATE_H
#define CILUTTEMPLATE_H

/// @file　CiLutTemplate.h
/// @brief CiLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
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
  friend class CiLutHash;

protected:

  /// @brief コンストラクタ
  CiLutTemplate(ShString name);

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  const char*
  name() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // ハッシュ用のリンク
  CiLutTemplate* mLink;

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
  CiLutTemplate1D(ShString name,
		  ClibVarType var_type,
		  const vector<double>& index_array);

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate1D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  virtual
  int
  dimension() const;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  ClibVarType
  variable_type(int var) const;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  int
  index_num(int var) const;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  virtual
  double
  index(int var,
	int pos) const;


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
  CiLutTemplate2D(ShString name,
		  ClibVarType var1,
		  const vector<double>& index_array1,
		  ClibVarType var2,
		  const vector<double>& index_array2);

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate2D();


public:

  /// @brief 次元数の取得
  virtual
  int
  dimension() const;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  ClibVarType
  variable_type(int var) const;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  int
  index_num(int var) const;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  virtual
  double
  index(int var,
	int pos) const;


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
  CiLutTemplate3D(ShString name,
		  ClibVarType var1,
		  const vector<double>& index_array1,
		  ClibVarType var2,
		  const vector<double>& index_array2,
		  ClibVarType var3,
		  const vector<double>& index_array3);

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate3D();


public:

  /// @brief 次元数の取得
  virtual
  int
  dimension() const;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  ClibVarType
  variable_type(int var) const;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  virtual
  int
  index_num(int var) const;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  virtual
  double
  index(int var,
	int pos) const;


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
