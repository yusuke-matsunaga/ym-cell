#ifndef ASTDIRECTION_H
#define ASTDIRECTION_H

/// @file AstDirection.h
/// @brief ピンの方向を表す AstNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstCellPinDirection AstDirection.h "dotlib/AstDirection.h"
/// @brief 'direction' のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstDirection :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstDirection(ClibDirection value,        ///< [in] 値
	       const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstDirection() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief direction を返す．
  ClibDirection
  direction_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibDirection mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTDIRECTION_H
