#ifndef ASTLATCHINFO_H
#define ASTLATCHINFO_H

/// @file AstLatchInfo.h
/// @brief AstLatchInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstFLInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLatchInfo AstLatchInfo.h "AstLatchInfo.h"
/// @brief ラッチグループの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLatchInfo :
  public AstFLInfo
{
public:

  /// @brief コンストラクタ
  AstLatchInfo() = default;

  /// @brief デストラクタ
  ~AstLatchInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 情報をセットする．
  bool
  set(
    const AstValue* ast_val
  );

  /// @brief enable_on の値を返す．
  const AstExpr*
  enable_on() const
  {
    return mEnableOn;
  }

  /// @brief enable_on_also の値を返す．
  const AstExpr*
  enable_on_also() const
  {
    return mEnableOnAlso;
  }

  /// @brief data_in の値を返す．
  const AstExpr*
  data_in() const
  {
    return mDataIn;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // enable_on の値
  const AstExpr* mEnableOn;

  // enable_on_also の値
  const AstExpr* mEnableOnAlso;

  // data_in の値
  const AstExpr* mDataIn;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTLATCHINFO_H
