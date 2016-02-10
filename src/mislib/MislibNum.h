﻿#ifndef MISLIBNUM_H
#define MISLIBNUM_H

/// @file MislibNum.h
/// @brief MislibNum のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNodeImpl.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibNum MislibNum.h "MislibNum.h"
/// @brief 数値を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibNum :
  public MislibNodeImpl
{
  friend class MislibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] num 数値
  MislibNum(const FileRegion& loc,
	    double num);

  /// @brief デストラクタ
  ~MislibNum();


public:

  /// @brief 種類を取り出す．
  virtual
  tType
  type() const;

  /// @brief 数値を取り出す
  virtual
  double
  num() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  virtual
  void
  dump(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 数値
  double mNum;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBNUM_H
