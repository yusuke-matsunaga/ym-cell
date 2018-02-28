#ifndef CLIBCELLLIST_H
#define CLIBCELLLIST_H

/// @file ClibCellList.h
/// @brief ClibCellList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class ClibCellListIterator ClibCellList.h "ClibCellList.h"
/// @brief ClibCellList 用の反復子
//////////////////////////////////////////////////////////////////////
class ClibCellListIterator
{
public:

  /// @brief コンストラクタ
  /// @brief obj_ptr 要素へのポインタ
  ClibCellListIterator(CiCell** obj_ptr);

  /// @brief デストラクタ
  ~ClibCellListIterator();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief dereference 演算子
  const ClibCell*
  operator*() const;

  /// @brief increment 演算子
  const ClibCellListIterator&
  operator++();

  /// @brief 等価比較演算子
  bool
  operator==(const ClibCellListIterator& right) const;

  /// @brief 非等価比較演算子
  bool
  operator!=(const ClibCellListIterator& right) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素へのポインタ
  CiCell** mObjPtr;

};


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
  typedef ClibCellListIterator iterator;

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

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibCell*
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

#endif // CLIBCELLLIST_H
