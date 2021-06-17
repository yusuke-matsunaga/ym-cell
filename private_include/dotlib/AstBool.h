﻿#ifndef ASTBOOL_H
#define ASTBOOL_H

/// @file AstBool.h
/// @brief AstBool のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstBool AstBool.h "AstBool.h"
/// @brief ブール値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstBool :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstBool(bool value,                 ///< [in] 値
	  const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstBool() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ブール値を返す．
  bool
  bool_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  bool mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTBOOL_H
