#ifndef FFHANDLER_H
#define FFHANDLER_H

/// @file FFHandler.h
/// @brief FFHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FLHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FFHandler FFHandler.h "FFHandler.h"
/// @brief 'FF' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * ヘッダの２つの文字列は状態を表す変数(肯定, 否定)を表す．
/// * Simple Attributes
///   - clear : "Boolean expression" ;
///   - clear_preset_var1 : L | H | N | T | X ;
///   - clear_preset_var2 : L | H | N | T | X ;
///   - clocked_on : "Boolean expression" ;
///   - clocked_on_also : "Boolean expression" ;
///   - next_state : "Boolean expression" ;
///   - preset : "Boolean expression" ;
//////////////////////////////////////////////////////////////////////
class FFHandler :
  public FLHandler
{
public:

  /// @brief コンストラクタ
  FFHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~FFHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief clocked_on を返す．
  const AstExpr*
  clocked_on() const
  {
    return mClockedOn;
  }

  /// @brief clocked_on_also を返す．
  const AstExpr*
  clocked_on_also() const
  {
    return mClockedOnAlso;
  }

  /// @brief next_state を返す．
  const AstExpr*
  next_state() const
  {
    return mNextState;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group() override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clocked_on
  const AstExpr* mClockedOn;

  // clocked_on_also
  const AstExpr* mClockedOnAlso;

  // next_state
  const AstExpr* mNextState;

};

END_NAMESPACE_YM_DOTLIB

#endif // FFHANDLER_H
