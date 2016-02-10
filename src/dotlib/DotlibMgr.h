﻿#ifndef DOTLIBMGR_H
#define DOTLIBMGR_H

/// @file DotlibMgr.h
/// @brief DotlibMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"


BEGIN_NAMESPACE_YM_DOTLIB

class DotlibMgrImpl;

//////////////////////////////////////////////////////////////////////
/// @class DotlibMgr DotlibMgr.h "DotlibMgr.h"
/// @brief DotlibNode を管理するためのクラス
/// 内容は DotlibParser によってセットされる．
//////////////////////////////////////////////////////////////////////
class DotlibMgr
{
  friend class DotlibParser;

public:

  /// @brief コンストラクタ
  DotlibMgr();

  /// @brief デストラクタ
  ~DotlibMgr();


public:

  /// @brief 初期化する．
  /// @note 以前，生成されたオブジェクトは破壊される．
  void
  clear();

  /// @brief 根のノードを返す．
  const DotlibNode*
  root_node() const;

  /// @brief 使用メモリ量の一覧を出力する．
  /// @param[in] s 出力先のストリーム
  void
  show_stats(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 実際の処理を行うクラス
  DotlibMgrImpl* mImpl;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBMGR_H
