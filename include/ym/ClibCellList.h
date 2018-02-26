#ifndef CLIBCELLLIST_H
#define CLIBCELLLIST_H

/// @file ClibCellList.h
/// @brief ClibCellList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibCellList ClibCellList.h "ClibCellList.h"
/// @brief ClibCell のリストを表すクラス
///
/// @code
/// const ClibCellList& cell_list = ...;
/// for ( auto cell: cell_list ) {
///   ...
/// }
/// @endcode
/// というふうに使える．
//////////////////////////////////////////////////////////////////////
class ClibCellList
{
public:
  typedef ArrayIterator<const ClibCell*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibCellList() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  virtual
  int
  num() const = 0;

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

#endif // CLIBCELLLIST_H
