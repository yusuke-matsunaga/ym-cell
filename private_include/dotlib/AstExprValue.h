#ifndef ASTEXPRVALUE_H
#define ASTEXPRVALUE_H

/// @file AstExprValue.h
/// @brief AstExprValue のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstExprValue AstExprValue.h "AstExprValue.h"
/// @brief AstExpr を持つ AstValue の派生クラス
//////////////////////////////////////////////////////////////////////
class AstExprValue :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstExprValue(const AstExpr* value); ///< [in] 値

  /// @brief デストラクタ
  ~AstExprValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief expr 型の値を返す．
  const AstExpr*
  expr_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  const AstExpr* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTINT_H
