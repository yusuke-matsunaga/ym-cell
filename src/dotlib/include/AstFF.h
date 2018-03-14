﻿#ifndef ASTFF_H
#define ASTFF_H

/// @file AstFF.h
/// @brief AstFF のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstFL.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFF AstFF.h "AstFF.h"
/// @brief AstNode の木から取り出した FF の情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstFF :
  public AstFL
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] var1, var2 変数名
  /// @param[in] clear クリア条件
  /// @param[in] preset プリセット条件
  /// @param[in] clear_preset_var1 'clear_preset_var1'
  /// @param[in] clear_preset_var2 'clear_preset_var2'
  /// @param[in] next_state 次状態遷移条件
  /// @param[in] clocked_on クロック条件
  /// @param[in] clocked_on_also 追加クロック条件
  AstFF(const FileRegion& loc,
	const AstString* var1,
	const AstString* var2,
	const AstExpr* clear,
	const AstExpr* preset,
	int clear_preset_var1,
	int clear_preset_var2,
	const AstExpr* next_state,
	const AstExpr* clocked_on,
	const AstExpr* clocked_on_also);

  /// @brief デストラクタ
  virtual
  ~AstFF();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "next_state" を返す．
  const AstExpr*
  next_state() const;

  /// @brief "clocked_on" を返す．
  const AstExpr*
  clocked_on() const;

  /// @brief "clocked_on_also" を返す．
  const AstExpr*
  clocked_on_also() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // next_state
  const AstExpr* mNextState;

  // clocked_on
  const AstExpr* mClockedOn;

  // clocked_on_also
  const AstExpr* mClockedOnAlso;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "next_state" を返す．
inline
const AstExpr*
AstFF::next_state() const
{
  return mNextState;
}

// @brief "clocked_on" を返す．
inline
const AstExpr*
AstFF::clocked_on() const
{
  return mClockedOn;
}

// @brief "clocked_on_also" を返す．
inline
const AstExpr*
AstFF::clocked_on_also() const
{
  return mClockedOnAlso;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFF_H
