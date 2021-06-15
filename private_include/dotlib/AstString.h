#ifndef ASTSTRING_H
#define ASTSTRING_H

/// @file AstString.h
/// @brief AstString のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstString AstString.h "AstString.h"
/// @brief 文字列を表すクラス
//////////////////////////////////////////////////////////////////////
class AstString :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstString(const FileRegion& loc, ///< [in] ファイル上の位置
	    ShString value);	   ///< [in] 値

  /// @brief デストラクタ
  ~AstString();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数シンボルを返す．
  /// @note type() が kString の時のみ意味を持つ．
  ShString
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
  ShString mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRING_H
