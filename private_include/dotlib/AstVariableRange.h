#ifndef ASTVARIABLERANGE_H
#define ASTVARIABLERANGE_H

/// @file AstVariableRange.h
/// @brief AstVariableRange のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstVariableRange AstVariableRange.h "AstVariableRange.h"
/// @brief domain group 内の vairable_n_range 属性を表すクラス
//////////////////////////////////////////////////////////////////////
class AstVariableRange :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] val1, val2 値
  AstVariableRange(const AstFloat* val1,
		   const AstFloat* val2);

  /// @brief デストラクタ
  ~AstVariableRange();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstFloat*
  val1() const;

  /// @brief 値2を得る．
  const AstFloat*
  val2() const;

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

  // 値1
  const AstFloat* mVal1;

  // 値2
  const AstFloat* mVal2;

};

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値1を得る．
inline
const AstFloat*
AstVariableRange::val1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstFloat*
AstVariableRange::val2() const
{
  return mVal2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTVARIABLERANGE_H
