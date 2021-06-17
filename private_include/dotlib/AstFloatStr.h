#ifndef ASTFLOATSTR_H
#define ASTFLOATSTR_H

/// @file AstFloatStr.h
/// @brief AstFloatStr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloatStr AstFloatStr.h "dotlib/AstFloatStr.h"
/// @brief float, string のペアを表す AstNode の派生クラス
//////////////////////////////////////////////////////////////////////
class AstFloatStr :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstFloatStr(const AstFloat* value1,   ///< [in] 値1
	      const AstString* value2); ///< [in] 値2

  /// @brief デストラクタ
  ~AstFloatStr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値1を得る．
  const AstFloat*
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

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,      ///< [in] 出力先のストリーム
       int indent = 0)  ///< [in] インデント量
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
  const AstFloat* mVal1;

  // 値2
  const AstString* mVal2;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOATSTR_H
