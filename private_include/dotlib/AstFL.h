﻿#ifndef ASTFL_H
#define ASTFL_H

/// @file AstFL.h
/// @brief AstFL のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFL AstFL.h "AstFL.h"
/// @brief AstFF と AstLatch の基底クラス
//////////////////////////////////////////////////////////////////////
class AstFL :
  public AstNode
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
  AstFL(const FileRegion& loc,
	const AstString* var1,
	const AstString* var2,
	const AstExpr* clear,
	const AstExpr* preset,
	int clear_preset_var1,
	int clear_preset_var2);

  /// @brief デストラクタ
  virtual
  ~AstFL();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief var1 の名前を返す．
  const AstString*
  var1_name() const;

  /// @brief var2 の名前を返す．
  const AstString*
  var2_name() const;

  /// @brief "clear" を返す．
  const AstExpr*
  clear() const;

  /// @brief "preset" を返す．
  const AstExpr*
  preset() const;

  /// @brief "clear_preset_var1" を返す．
  int
  clear_preset_var1() const;

  /// @brief "clear_preset_var2" を返す．
  int
  clear_preset_var2() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // var1
  const AstString* mVar1;

  // var2
  const AstString* mVar2;

  // clear
  const AstExpr* mClear;

  // preset
  const AstExpr* mPreset;

  // clear_preset_var1
  int mClearPresetVar1;

  // clear_preset_var2
  int mClearPresetVar2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief var1 の名前を返す．
inline
const AstString*
AstFL::var1_name() const
{
  return mVar1;
}

// @brief var2 の名前を返す．
inline
const AstString*
AstFL::var2_name() const
{
  return mVar2;
}

// @brief "clear" を返す．
inline
const AstExpr*
AstFL::clear() const
{
  return mClear;
}

// @brief "preset" を返す．
inline
const AstExpr*
AstFL::preset() const
{
  return mPreset;
}

// @brief "clear_preset_var1" を返す．
inline
int
AstFL::clear_preset_var1() const
{
  return mClearPresetVar1;
}

// @brief "clear_preset_var2" を返す．
inline
int
AstFL::clear_preset_var2() const
{
  return mClearPresetVar2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFL_H
