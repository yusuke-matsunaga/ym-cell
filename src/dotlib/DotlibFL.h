#ifndef DOTLIBFL_H
#define DOTLIBFL_H

/// @file DotlibFL.h
/// @brief DotlibFL のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibFL DotlibFL.h "DotlibFL.h"
/// @brief DotlibFF と DotlibLatch の基底クラス
//////////////////////////////////////////////////////////////////////
class DotlibFL
{
public:

  /// @brief コンストラクタ
  DotlibFL();

  /// @brief デストラクタ
  ~DotlibFL();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  bool
  set_data(const DotlibNode* node);

  /// @brief var1 の名前を返す．
  ShString
  var1_name() const;

  /// @brief var2 の名前を返す．
  ShString
  var2_name() const;

  /// @brief "clear" を返す．
  const DotlibNode*
  clear() const;

  /// @brief "preset" を返す．
  const DotlibNode*
  preset() const;

  /// @brief "clear_preset_var1" を返す．
  int
  clear_preset_var1() const;

  /// @brief "clear_preset_var2" を返す．
  int
  clear_preset_var2() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief set_data() の下請け関数
  bool
  set_data_sub(const DotlibNode* node,
	       const DotlibAttrMap& attr_map);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // var1
  ShString mVar1;

  // var2
  ShString mVar2;

  // clear
  const DotlibNode* mClear;

  // preset
  const DotlibNode* mPreset;

  // clear_preset_var1
  int mClearPresetVar1;

  // clear_preset_var2
  int mClearPresetVar2;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBFF_H
