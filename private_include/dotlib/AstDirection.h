#ifndef ASTDIRECTION_H
#define ASTDIRECTION_H

/// @file AstDirection.h
/// @brief ピンの方向を表す AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
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
  AstDirection(const FileRegion& loc, ///< [in] ファイル上の位置
	       ClibDirection value);  ///< [in] 値

  /// @brief デストラクタ
  ~AstDirection();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief CellPinDirection を返す．
  ClibDirection
  value() const
  {
    return mValue;
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

  // 値
  ClibDirection mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTDIRECTION_H
