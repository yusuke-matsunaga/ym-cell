
/// @file DotlibStateTable.cc
/// @brief DotlibStateTable の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibStateTable.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibStateTable
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
DotlibStateTable::DotlibStateTable(const FileRegion& loc,
				   const ShString var1,
				   const ShString var2,
				   const DotlibExpr* clear,
				   const DotlibExpr* preset,
				   int clear_preset_var1,
				   int clear_preset_var2,
				   const DotlibExpr* next_state,
				   const DotlibExpr* clocked_on,
				   const DotlibExpr* clocked_on_also) :
  DotlibFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mNextState(next_state),
  mClockedOn(clocked_on),
  mClockedOnAlso(clocked_on_also)
{
}

// @brief デストラクタ
DotlibStateTable::~DotlibStateTable()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibStateTable::dump(ostream& s,
		       int indent) const
{
  #warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
