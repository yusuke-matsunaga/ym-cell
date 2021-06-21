
/// @file AstFL.cc
/// @brief AstFL の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFL.h"
#include "dotlib/AstMgr.h"
#include "dotlib/StrStrHandler.h"
#include "dotlib/StrStrIntHandler.h"
#include "dotlib/FLHandler.h"


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
  mClear{group.mClear},
  mPreset{group.mPreset},
  mClearPresetVar1{group.mClearPresetVar1},
  mClearPresetVar2{group.mClearPresetVar2}
{
}

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFL::AstFL(const FileRegion& attr_loc,
	     const StrStrIntHandler& header,
	     const FLHandler& group) :
  AstNode{FileRegion{attr_loc, group.group_loc()}},
  mVar1{header.value1()},
  mVar2{header.value2()},
  mClear{group.mClear},
  mPreset{group.mPreset},
  mClearPresetVar1{group.mClearPresetVar1},
  mClearPresetVar2{group.mClearPresetVar2}
{
}

// @brief デストラクタ
AstFL::~AstFL()
{
}

END_NAMESPACE_YM_DOTLIB
