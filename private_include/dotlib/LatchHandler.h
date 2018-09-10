#ifndef LATCHHANDLER_H
#define LATCHHANDLER_H

/// @file LatchHandler.h
/// @brief LatchHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str2GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class LatchHandler LatchHandler.h "LatchHandler.h"
/// @brief 'latch' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * ヘッダの2つの文字列は状態を表す変数(肯定, 否定)を表す．
/// * Simple Attributes
///   - clear : "Boolean expression" ;
///   - clear_preset_var1 : L | H | N | T | X ;
///   - clear_preset_var2 : L | H | N | T | X ;
///   - data_in : "Boolean expression" ;
///   - enable_on : "Boolean expression" ;
///   - enable_on_also : "Boolean expression" ;
///   - preset : "Boolean expression" ;
//////////////////////////////////////////////////////////////////////
class LatchHandler :
  public Str2GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  LatchHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~LatchHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif latch Group Statement の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstLatch*& dst);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


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

  // enable_on
  const AstExpr* mEnableOn;

  // enable_on_also
  const AstExpr* mEnableOnAlso;

  // data_in
  const AstExpr* mDataIn;

  // 読み込んだ値
  const AstLatch* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // LATCHHANDLER_H