#ifndef ASTSTRFLOAT_H
#define ASTSTRFLOAT_H

/// @file AstStrFloat.h
/// @brief AstStrFloat のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstStrFloat AstStrFloat.h "dotlib/AstStrFloat.h"
/// @brief string, float のペアを表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstStrFloat :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] val1, val2 値
  AstStrFloat(const AstString* val1,
	      const AstFloat* val2);

  /// @brief デストラクタ
  ~AstStrFloat();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstString*
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
  const AstString* mVal1;

  // 値2
  const AstFloat* mVal2;

};

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値1を得る．
inline
const AstString*
AstStrFloat::val1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstFloat*
AstStrFloat::val2() const
{
  return mVal2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRFLOAT_H
