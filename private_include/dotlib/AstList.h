#ifndef DOTLIBLIST_H
#define DOTLIBLIST_H

/// @file AstList.h
/// @brief AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibList AstList.h "AstList.h"
/// @brief リストを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibList :
  public AstNode
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] elem_list 要素のリスト
  DotlibList(const vector<AstNode*>& elem_list);

  /// @brief デストラクタ
  virtual
  ~DotlibList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief リストの要素数を返す．
  int
  list_size() const;

  /// @brief リストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
  const AstNode*
  list_elem(int pos) const;

  /// @brief 1つの文字列からなるリストの場合に文字列を返す．
  ///
  /// 仮定が外れたらアボートする．
  virtual
  ShString
  get_string_from_value_list() const;

  /// @brief 2つの文字列からなるリストの内容を取り出す．
  /// @param[out] str1 1つ目の文字列を格納する変数
  /// @param[out] str2 2つ目の文字列を格納する変数
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  /// @note エラーは MsgMgr に出力する．
  virtual
  bool
  expect_string_pair(ShString& str1,
		     ShString& str2) const;

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

  // 要素の配列
  const AstNode* mList[1];

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief リストの要素数を返す．
inline
int
DotlibList::list_size() const
{
  return mNum;
}

// @brief リストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
inline
const AstNode*
DotlibList::list_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < list_size() );

  return mList[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBLIST_H
