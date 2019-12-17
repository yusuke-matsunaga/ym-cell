#ifndef CLIBOBJLIST_H
#define CLIBOBJLIST_H

/// @file ClibObjList.h
/// @brief ClibObjList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2019 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibObjIterator ClibObjList.h "ym/ClibObjList.h"
/// @brief ClibObjList 用の反復子
///
/// 実際は T* を持っているのに const T& を返すところがミソ
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibObjIterator
{
public:

  /// @brief コンストラクタ
  /// @param[in] obj_ptr 要素へのポインタ
  ClibObjIterator(T** obj_ptr);

  /// @brief デストラクタ
  ~ClibObjIterator();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief dereference 演算子
  const T&
  operator*() const;

  /// @brief 増加演算子
  ClibObjIterator<T>
  operator++();

  /// @brief 等価比較演算子
  bool
  operator==(const ClibObjIterator<T>& right) const;

  /// @brief 非等価比較演算子
  bool
  operator!=(const ClibObjIterator<T>& right) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素へのポインタ
  T** mObjPtr;

};


//////////////////////////////////////////////////////////////////////
/// @class ClibObjList ClibObjList.h "ym/ClibObjList.h"
/// @brief Clib オブジェクトのリストを表すテンプレートクラス
//////////////////////////////////////////////////////////////////////
template<class T>
class ClibObjList
{
public:

  /// @brief 空のコンストラクタ
  ClibObjList() = default;

  /// @brief 内容を指定したコンストラクタ
  /// @param[in] src_list ソースリスト
  ClibObjList(const vector<T*>& src_list);

  /// @brief デストラクタ
  ~ClibObjList();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を(再)設定する．
  /// @param[in] src_list ソースリスト
  ///
  /// 以前の内容は破棄される．
  void
  init(const vector<T*>& src_list);

  /// @brief 要素数を返す．
  int
  num() const;

  /// @brief 要素を返す．
  /// @param[in] pos 要素の位置 ( 0 <= pos < num() )
  const T&
  operator[](int pos) const;

  /// @brief 先頭の反復子を返す．
  ClibObjIterator<T>
  begin() const;

  /// @brief 末尾の反復子を返す．
  ClibObjIterator<T>
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
  int mNum{0};

  // 要素(のポインタ)の配列
  T** mBody{nullptr};

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] obj_ptr 要素へのポインタ
template<class T>
inline
ClibObjIterator<T>::ClibObjIterator(T** obj_ptr) :
  mObjPtr{obj_ptr}
{
}

// @brief デストラクタ
template<class T>
inline
ClibObjIterator<T>::~ClibObjIterator()
{
}

// @brief dereference 演算子
template<class T>
inline
const T&
ClibObjIterator<T>::operator*() const
{
  return **mObjPtr;
}

// @brief 増加演算子
template<class T>
inline
ClibObjIterator<T>
ClibObjIterator<T>::operator++()
{
  ++ mObjPtr;

  return *this;
}

// @brief 等価比較演算子
template<class T>
inline
bool
ClibObjIterator<T>::operator==(const ClibObjIterator<T>& right) const
{
  return mObjPtr == right.mObjPtr;
}

// @brief 非等価比較演算子
template<class T>
inline
bool
ClibObjIterator<T>::operator!=(const ClibObjIterator<T>& right) const
{
  return !operator==(right);
}

// @brief 内容を指定したコンストラクタ
// @param[in] src_list ソースリスト
template<class T>
inline
ClibObjList<T>::ClibObjList(const vector<T*>& src_list)
{
  init(src_list);
}

// @brief デストラクタ
template<class T>
inline
ClibObjList<T>::~ClibObjList()
{
  delete [] mBody;
}

// @brief 内容を(再)設定する．
// @param[in] src_list ソースリスト
//
// 以前の内容は破棄される．
template<class T>
inline
void
ClibObjList<T>::init(const vector<T*>& src_list)
{
  delete [] mBody;
  mNum = src_list.size();
  mBody = new T*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    mBody[i] = src_list[i];
  }
}

// @brief 要素数を返す．
template<class T>
inline
int
ClibObjList<T>::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 要素の位置 ( 0 <= pos < num() )
template<class T>
inline
const T&
ClibObjList<T>::operator[](int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return *mBody[pos];
}

// @brief 先頭の反復子を返す．
template<class T>
inline
ClibObjIterator<T>
ClibObjList<T>::begin() const
{
  return ClibObjIterator<T>(mBody);
}

// @brief 末尾の反復子を返す．
template<class T>
inline
ClibObjIterator<T>
ClibObjList<T>::end() const
{
  return ClibObjIterator<T>(mBody + num());
}

END_NAMESPACE_YM_CLIB

#endif // CLIBOBJLIST_H
