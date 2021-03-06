﻿
/// @file AstStateTable.cc
/// @brief AstStateTable の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstStateTable.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstStateTable
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] var1, var2 変数名
// @param[in] clear クリア条件
// @param[in] preset プリセット条件
// @param[in] clear_preset_var1 'clear_preset_var1'
// @param[in] clear_preset_var2 'clear_preset_var2'
// @param[in] next_state 次状態遷移条件
// @param[in] clocked_on クロック条件
// @param[in] clocked_on_also 追加クロック条件
AstStateTable::AstStateTable(const FileRegion& loc,
			     const AstString* var1,
			     const AstString* var2,
			     const AstExpr* clear,
			     const AstExpr* preset,
			     const AstCPType* clear_preset_var1,
			     const AstCPType* clear_preset_var2,
			     const AstExpr* next_state,
			     const AstExpr* clocked_on,
			     const AstExpr* clocked_on_also) :
  AstFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mNextState(next_state),
  mClockedOn(clocked_on),
  mClockedOnAlso(clocked_on_also)
{
}

// @brief デストラクタ
AstStateTable::~AstStateTable()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStateTable::dump(ostream& s,
		    int indent) const
{
  #warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
