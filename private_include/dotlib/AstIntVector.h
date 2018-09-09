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

  /// @brief 整数値を返す．
  const vector<int>&
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
  vector<int> mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数
//////////////////////////////////////////////////////////////////////

// @brief 整数値を返す．
inline
const vector<int>&
AstIntVector::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTVECTOR_H
