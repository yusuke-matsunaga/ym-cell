
/// @file AstFL.cc
/// @brief AstFL の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFL.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFL
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFL::AstFL(const FileRegion& attr_loc,
	     const StrStrHandler& header,
	     const FLHandler& group) :
  AstNode{FileRegion{attr_loc, group.group_loc()}},
  mVar1{header.value1()},
  mVar2{header.value2()},
  mClear{group.clear()},
  mPreset{group.preset()},
  mClearPresetVar1{group.clear_preset_var1()},
  mClearPresetVar2{group.clear_preset_var2()}
{
}

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFL::AstFL(const FileRegion& attr_loc,
	     const StrStrIntHandler& header,
	     const FFHandler& group) :
  AstNode{FileRegion{attr_loc, group.group_loc()}},
  mVar1{header.value1()},
  mVar2{header.value2()},
  mClear{group.clear()},
  mPreset{group.preset()},
  mClearPresetVar1{group.clear_preset_var1()},
  mClearPresetVar2{group.clear_preset_var2()}
{
}

// @brief デストラクタ
AstFL::~AstFL()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFL::dump(ostream& s,
	    int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
