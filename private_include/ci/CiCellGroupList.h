#ifndef CICELLGROUPLIST_H
#define CICELLGROUPLIST_H

/// @file CiCellGroupList.h
/// @brief CiCellGroupList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellGroupList.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellGroup;

//////////////////////////////////////////////////////////////////////
/// @class CiCellGroupList CiCellGroupList.h "CiCellGroupList.h"
/// @brief ClibCellGroupList の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellGroupList :
  public ClibCellGroupList
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  CiCellGroupList();

  /// @brief デストラクタ
  virtual
  ~CiCellGroupList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  /// @param[in] group_list セルグループのリスト
  /// @param[in] alloc メモリアロケータ
  void
  init(const vector<const ClibCellGroup*>& group_list,
       Alloc& alloc);

  /// @brief 要素数を返す．
  virtual
  int
  num() const;

  /// @brief 先頭の反復子を返す．
  virtual
  iterator
  begin() const;

  /// @brief 末尾の反復子を返す．
  virtual
  iterator
  end() const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素数
  int mNum;

  // セルグループへのポインタ配列
  const ClibCellGroup** mArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUPLIST_H
