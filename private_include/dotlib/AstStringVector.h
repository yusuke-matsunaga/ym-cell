#ifndef ASTSTRINGVECTOR_H
#define ASTSTRINGVECTOR_H

/// @file AstStringVector.h
/// @brief AstStringVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstStringVector AstStringVector.h "AstStringVector.h"
/// @brief 文字列のベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstStringVector :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 文字列のリスト
  AstStringVector(const FileRegion& loc,
		  const vector<ShString>& value);

  /// @brief デストラクタ
  ~AstStringVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 文字列のリストを返す．
  const vector<ShString>&
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
  vector<ShString> mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 文字列のリストを返す．
inline
const vector<ShString>&
AstStringVector::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRINGVECTOR_H
