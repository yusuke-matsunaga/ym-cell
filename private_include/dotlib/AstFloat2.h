#ifndef ASTFLOAT2_H
#define ASTFLOAT2_H

/// @file AstFloat2.h
/// @brief AstFloat2 のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloat2 AstFloat2.h "AstFloat2.h"
/// @brief float のペアを表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstFloat2 :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] handler ハンドラ
  AstFloat2(const FloatFloatHandler& handler);

  /// @brief デストラクタ
  ~AstFloat2();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstFloat*
  value1() const;

  /// @brief 値2を得る．
  const AstFloat*
  value2() const;

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
AstFloat2::value1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstFloat*
AstFloat2::value2() const
{
  return mVal2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOAT2_H
