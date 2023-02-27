#ifndef FFINFO_H
#define FFINFO_H

/// @file FFInfo.h
/// @brief FFInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/FLInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FFInfo FFInfo.h "FFInfo.h"
/// @brief FF グループの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class FFInfo :
  public FLInfo
{
public:

  /// @brief コンストラクタ
  FFInfo() = default;

  /// @brief デストラクタ
  ~FFInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 情報をセットする．
  bool
  set(
    const AstValue* ast_val
  );

  /// @brief clocked_on の値を返す．
  const AstExpr*
  clocked_on() const
  {
    return mClockedOn;
  }

  /// @brief clocked_on_also の値を返す．
  const AstExpr*
  clocked_on_also() const
  {
    return mClockedOnAlso;
  }

  /// @brief next_state の値を返す．
  const AstExpr*
  next_state() const
  {
    return mNextState;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  const AstExpr* mClockedOn{nullptr};

  const AstExpr* mClockedOnAlso{nullptr};

  const AstExpr* mNextState{nullptr};

};

END_NAMESPACE_YM_DOTLIB

#endif // FFINFO_H
