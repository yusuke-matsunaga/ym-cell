#ifndef ASTVARTYPE_H
#define ASTVARTYPE_H

/// @file AstVarType.h
/// @brief AstVarType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstVarType AstVarType.h "AstVarType.h"
/// @brief var typeを表すクラス
//////////////////////////////////////////////////////////////////////
class AstVarType :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstVarType(const FileRegion& loc, ///< [in] ファイル上の位置
	     ClibVarType value);    ///< [in] 値

  /// @brief デストラクタ
  ~AstVarType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType を返す．
  ClibVarType
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
  ClibVarType mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTVARTYPE_H
