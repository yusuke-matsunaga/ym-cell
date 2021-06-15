#ifndef ASTINTVECTOR_H
#define ASTINTVECTOR_H

/// @file AstIntVector.h
/// @brief AstIntVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstIntVector(const FileRegion& loc,     ///< [in] ファイル上の位置
	       const vector<int>& value); ///< [in] 値

  /// @brief デストラクタ
  ~AstIntVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  int
  size() const
  {
    return mNum;
  }

  /// @brief 要素を返す．
  int
  value(int pos) const ///< [in] 位置番号 ( 0 <= pos < size() )
  {
    ASSERT_COND( pos >= 0 && pos < size() );

    return mBody[pos];
  }

  /// @brief ベクタを取り出す．
  vector<int>
  get_vector() const
  {
    return vector<int>(&mBody[0], &mBody[size()]);
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

  // 本体の配列
  int mBody[1];

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTVECTOR_H
