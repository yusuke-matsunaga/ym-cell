#ifndef LCGROUP_H
#define LCGROUP_H

/// @file LcGroup.h
/// @brief LcGroup.h
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "ym/NpnMapM.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcGroup LcGroup.h "LcGroup.h"
/// @brief テンポラリに使用するセルグループ用のクラス
//////////////////////////////////////////////////////////////////////
class LcGroup
{
  friend class LcClass;

public:

  /// @brief コンストラクタ
  LcGroup(
    int id ///< [in] ID番号
  ) :  mId(id),
       mParent(nullptr),
       mCellGroup(nullptr)
  {
  }

  /// @brief デストラクタ
  ~LcGroup() = default;


public:

  /// @brief ID番号を返す．
  int
  id() const
  {
    return mId;
  }

  /// @brief 親の LcClass を返す．
  LcClass*
  parent() const
  {
    return mParent;
  }

  /// @brief 親のクラスに対する変換マップを返す．
  const NpnMapM&
  map() const
  {
    return mMap;
  }

  /// @brief 実体を返す．
  ClibCellGroup*
  cell_group() const
  {
    return mCellGroup;
  }

  /// @brief 属しているセルのリストを返す．
  const vector<CiCell*>&
  cell_list() const
  {
    return mCellList;
  }

  /// @brief セルを追加する．
  void
  add_cell(
    CiCell* cell ///< [in] 追加するセル
  )
  {
    mCellList.push_back(cell);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  int mId;

  // 親の LcClass
  LcClass* mParent;

  // 親のクラスに対する変換マップ
  NpnMapM mMap;

  // 実体のオブジェクト
  ClibCellGroup* mCellGroup;

  // セルのリスト
  vector<CiCell*> mCellList;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCGROUP_H
