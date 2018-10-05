#ifndef ASTSTR2_H
#define ASTSTR2_H

/// @file AstStr2.h
/// @brief AstStr2 のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstStr2 AstStr2.h "dotlib/AstStr2.h"
/// @brief string, string のペアを表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstStr2 :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] handler ハンドラ
  AstStr2(const StrStrHandler& handler);

  /// @brief デストラクタ
  ~AstStr2();


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

};

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 値1を得る．
inline
const AstString*
AstStr2::value1() const
{
  return mVal1;
}

// @brief 値2を得る．
inline
const AstString*
AstStr2::value2() const
{
  return mVal2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTR2_H