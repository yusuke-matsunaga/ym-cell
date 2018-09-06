#ifndef ASTDOMAIN_H
#define ASTDOMAIN_H

/// @file AstDomain.h
/// @brief AstDomain のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstDomain AstDomain.h "AstDomain.h"
/// @brief domain group statement を表すクラス
//////////////////////////////////////////////////////////////////////
class AstDomain :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] calc_mode calc_mode 属性
  /// @param[in] coefs coefs 属性
  /// @param[in] orders orders 属性
  /// @param[in] var1_range variable_1_range 属性
  /// @param[in] var2_range variable_2_range 属性
  /// @param[in] var3_range variable_3_range 属性
  AstDomain(const FileRegion& loc,
	    const AstString* name,
	    const AstString* calc_mode,
	    const AstString* coefs,
	    const AstString* orders,
	    const AstVariableRange* var1_range,
	    const AstVariableRange* var2_range,
	    const AstVariableRange* var3_range);


  /// @brief デストラクタ
  ~AstDomain();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief calc_mode 属性を返す．
  const AstString*
  calc_mode() const;

  /// @brief coefs 属性を返す．
  const AstString*
  coefs() const;

  /// @brief orders 属性を返す．
  const AstString*
  orders() const;

  /// @brief variable_1_range 属性を返す．
  const AstVariableRange*
  variable_1_range() const;

  /// @brief variable_2_range 属性を返す．
  const AstVariableRange*
  variable_2_range() const;

  /// @brief variable_3_range 属性を返す．
  const AstVariableRange*
  variable_3_range() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const AstString* mName;

  // calc_mode 属性
  const AstString* mCalcMode;

  // coefs 属性
  const AstString* mCoefs;

  // orders 属性
  const AstString* mOrders;

  // variable_1_range 属性
  const AstVariableRange* mVar1Range;

  // variable_2_range 属性
  const AstVariableRange* mVar2Range;

  // variable_3_range 属性
  const AstVariableRange* mVar3Range;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstDomain::name() const
{
  return mName;
}

// @brief calc_mode 属性を返す．
inline
const AstString*
AstDomain::calc_mode() const
{
  return mCalcMode;
}

// @brief coefs 属性を返す．
inline
const AstString*
AstDomain::coefs() const
{
  return mCoefs;
}

// @brief orders 属性を返す．
inline
const AstString*
AstDomain::orders() const
{
  return mOrders;
}

// @brief variable_1_range 属性を返す．
inline
const AstVariableRange*
AstDomain::variable_1_range() const
{
  return mVar1Range;
}

// @brief variable_2_range 属性を返す．
inline
const AstVariableRange*
AstDomain::variable_2_range() const
{
  return mVar2Range;
}

// @brief variable_3_range 属性を返す．
inline
const AstVariableRange*
AstDomain::variable_3_range() const
{
  return mVar3Range;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTDOMAIN_H
