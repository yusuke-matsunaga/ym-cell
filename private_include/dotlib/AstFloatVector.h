#ifndef ASTFLOATVECTOR_H
#define ASTFLOATVECTOR_H

/// @file AstFloatVector.h
/// @brief AstFloatVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloatVector AstFloatVector.h "AstFloatVector.h"
/// @brief ベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloatVector :
  public AstNode
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  AstFloatVector(const FileRegion& loc,
		 const vector<double>& value_list);

  /// @brief デストラクタ
  virtual
  ~AstFloatVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタの要素数を返す．
  int
  size() const;

  /// @brief ベクタの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
  double
  value(int pos) const;

  /// @brief ベクタの全体を取り出す．
  /// @param[out] vector 結果を格納する変数
  void
  get_vector(vector<double>& vector) const;

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

  // 要素数
  int mNum;

  // ベクタの本体
  double mBody[1];

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ベクタの要素数を返す．
inline
int
AstFloatVector::size() const
{
  return mNum;
}

// @brief ベクタの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
inline
double
AstFloatVector::value(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < size() );

  return mBody[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOATVECTOR_H
