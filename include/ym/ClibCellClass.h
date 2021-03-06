﻿#ifndef YM_CLIBCELLCLASS_H
#define YM_CLIBCELLCLASS_H

/// @file ym/ClibCellClass.h
/// @brief ClibCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellClass ClibCellClass.h "ym/ClibCellClass.h"
/// @brief NPN同値なセルグループの集合を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibCellClass
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibCellClass() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  ///
  /// ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
  virtual
  int
  id() const = 0;

  /// @brief 同位体変換の個数を得る．
  ///
  /// 恒等変換は含まない．
  virtual
  int
  idmap_num() const = 0;

  /// @brief 同位体変換を得る．
  virtual
  const NpnMapM&
  idmap(int pos) const ///< [in] 位置番号 ( 0 <= pos < idmap_num() )
  = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスに属しているセルグループの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCellGroup のリストを返す．
  virtual
  const ClibCellGroupList&
  group_list() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(ostream& s) const ///< [in] 出力先のストリーム
  = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLCLASS_H
