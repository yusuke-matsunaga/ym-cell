﻿#ifndef DOTLIBLATCH_H
#define DOTLIBLATCH_H

/// @file ym_dotlib/DotlibLatch.h
/// @brief DotlibLatch のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibLatch DotlibLatch.h "DotlibLatch.h"
/// @brief DotlibNode の木から取り出した Latch の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibLatch :
  public DotlibFL
{
public:

  /// @brief コンストラクタ
  DotlibLatch();

  /// @brief デストラクタ
  ~DotlibLatch();


public:

  /// @brief 内容を初期化する．
  bool
  set_data(const DotlibNode* latch_node);

  /// @brief "data_in" を返す．
  const DotlibNode*
  data_in() const;

  /// @brief "enable" を返す．
  const DotlibNode*
  enable() const;

  /// @brief "enable_also" を返す．
  const DotlibNode*
  enable_also() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // data_in
  const DotlibNode* mDataIn;

  // enable
  const DotlibNode* mEnable;

  // enable_also
  const DotlibNode* mEnableAlso;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBLATCH_H
