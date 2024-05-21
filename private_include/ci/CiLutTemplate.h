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
#include "ci/CiLibObj.h"


BEGIN_NAMESPACE_YM_CLIB

class Serializer;
class Deserializer;

//////////////////////////////////////////////////////////////////////
/// @class CiLutTemplate CiLutTemplate.h "CiLutTemplate.h"
/// @brief CiLutTemplateXXX の(擬似)基底クラス
//////////////////////////////////////////////////////////////////////
class CiLutTemplate :
  public CiLibObj
{
public:

  /// @brief コンストラクタ
  CiLutTemplate(
    const CiCellLibrary* lib ///< [in] 親のライブラリ
  ) : CiLibObj{lib}
  {
  }

  /// @brief デストラクタ
  virtual
  ~CiLutTemplate() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

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

  /// @brief インデックス配列の取得
  virtual
  const vector<double>&
  index_array(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をシリアライズする．
  void
  serialize(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    Serializer& s ///< [in] シリアライザ
  ) const = 0;

  /// @brief 内容を復元する．
  static
  CiLutTemplate*
  restore(
    Deserializer& s,   ///< [in] デシリアライザ
    CiCellLibrary* lib ///< [in] 親のセルライブラリ
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1つの変数の情報をバイナリダンプする．
  static
  void
  dump_var(
    Serializer& s,                    ///< [in] シリアライザ
    ClibVarType var_type,             ///< [in] 変数のタイプ
    const vector<double>& index_array ///< [in] インデックスの配列
  );

};

END_NAMESPACE_YM_CLIB

#endif // CILUTTEMPLATE_H
