#ifndef ASTFL_H
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
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstFL(const FileRegion& attr_loc,
	const StrStrHandler& header,
	const FLHandler& group);

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstFL(const FileRegion& attr_loc,
	const StrStrIntHandler& header,
	const FLHandler& group);

  /// @brief デストラクタ
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
  const AstCPType*
  clear_preset_var1() const;

  /// @brief "clear_preset_var2" を返す．
  const AstCPType*
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
  const AstCPType* mClearPresetVar1;

  // clear_preset_var2
  const AstCPType* mClearPresetVar2;

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
const AstCPType*
AstFL::clear_preset_var1() const
{
  return mClearPresetVar1;
}

// @brief "clear_preset_var2" を返す．
inline
const AstCPType*
AstFL::clear_preset_var2() const
{
  return mClearPresetVar2;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTFL_H
