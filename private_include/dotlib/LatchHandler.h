#ifndef LATCHHANDLER_H
#define LATCHHANDLER_H

/// @file LatchHandler.h
/// @brief LatchHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FLHandler.h"


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
  public FLHandler
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

  /// @brief enable_on を返す．
  const AstExpr*
  enable_on() const;

  /// @brief enable_on_also を返す．
  const AstExpr*
  enable_on_also() const;

  /// @brief data_in を返す．
  const AstExpr*
  data_in() const;


protected:
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

  // enable_on
  const AstExpr* mEnableOn;

  // enable_on_also
  const AstExpr* mEnableOnAlso;

  // data_in
  const AstExpr* mDataIn;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief enable_on を返す．
inline
const AstExpr*
LatchHandler::enable_on() const
{
  return mEnableOn;
}

// @brief enable_on_also を返す．
inline
const AstExpr*
LatchHandler::enable_on_also() const
{
  return mEnableOnAlso;
}

// @brief data_in を返す．
inline
const AstExpr*
LatchHandler::data_in() const
{
  return mDataIn;
}

END_NAMESPACE_YM_DOTLIB

#endif // LATCHHANDLER_H
