#ifndef CLIBCELLCLASSLIST_H
#define CLIBCELLCLASSLIST_H

/// @file ClibCellClassList.h
/// @brief ClibCellClassList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellClass;

//////////////////////////////////////////////////////////////////////
/// @class ClibCellClassListIterator ClibCellClassList.h "ClibCellClassList.h"
/// @brief ClibCellClassList 用の反復子
//////////////////////////////////////////////////////////////////////
class ClibCellClassListIterator
{
public:

  /// @brief コンストラクタ
  /// @brief obj_ptr 要素へのポインタ
  ClibCellClassListIterator(CiCellClass** obj_ptr);

  /// @brief デストラクタ
  ~ClibCellClassListIterator();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief dereference 演算子
  const ClibCellClass*
  operator*() const;

  /// @brief increment 演算子
  const ClibCellClassListIterator&
  operator++();

  /// @brief 等価比較演算子
  bool
  operator==(const ClibCellClassListIterator& right) const;

  /// @brief 非等価比較演算子
  bool
  operator!=(const ClibCellClassListIterator& right) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素へのポインタ
  CiCellClass** mObjPtr;

};


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
  typedef ClibCellClassListIterator iterator;

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

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  virtual
  const ClibCellClass*
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

#endif // CLIBCELLCLASSLIST_H
