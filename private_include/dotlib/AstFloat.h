#ifndef ASTFLOAT_H
#define ASTFLOAT_H

/// @file AstFloat.h
/// @brief AstFloat のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloat AstFloat.h "AstFloat.h"
/// @brief 実数値を表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloat :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstFloat(const FileRegion& loc,
	   double value);

  /// @brief デストラクタ
  ~AstFloat();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  /// @note type() が kFloat の時のみ意味を持つ．
  double
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
  double mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 数値を返す．
// @note type() が kFloat の時のみ意味を持つ．
inline
double
AstFloat::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOAT_H
