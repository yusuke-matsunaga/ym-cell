#ifndef FLHANDLER_H
#define FLHANDLER_H

/// @file FLHandler.h
/// @brief FLHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FLHandler FLHandler.h "FLHandler.h"
/// @brief 'FF'/Latch Group Statement 用のハンドラ
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
class FLHandler :
  public GroupHandler
{
  friend class AstFL;

public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FLHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~FLHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


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

  // clear
  const AstExpr* mClear;

  // preset
  const AstExpr* mPreset;

  // clear_preset_var1
  const AstCPType* mClearPresetVar1;

  // clear_preset_var2
  const AstCPType* mClearPresetVar2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

END_NAMESPACE_YM_DOTLIB

#endif // FFHANDLER_H
