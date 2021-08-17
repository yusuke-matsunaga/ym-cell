#ifndef LIBCOMP_NSDEF_H
#define LIBCOMP_NSDEF_H

/// @file libcomp_nsdef.h
/// @brief libcomp 用の名前空間の定義
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"

/// @brief libcomp 用の名前空間の開始
#define BEGIN_NAMESPACE_YM_CLIB_LIBCOMP \
BEGIN_NAMESPACE_YM_CLIB \
BEGIN_NAMESPACE(nsLibcomp)

/// @brief libcomp 用の名前空間の終了
#define END_NAMESPACE_YM_CLIB_LIBCOMP \
END_NAMESPACE(nsLibcomp) \
END_NAMESPACE_YM_CLIB


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

/// @brief 種類を表す列挙型
enum class LcType {
  Logic = 0, ///< 組み合わせ論理
  FF    = 2, ///< FF
  Latch = 3  ///< ラッチ
};

class LibComp;
class LcClass;
class LcGroup;
class LcSignature;

class LcPatMgr;
class LcPatNode;
class LcPatHandle;

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LIBCOMP_NSDEF_H
