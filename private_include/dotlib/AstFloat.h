#ifndef ASTFLOAT_H
#define ASTFLOAT_H

/// @file AstFloat.h
/// @brief AstFloat のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloat AstFloat.h "AstFloat.h"
/// @brief 実数値を表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloat :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstFloat(const FileRegion& loc, ///< [in] ファイル上の位置
	   double value);         ///< [in] 値

  /// @brief デストラクタ
  ~AstFloat();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  ///
  /// type() が Float の時のみ意味を持つ．
  double
  value() const
  {
    return mValue;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOAT_H
