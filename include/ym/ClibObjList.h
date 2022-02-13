#ifndef CLIBOBJLIST_H
#define CLIBOBJLIST_H

/// @file ClibObjList.h
/// @brief ClibObjList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

class ClibCell;

//////////////////////////////////////////////////////////////////////
/// @class ClibObjListIter ClibObjListIter.h "ClibObjListIter.h"
/// @brief ClibObjList の反復子
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibObjListIter
{
  using iter_type = typename vector<const T*>::const_iterator;

public:

  /// @brief 空のコンストラクタ
  ClibObjListIter() = default;

  /// @brief 値を指定したコンストラクタ
  ClibObjListIter(
    iter_type iter
  ) : mIter{iter}
  {
  }

  /// @brief デストラクタ
  ~ClibObjListIter() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を取り出す．
  const T&
  operator*() const
  {
    return **mIter;
  }

  /// @brief 次の要素を指す．
  ClibObjListIter&
  operator++()
  {
    ++ mIter;
    return *this;
  }

  /// @brief 等価比較演算子
  bool
  operator==(
    const ClibObjListIter& right
  )
  {
    return mIter == right.mIter;
  }

  /// @brief 非等価比較演算子
  bool
  operator!=(
    const ClibObjListIter& right
  )
  {
    return mIter != right.mIter;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 本当の反復子
  iter_type mIter;

};


//////////////////////////////////////////////////////////////////////
/// @class ClibObjList ClibObjList.h "ClibObjList.h"
/// @brief ClibCell のリストを表すクラス
///
/// 実際には vector<const T*> のラッパクラス
/// for ( auto& cell: cell_list ) の形で使えるように，
/// ポインタではなく参照を返すようにしている．
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibObjList
{
public:

  using iterator = ClibObjListIter<T>;

public:

  /// @brief コンストラクタ
  ClibObjList(
    const vector<const T*>& list
  ) : mList{list}
  {
  }

  /// @brief デストラクタ
  ~ClibObjList() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 先頭の反復子を得る．
  iterator
  begin() const
  {
    return iterator{mList.begin()};
  }

  /// @brief 末尾の反復子を得る．
  iterator
  end() const
  {
    return iterator{mList.end()};

  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // リストの本体
  const vector<const T*>& mList;

};

END_NAMESPACE_YM_CLIB

#endif // CLIBOBJLIST_H
