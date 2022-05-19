#ifndef CGOUTPUTINFO_H
#define CGOUTPUTINFO_H

/// @file CgOutputInfo.h
/// @brief CgOutputInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "CgPolInfo.h"


BEGIN_NAMESPACE_YM_CLIB

/// @brief 出力に関する情報
struct CgOutputInfo
{
  // 出力番号
  SizeType mId;
  // 極性
  CgPolInfo mPol;
  // 出力の Walsh_0
  int mFuncW0;
  // tristate 関数の Walsh_0
  int mTristateW0;
};

/// @brief 大小比較関数
inline
bool
operator<(
  const CgOutputInfo& a,
  const CgOutputInfo& b
)
{
  if ( a.mFuncW0 < b.mFuncW0 ) {
    return true;
  }
  else if ( a.mFuncW0 > b.mFuncW0 ) {
    return false;
  }
  else {
    return a.mTristateW0 < b.mTristateW0;
  }
}

/// @brief 等価比較関数
inline
bool
operator==(
  const CgOutputInfo& a,
  const CgOutputInfo& b
)
{
  return a.mFuncW0 == b.mFuncW0 && a.mTristateW0 == b.mTristateW0;
}

/// @brief 等価比較関数
inline
bool
operator!=(
  const CgOutputInfo& a,
  const CgOutputInfo& b
)
{
  return !operator==(a, b);
}

END_NAMESPACE_YM_CLIB

#endif // CGOUTPUTINFO_H
