#ifndef ASTSTR3_H
#define ASTSTR3_H

/// @file AstStr3.h
/// @brief AstStr3 のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstStr3 AstStr3.h "dotlib/AstStr3.h"
/// @brief string, string, string の3つ組を表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstStr3 :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] handler ハンドラ
  AstStr3(const Str3Handler& handler);

  /// @brief デストラクタ
  ~AstStr3();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstString*
  value1() const;

  /// @brief 値2を得る．
  const AstString*
  value2() const;

  /// @brief 値3を得る．
  const AstString*
  value3() const;

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
  const AstString* mVal2;

  // 値3
  const AstString* mVal3;

};

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値1を得る．
inline
const AstString*
AstStr3::value1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstString*
AstStr3::value2() const
{
  return mVal2;
}

// @brief 値3を得る．
inline
const AstString*
AstStr3::value3() const
{
  return mVal3;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTR3_H
