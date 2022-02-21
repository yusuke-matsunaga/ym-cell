#ifndef ASTFFINFO_H
#define ASTFFINFO_H

/// @file AstFFInfo.h
/// @brief AstFFInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstFLInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFFInfo AstFFInfo.h "AstFFInfo.h"
/// @brief FF グループの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstFFInfo :
  public AstFLInfo
{
public:

  /// @brief コンストラクタ
  AstFFInfo() = default;

  /// @brief デストラクタ
  ~AstFFInfo() = default;


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

  const AstExpr* mClockedOn;
  const AstExpr* mClockedOnAlso;
  const AstExpr* mNextState;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFFINFO_H
