#ifndef ASTUNIT_H
#define ASTUNIT_H

/// @file AstUnit.h
/// @brief AstUnit のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstUnit AstUnit.h "AstUnit.h"
/// @brief 単位を表すクラス
//////////////////////////////////////////////////////////////////////
class AstUnit :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] unit_val 数値
  /// @param[in] unit_str 単位を表す文字列
  AstUnit(const FileRegion& loc,
	  const AstFloat* unit_val,
	  const AstString* unit_str);

  /// @brief デストラクタ
  ~AstUnit();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 単位を表す数値を返す．
  const AstFloat*
  unit_val() const;

  /// @brief 単位を表す文字列を返す．
  const AstString*
  unit_str() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 単位を表す数値
  const AstFloat* mVal;

  // 単位を表す文字列
  const AstString* mStr;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 単位を表す数値を返す．
inline
const AstFloat*
AstUnit::unit_val() const
{
  return mVal;
}

// @brief 単位を表す文字列を返す．
inline
const AstString*
AstUnit::unit_str() const
{
  return mStr;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTUNIT_H
