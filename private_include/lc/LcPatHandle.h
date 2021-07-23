#ifndef LCPATHANDLE_H
#define LCPATHANDLE_H

/// @file LcPatHandle.h
/// @brief LcPatHandle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

class LcPatNode;

//////////////////////////////////////////////////////////////////////
/// @class LcPatHandle LcPatHandle.h "LcPatHandle.h"
/// @brief LcPatNode と極性を表すクラス
//////////////////////////////////////////////////////////////////////
class LcPatHandle
{
public:

  /// @brief コンストラクタ
  explicit
  LcPatHandle(
    LcPatNode* node = nullptr, ///< [in] ノード
    bool inv = false           ///< [in] 反転属性
  )
  {
    set(node, inv);
  }

  /// @brief デストラクタ
  ~LcPatHandle() = default;


public:

  /// @brief ノードを取り出す．
  const LcPatNode&
  node() const
  {
    return *reinterpret_cast<LcPatNode*>(mData & ~1UL);
  }

  /// @brief 反転属性を取り出す．
  bool
  inv() const
  {
    return static_cast<bool>(mData & 1UL);
  }

  /// @brief 値を設定する．
  void
  set(
    LcPatNode* node, ///< [in] ノード
    bool inv         ///< [in] 反転属性
  )
  {
    // bool に対する & 1UL は不必要だが念のため．
    mData = reinterpret_cast<ympuint>(node) | (static_cast<ympuint>(inv) & 1UL);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ポインタと反転属性を合わせたもの
  ympuint mData;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCPATHANDLE_H
