#ifndef CLIBCELLCLASSLIST_H
#define CLIBCELLCLASSLIST_H

/// @file ClibCellClassList.h
/// @brief ClibCellClassList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibCellClassList ClibCellClassList.h "ClibCellClassList.h"
/// @brief ClibCell のリストを表すクラス
///
/// @code
/// const ClibCellClassList& class_list = ...;
/// for ( auto cell_class: class_list ) {
///   ...
/// }
/// @endcode
/// というふうに使える．
//////////////////////////////////////////////////////////////////////
class ClibCellClassList
{
public:
  typedef ArrayIterator<const ClibCellClass*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibCellClassList() { }


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

#endif // CLIBCELLCLASSLIST_H
