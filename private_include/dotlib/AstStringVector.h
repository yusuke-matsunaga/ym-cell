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

  /// @brief ベクタの要素数を返す．
  int
  size() const;

  /// @brief ベクタの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < size() )
  ShString
  value(int pos) const;

  /// @brief ベクタを取り出す．
  /// @param[out] vector ベクタを格納する変数
  void
  get_vector(vector<ShString>& vector) const;

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

  // 要素数
  int mNum;

  // ベクタの本体
  ShString mBody[1];

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ベクタの要素数を返す．
inline
int
AstStringVector::size() const
{
  return mNum;
}

// @brief ベクタの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < size() )
inline
ShString
AstStringVector::value(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < size() );

  return mBody[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRINGVECTOR_H
