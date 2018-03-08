﻿#ifndef MISLIBNODE_H
#define MISLIBNODE_H

/// @file MislibNode.h
/// @brief MislibNode のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibNode MislibNode.h "MislibNode.h"
/// @brief mislib 形式のASTを表すクラス
//////////////////////////////////////////////////////////////////////
class MislibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  MislibNode(const FileRegion& loc);

  /// @brief デストラクタ
  ~MislibNode();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通な関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 位置情報を取り出す．
  FileRegion
  loc() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 派生クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 位置を出力する．
  void
  dump_loc(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 位置情報
  FileRegion mLoc;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 位置情報を取り出す．
inline
FileRegion
MislibNode::loc() const
{
  return mLoc;
}

END_NAMESPACE_YM_MISLIB

#endif // MISLIBNODE_H
