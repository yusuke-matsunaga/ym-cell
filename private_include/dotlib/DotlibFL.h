#ifndef DOTLIBFL_H
#define DOTLIBFL_H

/// @file DotlibFL.h
/// @brief DotlibFL のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibFL DotlibFL.h "DotlibFL.h"
/// @brief DotlibFF と DotlibLatch の基底クラス
//////////////////////////////////////////////////////////////////////
class DotlibFL :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] var1, var2 変数名
  /// @param[in] clear クリア条件
  /// @param[in] preset プリセット条件
  /// @param[in] clear_preset_var1 'clear_preset_var1'
  /// @param[in] clear_preset_var2 'clear_preset_var2'
  DotlibFL(const FileRegion& loc,
	   const ShString var1,
	   const ShString var2,
	   const DotlibExpr* clear,
	   const DotlibExpr* preset,
	   int clear_preset_var1,
	   int clear_preset_var2);

  /// @brief デストラクタ
  virtual
  ~DotlibFL();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief var1 の名前を返す．
  ShString
  var1_name() const;

  /// @brief var2 の名前を返す．
  ShString
  var2_name() const;

  /// @brief "clear" を返す．
  const DotlibExpr*
  clear() const;

  /// @brief "preset" を返す．
  const DotlibExpr*
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
  ShString mVar1;

  // var2
  ShString mVar2;

  // clear
  const DotlibExpr* mClear;

  // preset
  const DotlibExpr* mPreset;

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
ShString
DotlibFL::var1_name() const
{
  return mVar1;
}

// @brief var2 の名前を返す．
inline
ShString
DotlibFL::var2_name() const
{
  return mVar2;
}

// @brief "clear" を返す．
inline
const DotlibExpr*
DotlibFL::clear() const
{
  return mClear;
}

// @brief "preset" を返す．
inline
const DotlibExpr*
DotlibFL::preset() const
{
  return mPreset;
}

// @brief "clear_preset_var1" を返す．
inline
int
DotlibFL::clear_preset_var1() const
{
  return mClearPresetVar1;
}

// @brief "clear_preset_var2" を返す．
inline
int
DotlibFL::clear_preset_var2() const
{
  return mClearPresetVar2;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBFF_H
