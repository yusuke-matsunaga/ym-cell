#ifndef ASTSTRFLOAT_H
#define ASTSTRFLOAT_H

/// @file AstStrFloat.h
/// @brief AstStrFloat のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
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
  AstStrFloat(const StrFloatHandler& handler); ///< [in] ハンドラ

  /// @brief デストラクタ
  ~AstStrFloat();


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
  const AstFloat*
  value2() const
  {
    return mVal2;
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
  const AstFloat* mVal2;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRFLOAT_H
