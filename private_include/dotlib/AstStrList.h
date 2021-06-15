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
  AstStrList(const StrListHandler& handler); ///< [in] ハンドラ

  /// @brief デストラクタ
  ~AstStrList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief リストの要素数を返す．
  int
  size() const
  {
    return mNum;
  }

  /// @brief リストの要素を返す．
  const AstString*
  value(int pos) const ///< [in] 位置番号 ( 0 <= pos < size() )
  {
    ASSERT_COND( pos >= 0 && pos < size() );

    return mBody[pos];
  }

  /// @brief リストを取り出す．
  vector<const AstString*>
  get_vector() const
  {
    return vector<const AstString*>(&mBody[0], &mBody[size()]);
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

  // 要素数
  int mNum;

  // リストの本体
  const AstString* mBody[1];

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRLIST_H
