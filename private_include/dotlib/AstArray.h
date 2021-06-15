#ifndef ASTARRAY_H
#define ASTARRAY_H

/// @file AstArray.h
/// @brief AstArray のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"


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
  AstArray(const vector<T>& src)  ///< [in] もとのオブジェクト
    : mSize{src.size()},
      mBody{new T[mSize]}
  {
    for ( SizeType i = 0; i < mSize; ++ i ) {
      mBody[i] = src[i];
    }
  }

  /// @brief コピーコンストラクタ
  AstArray(const AstArray& src) = default;

  /// @brief コピー代入演算子
  AstArray&
  operator=(const AstArray& src) = default;

  /// @brief デストラクタ
  ~AstArray()
  {
    delete [] mBody;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素数を返す．
  SizeType
  size() const
  {
    return mSize;
  }

  /// @brief 要素を返す．
  T
  operator[](SizeType pos) const ///< [in] 位置番号 ( 0 <= pos < size() )
  {
    ASSERT_COND( 0 <= pos && pos < size() );

    return mBody[pos];
  }

  /// @brief 先頭の反復子を返す．
  iterator
  begin() const
  {
    return mBody;
  }

  /// @brief 末尾の反復子を返す．
  iterator
  end() const
  {
    return mBody + mSize;
  }


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

END_NAMESPACE_YM_DOTLIB

#endif // ASTARRAY_H
