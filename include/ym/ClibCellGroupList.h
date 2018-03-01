#ifndef CLIBCELLGROUPLIST_H
#define CLIBCELLGROUPLIST_H

/// @file ClibCellGroupList.h
/// @brief ClibCellGroupList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibCellGroupList ClibCellGroupList.h "ClibCellGroupList.h"
/// @brief ClibCell のリストを表すクラス
///
/// @code
/// const ClibCellGroupList& cg_list = ...;
/// for ( auto group: cg_list ) {
///   ...
/// }
/// @endcode
/// というふうに使える．
//////////////////////////////////////////////////////////////////////
class ClibCellGroupList
{
public:
  typedef ArrayIterator<const ClibCellGroup*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibCellGroupList() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  virtual
  int
  num() const = 0;

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibCellGroup*
  operator[](int pos) const = 0;

  /// @brief 先頭の反復子を返す．
  virtual
  iterator
  begin() const = 0;

  /// @brief 末尾の反復子を返す．
  virtual
  iterator
  end() const = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_CLIB

#endif // CLIBCELLGROUPLIST_H
