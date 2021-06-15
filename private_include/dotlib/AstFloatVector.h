#ifndef ASTFLOATVECTOR_H
#define ASTFLOATVECTOR_H

/// @file AstFloatVector.h
/// @brief AstFloatVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
public:

  /// @brief コンストラクタ
  AstFloatVector(const FileRegion& loc,             ///< [in] ファイル上の位置
		 const vector<double>& value_list); ///< [in] 値のリスト

  /// @brief デストラクタ
  ~AstFloatVector();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタの要素数を返す．
  int
  size() const
  {
    return mNum;
  }

  /// @brief ベクタの要素を返す．
  double
  value(int pos) const ///< [in] 位置番号 ( 0 <= pos < size() )
  {
    ASSERT_COND( pos >= 0 && pos < size() );

    return mBody[pos];
  }

  /// @brief ベクタの全体を取り出す．
  vector<double>
  get_vector() const
  {
    return vector<double>(&mBody[0], &mBody[size()]);
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

  // ベクタの本体
  double mBody[1];

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOATVECTOR_H
