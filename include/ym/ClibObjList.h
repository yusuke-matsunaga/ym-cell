#ifndef CLIBOBJLIST_H
#define CLIBOBJLIST_H

/// @file ClibObjList.h
/// @brief ClibObjList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2019, 2021 Yusuke Matsunaga
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
  ClibObjIterator(
    T** obj_ptr ///< [in] 要素へのポインタ
  ) : mObjPtr{obj_ptr}
  {
  }

  /// @brief デストラクタ
  ~ClibObjIterator() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief dereference 演算子
  const T&
  operator*() const
  {
    return **mObjPtr;
  }

  /// @brief 増加演算子
  ClibObjIterator<T>
  operator++()
  {
    ++ mObjPtr;

    return *this;
  }

  /// @brief 等価比較演算子
  bool
  operator==(
    const ClibObjIterator<T>& right ///< [in] 比較対象のオペランド
  ) const
  {
    return mObjPtr == right.mObjPtr;
  }

  /// @brief 非等価比較演算子
  bool
  operator!=(
    const ClibObjIterator<T>& right ///< [in] 比較対象のオペランド
  ) const
  {
    return !operator==(right);
  }


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
  ClibObjList(
    const vector<T*>& src_list ///< [in] ソースリスト
  )
  {
    init(src_list);
  }

  /// @brief デストラクタ
  ~ClibObjList()
  {
    delete [] mBody;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を(再)設定する．
  ///
  /// 以前の内容は破棄される．
  void
  init(
    const vector<T*>& src_list ///< [in] ソースリスト
  )
  {
    delete [] mBody;
    mNum = src_list.size();
    mBody = new T*[mNum];
    for ( int i = 0; i < mNum; ++ i ) {
      mBody[i] = src_list[i];
    }
  }

  /// @brief 要素数を返す．
  int
  num() const
  {
    return mNum;
  }

  /// @brief 要素を返す．
  const T&
  operator[](
    int pos ///< [in] 要素の位置 ( 0 <= pos < num() )
  ) const
  {
    ASSERT_COND( pos >= 0 && pos < num() );

    return *mBody[pos];
  }

  /// @brief 先頭の反復子を返す．
  ClibObjIterator<T>
  begin() const
  {
    return ClibObjIterator<T>(mBody);
  }

  /// @brief 末尾の反復子を返す．
  ClibObjIterator<T>
  end() const
  {
    return ClibObjIterator<T>(mBody + num());
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素数
  int mNum{0};

  // 要素(のポインタ)の配列
  T** mBody{nullptr};

};

END_NAMESPACE_YM_CLIB

#endif // CLIBOBJLIST_H
