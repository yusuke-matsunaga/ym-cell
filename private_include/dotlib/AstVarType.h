#ifndef ASTVARTYPE_H
#define ASTVARTYPE_H

/// @file AstVarType.h
/// @brief AstVarType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstVarType(const FileRegion& loc,
	     ClibVarType value);

  /// @brief デストラクタ
  ~AstVarType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType を返す．
  ClibVarType
  value() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibVarType mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief VarType を返す．
inline
ClibVarType
AstVarType::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTVARTYPE_H
