#ifndef CLIBCELLPINLIST_H
#define CLIBCELLPINLIST_H

/// @file ClibCellPinList.h
/// @brief ClibCellPinList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibCellPinList ClibCellPinList.h "ClibCellPinList.h"
/// @brief ClibCellPin のリストを表すクラス
///
/// @code
/// const ClibCellPinList& pin_list = ...;
/// for ( auto pin: pin_list ) {
///   ...
/// }
/// @endcode
/// というふうに使える．
//////////////////////////////////////////////////////////////////////
class ClibCellPinList
{
public:
  typedef ArrayIterator<const ClibCellPin*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibCellPinList() { }


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
  const ClibCellPin*
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

#endif // CLIBCELLPINLIST_H
