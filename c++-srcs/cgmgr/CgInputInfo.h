#ifndef CGINPUTINFO_H
#define CGINPUTINFO_H

/// @file CgInputInfo.h
/// @brief CgInputInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "CgPolInfo.h"


BEGIN_NAMESPACE_YM_CLIB

/// @brief 入力に関する情報
struct CgInputInfo
{
  // 入力番号
  SizeType mId;
  // 極性
  CgPolInfo mPol;
  // 出力関数の Walsh_1 の和
  int mFuncW1;
  // tristate関数の Walsh_1 の和
  int mTristateW1;
  // 代表元へのポインタ
  CgInputInfo* mRep;
  // 逆相の代表元へのポインタ
  CgInputInfo* mRevRep;
};

// 大小比較関数
inline
bool
operator<(
  const CgInputInfo& a,
  const CgInputInfo& b
)
{
  if ( a.mFuncW1 < b.mFuncW1 ) {
    return true;
  }
  else if ( a.mFuncW1 > b.mFuncW1 ) {
    return false;
  }
  else {
    return a.mTristateW1 < b.mTristateW1;
  }
}

// 等価比較関数
inline
bool
operator==(
  const CgInputInfo& a,
  const CgInputInfo& b
)
{
  return a.mFuncW1 == b.mFuncW1 && a.mTristateW1 == b.mTristateW1;
}

END_NAMESPACE_YM_CLIB

#endif // CGINPUTINFO_H
