#ifndef ASTINT_H
#define ASTINT_H

/// @file AstInt.h
/// @brief AstInt のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstInt AstInt.h "AstInt.h"
/// @brief 整数値を表すクラス
//////////////////////////////////////////////////////////////////////
class AstInt :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstInt(const FileRegion& loc, ///< [in] ファイル上の位置
	 int value);            ///< [in] 値

  /// @brief デストラクタ
  ~AstInt();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値を返す．
  int
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
  int mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTINT_H
