#ifndef ASTLUT_H
#define ASTLUT_H

/// @file AstLut.h
/// @brief AstLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLut AstLut.h "AstLut.h"
/// @brief lut 情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLut :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] index_1, index_2, index_3 インデックスのベクタ
  /// @param[in] value_list 値のリスト
  /// @param[in] coefs 'coefs' 属性
  /// @param[in] orders 'orders' 属性
  /// @param[in] variable_1_range, variable_2_range, variable_3_range 'variable_n_range' 属性
  /// @param[in] domain 'domain'
  AstLut(const FileRegion& loc,
	 const AstString* name,
	 const AstFloatVector* index_1,
	 const AstFloatVector* index_2,
	 const AstFloatVector* index_3,
	 const AstFloatVector* value_list,
	 const AstFloatVector* coefs,
	 const AstIntVector* orders,
	 const AstVariableRange* variable_1_range,
	 const AstVariableRange* variable_2_range,
	 const AstVariableRange* variable_3_range,
	 const AstDomain* domain);

  /// @brief デストラクタ
  ~AstLut();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレート名を返す．
  const AstString*
  name() const;

  /// @brief 'index_1' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_1() const;

  /// @brief 'index_2' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_2() const;

  /// @brief 'index_3' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstFloatVector*
  index_3() const;

  /// @brief 値のリストを返す．
  const AstFloatVector*
  value_list() const;

  /// @brief 'coefs' のノードを返す．
  const AstFloatVector*
  coefs() const;

  /// @brief 'orders' のノードを返す．
  const AstIntVector*
  orders() const;

  /// @brief 'variable_1_range' のノードを返す．
  const AstVariableRange*
  variable_1_range() const;

  /// @brief 'variable_2_range' のノードを返す．
  const AstVariableRange*
  variable_2_range() const;

  /// @brief 'variable_3_range' のノードを返す．
  const AstVariableRange*
  variable_3_range() const;

  /// @brief 'domain' のノードを返す．
  ///
  /// 未定義なら nullptr を返す．
  const AstDomain*
  domain() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート名
  const AstString* mName;

  // index_1
  const AstFloatVector* mIndex1;

  // index_2
  const AstFloatVector* mIndex2;

  // index_3
  const AstFloatVector* mIndex3;

  // 値のリスト
  const AstFloatVector* mValueList;

  // coefs
  const AstFloatVector* mCoefs;

  // orders
  const AstIntVector* mOrders;

  // variable_1_range
  const AstVariableRange* mVar1Range;

  // variable_2_range
  const AstVariableRange* mVar2Range;

  // variable_3_range
  const AstVariableRange* mVar3Range;

  // domain
  const AstDomain* mDomain;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief テンプレート名を返す．
inline
const AstString*
AstLut::name() const
{
  return mName;
}

 // @brief 'index_1' のノードを返す．
inline
const AstFloatVector*
AstLut::index_1() const
{
  return mIndex1;
}

// @brief 'index_2' のノードを返す．
inline
const AstFloatVector*
AstLut::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' のノードを返す．
inline
const AstFloatVector*
AstLut::index_3() const
{
  return mIndex3;
}

// @brief 値のリストを返す．
inline
const AstFloatVector*
AstLut::value_list() const
{
  return mValueList;
}

// @brief 'coefs' のノードを返す．
inline
const AstFloatVector*
AstLut::coefs() const
{
  return mCoefs;
}

// @brief 'orders' のノードを返す．
inline
const AstIntVector*
AstLut::orders() const
{
  return mOrders;
}

// @brief 'variable_1_range' のノードを返す．
inline
const AstVariableRange*
AstLut::variable_1_range() const
{
  return mVar1Range;
}

// @brief 'variable_2_range' のノードを返す．
inline
const AstVariableRange*
AstLut::variable_2_range() const
{
  return mVar2Range;
}

// @brief 'variable_3_range' のノードを返す．
inline
const AstVariableRange*
AstLut::variable_3_range() const
{
  return mVar3Range;
}

// @brief 'domain' のノードを返す．
//
// 未定義なら nullptr を返す．
inline
const AstDomain*
AstLut::domain() const
{
  return mDomain;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTLUT_H
