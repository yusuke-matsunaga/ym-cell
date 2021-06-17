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
  AstStrList(const vector<AstString*>& str_list, ///< [in] 文字列のリスト
	     const FileRegion& loc);             ///< [in] ファイル上の位置

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
    return mBody.size();
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
    return mBody;
  }

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,                     ///< [in] 出力先のストリーム
       int indent = 0) const override; ///< [in] インデント量


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // リストの本体
  vector<const AstString*> mBody;

  // ファイル上の位置
  FileRegion mLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTSTRLIST_H
