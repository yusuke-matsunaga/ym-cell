#ifndef ASTARRAY_H
#define ASTARRAY_H

/// @file AstArray.h
/// @brief AstArray のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2019 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstArray AstArray.h "AstArray.h"
/// @brief Astの要素の配列を表すテンプレートクラス
//////////////////////////////////////////////////////////////////////
template<typename T>
class AstArray
{
public:

  /// @brief 反復子を表す型
  using iterator = T*;

public:

  /// @brief コンストラクタ
  /// @param[in] src もとのオブジェクト
  /// @param[in] alloc メモリアロケータ
  AstArray(const vector<T>& src,
	   Alloc& alloc);

  /// @brief コピーコンストラクタ
  AstArray(const AstArray& src) = default;

  /// @brief コピー代入演算子
  AstArray&
  operator=(const AstArray& src) = default;

  /// @brief デストラクタ
  ~AstArray();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  SizeType
  size() const;

  /// @brief 要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < size() )
  T
  operator[](SizeType pos) const;

  /// @brief 先頭の反復子を返す．
  iterator
  begin() const;

  /// @brief 末尾の反復子を返す．
  iterator
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
  SizeType mSize;

  // 要素の配列
  T* mBody;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] src もとのオブジェクト
// @param[in] alloc メモリアロケータ
template<typename T>
inline
AstArray<T>::AstArray(const vector<T>& src,
		      Alloc& alloc) :
  mSize{src.size()}
{
  void* p = alloc.get_memory(sizeof(T) * mSize);
  mBody = new (p) T[mSize];
  for ( SizeType i = 0; i < mSize; ++ i ) {
    mBody[i] = src[i];
  }
}

// @brief デストラクタ
template<typename T>
AstArray<T>::~AstArray()
{
}

// @brief 要素数を返す．
template<typename T>
inline
SizeType
AstArray<T>::size() const
{
  return mSize;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < size() )
template<typename T>
inline
T
AstArray<T>::operator[](SizeType pos) const
{
  ASSERT_COND( 0 <= pos && pos < size() );

  return mBody[pos];
}

// @brief 先頭の反復子を返す．
template<typename T>
inline
typename AstArray<T>::iterator
AstArray<T>::begin() const
{
  return mBody;
}

// @brief 末尾の反復子を返す．
template<typename T>
inline
typename AstArray<T>::iterator
AstArray<T>::end() const
{
  return mBody + mSize;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTARRAY_H
