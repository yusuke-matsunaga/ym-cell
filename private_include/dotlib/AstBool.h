#ifndef ASTBOOL_H
#define ASTBOOL_H

/// @file AstBool.h
/// @brief AstBool のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstBool AstBool.h "AstBool.h"
/// @brief 整数値を表すクラス
//////////////////////////////////////////////////////////////////////
class AstBool :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstBool(const FileRegion& loc, ///< [in] ファイル上の位置
	  bool value);           ///< [in] 値

  /// @brief デストラクタ
  ~AstBool();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ブール値を返す．
  bool
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
  bool mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTBOOL_H
