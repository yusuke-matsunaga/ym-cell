#ifndef ASTSTRING_H
#define ASTSTRING_H

/// @file AstString.h
/// @brief AstString のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstString(const FileRegion& loc,
	    ShString value);

  /// @brief デストラクタ
  virtual
  ~AstString();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数シンボルを返す．
  /// @note type() が kString の時のみ意味を持つ．
  ShString
  value() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ShString mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 定数シンボルを返す．
inline
ShString
AstString::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRING_H
