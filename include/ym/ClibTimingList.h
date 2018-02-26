#ifndef CLIBTIMINGLIST_H
#define CLIBTIMINGLIST_H

/// @file ClibTimingList.h
/// @brief ClibTimingList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ArrayIterator.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibTimingList ClibTimingList.h "ClibTimingList.h"
/// @brief ClibCell のリストを表すクラス
///
/// @code
/// const ClibTimingList& timing_list = ...;
/// for ( auto timing: timing_list ) {
///   ...
/// }
/// @endcode
/// というふうに使える．
//////////////////////////////////////////////////////////////////////
class ClibTimingList
{
public:
  typedef ArrayIterator<const ClibTiming*> iterator;

  /// @brief デストラクタ
  virtual
  ~ClibTimingList() { }


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

  /// @brief 指定された位置の要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibTiming*
  operator[](int pos) const = 0;


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

#endif // CLIBTIMINGLIST_H
