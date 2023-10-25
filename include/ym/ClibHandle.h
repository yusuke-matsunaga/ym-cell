#ifndef CLIBHANDLE_H
#define CLIBHANDLE_H

/// @file ClibHandle.h
/// @brief ClibHandle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibLibraryPtr.h"
#include "ym/ClibCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibHandle ClibHandle.h "ClibHandle.h"
/// @brief Clib の要素を表す基底クラス
//////////////////////////////////////////////////////////////////////
class ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibHandle() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibHandle(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : mLibrary{library},
      mId{id}
  {
    if ( id == CLIB_NULLID ) {
      // 不正値にしておく．
      mLibrary = nullptr;
    }
  }

  /// @brief デストラクタ
  ~ClibHandle() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 適正な値を持っている時 true を返す．
  bool
  is_valid() const
  {
    return mLibrary.is_valid();
  }

  /// @brief 不正値の時 true を返す．
  bool
  is_invalid() const
  {
    return !is_valid();
  }

  /// @brief セルライブラリを返す．
  ClibCellLibrary
  library() const
  {
    return ClibCellLibrary{mLibrary};
  }


protected:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  ClibLibraryPtr mLibrary;

  // ID番号
  SizeType mId{CLIB_NULLID};

};

END_NAMESPACE_YM_CLIB

#endif // CLIBHANDLE_H
