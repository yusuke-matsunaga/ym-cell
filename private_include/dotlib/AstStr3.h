#ifndef ASTSTR3_H
#define ASTSTR3_H

/// @file AstStr3.h
/// @brief AstStr3 のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
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
  AstStr3(const StrStrStrHandler& handler); ///< [in] ハンドラ

  /// @brief デストラクタ
  ~AstStr3();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstString*
  value1() const
  {
    return mVal1;
  }

  /// @brief 値2を得る．
  const AstString*
  value2() const
  {
    return mVal2;
  }

  /// @brief 値3を得る．
  const AstString*
  value3() const
  {
    return mVal3;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


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

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTR3_H
