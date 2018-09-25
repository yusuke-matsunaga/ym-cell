#ifndef ASTSTRLIST_H
#define ASTSTRLIST_H

/// @file AstStrList.h
/// @brief AstStrList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstStrList AstStrList.h "AstStrList.h"
/// @brief 文字列のリストを表すクラス
//////////////////////////////////////////////////////////////////////
class AstStrList :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] handler ハンドラ
  AstStrList(const StrListHandler& handler);

  /// @brief デストラクタ
  ~AstStrList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief リストの要素数を返す．
  int
  size() const;

  /// @brief リストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < size() )
  const AstString*
  value(int pos) const;

  /// @brief リストを取り出す．
  /// @param[out] vector リストを格納する変数
  void
  get_vector(vector<const AstString*>& vector) const;

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

  // リストの本体
  const AstString* mBody[1];

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief リストの要素数を返す．
inline
int
AstStrList::size() const
{
  return mNum;
}

// @brief リストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < size() )
inline
const AstString*
AstStrList::value(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < size() );

  return mBody[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRLIST_H
