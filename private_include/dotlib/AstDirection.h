#ifndef ASTDIRECTION_H
#define ASTDIRECTION_H

/// @file AstDirection.h
/// @brief ピンの方向を表す AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstCellPinDirection AstDirection.h "dotlib/AstDirection.h"
/// @brief 'direction' を表すクラス
//////////////////////////////////////////////////////////////////////
class AstDirection :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  AstDirection(const FileRegion& loc,
	       ClibDirection value);

  /// @brief デストラクタ
  ~AstDirection();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief CellPinDirection を返す．
  ClibDirection
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
  ClibDirection mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief CellPinDirection を返す．
inline
ClibDirection
AstDirection::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTDIRECTION_H
