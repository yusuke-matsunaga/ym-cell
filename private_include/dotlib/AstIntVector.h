#ifndef ASTINTVECTOR_H
#define ASTINTVECTOR_H

/// @file AstIntVector.h
/// @brief AstIntVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstIntVector AstIntVector.h "AstIntVector.h"
/// @brief 整数値のベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstIntVector :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstIntVector(const FileRegion& loc,
	       const vector<int>& value);

  /// @brief デストラクタ
  ~AstIntVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  int
  size() const;

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < size() )
  int
  value(int pos) const;

  /// @brief ベクタを取り出す．
  /// @param[out] vector ベクタを格納する変数
  void
  get_vector(vector<int>& vector) const;

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

  // 本体の配列
  int mBody[1];

};


//////////////////////////////////////////////////////////////////////
// インライン関数
//////////////////////////////////////////////////////////////////////

// @brief 要素数を返す．
inline
int
AstIntVector::size() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < size() )
inline
int
AstIntVector::value(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < size() );

  return mBody[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTVECTOR_H
