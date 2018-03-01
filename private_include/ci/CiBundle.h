﻿#ifndef CIBUNDLE_H
#define CIBUNDLE_H

/// @file CiBundle.h
/// @brief CiBundle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibBundle.h"
#include "ym/ShString.h"
#include "ci/CiCellPinList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBundle CiBundle.h "CiBundle.h"
/// @brief ClibBundle の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBundle :
  public ClibBundle
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiBundle();

  /// @brief デストラクタ
  ~CiBundle();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const;

  /// @brief ピン数の取得
  virtual
  int
  pin_num() const;

  /// @brief ピンの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
  virtual
  const ClibCellPin*
  pin(int pos) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  void
  init(const ShString& name,
       const vector<CiCellPin*>& pin_list,
       Alloc& alloc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // ピンのリスト
  CiCellPinList mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUNDLE_H
