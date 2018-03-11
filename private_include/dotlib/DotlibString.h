#ifndef DOTLIBSTRING_H
#define DOTLIBSTRING_H

/// @file DotlibString.h
/// @brief DotlibString のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibString DotlibString.h "DotlibString.h"
/// @brief 文字列を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibString :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibString(const FileRegion& loc,
	       ShString value);

  /// @brief デストラクタ
  virtual
  ~DotlibString();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数シンボルを返す．
  /// @note type() が kString の時のみ意味を持つ．
  ShString
  value() const;

  /// @brief 文字列を取り出す．
  ///
  /// 型が違ったらエラーを MsgMgr に出力する．
  virtual
  bool
  expect_string(ShString& value) const;

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
DotlibString::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
