﻿#ifndef YM_CELLBUNDLE_H
#define YM_CELLBUNDLE_H

/// @file ym/CellBundle.h
/// @brief CellBundle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ym_cell.h"


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
/// @class CellBundle CellBundle.h "ym/CellBundle.h"
/// @brief バンドルを表すクラス
//////////////////////////////////////////////////////////////////////
class CellBundle
{
public:

  /// @brief コンストラクタ
  CellBundle() { }

  /// @brief デストラクタ
  virtual
  ~CellBundle() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief ピン数の取得
  virtual
  ymuint
  pin_num() const = 0;

  /// @brief ピンの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
  virtual
  const CellPin*
  pin(ymuint pos) const = 0;

};

END_NAMESPACE_YM_CELL

#endif // YM_CELLBUNDLE_H
