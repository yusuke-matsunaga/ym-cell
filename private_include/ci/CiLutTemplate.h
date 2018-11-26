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
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiLutTemplate(ShString name);

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
  _name() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  void
  dump(ODO& s) const override;


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
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  ClibVarType
  variable_type(int var) const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;

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
  ~CiLutTemplate1D();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  ClibVarType
  variable_type(int var) const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;


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
  ~CiLutTemplate2D();


public:

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  ClibVarType
  variable_type(int var) const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;


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
  ~CiLutTemplate3D();


public:

  /// @brief 次元数の取得
  int
  dimension() const override;

  /// @brief 変数型の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  ClibVarType
  variable_type(int var) const override;

  /// @brief インデックス数の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  int
  index_num(int var) const override;

  /// @brief デフォルトインデックス値の取得
  /// @param[in] var 変数番号 ( 0 <= var < dimension() )
  /// @param[in] pos 位置番号 ( 0 <= pos < index_num(var) )
  double
  index(int var,
	int pos) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 変数の型
  ClibVarType mVarType[3];

  // デフォルトインデックス値の配列
  vector<double> mIndexArray[3];

};

// @brief 名前の取得
inline
ShString
CiLutTemplate::_name() const
{
  return mName;
}

END_NAMESPACE_YM_CLIB

#endif // CILUTTEMPLATE_H
