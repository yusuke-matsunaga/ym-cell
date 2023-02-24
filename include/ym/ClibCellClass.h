#ifndef YM_CLIBCELLCLASS_H
#define YM_CLIBCELLCLASS_H

/// @file ym/ClibCellClass.h
/// @brief ClibCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"
#include "ym/ClibList.h"
#include "ym/logic.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellClass ClibCellClass.h "ym/ClibCellClass.h"
/// @brief NPN同値なセルグループの集合を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibCellClass :
  public ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibCellClass() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibCellClass(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibCellClass() = default;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 一般的な情報を取得する関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  SizeType
  id() const { return mId; }

  /// @brief 同位体変換の個数を得る．
  ///
  /// 恒等変換は含まない．
  SizeType
  idmap_num() const;

  /// @brief 同位体変換を得る．
  const ClibIOMap&
  idmap(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < idmap_num() )
  ) const;

  /// @brief 同位体変換のリストを得る．
  const vector<ClibIOMap>&
  idmap_list() const;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name このクラスに属しているセルグループの情報を取得する関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ数を返す．
  SizeType
  cell_group_num() const;

  /// @brief グループを返す．
  ClibCellGroup
  cell_group(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_group_num() )
  ) const;

  /// @brief グループのリストを返す．
  ClibCellGroupList
  cell_group_list() const;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLCLASS_H
