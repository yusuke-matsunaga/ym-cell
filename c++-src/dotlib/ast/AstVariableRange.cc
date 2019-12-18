
/// @file AstVariableRange.cc
/// @brief AstVariableRange の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstVariableRange.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief variable_n_range を表す AstNode を生成する．
// @param[in] value1, value2 値
AstVariableRange*
AstMgr::new_variable_range(const AstFloat* value1,
			   const AstFloat* value2)
{
  ++ mVarRangeNum;
  auto node = new AstVariableRange(value1, value2);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstVariableRange
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] val1, val2 値
AstVariableRange::AstVariableRange(const AstFloat* val1,
				   const AstFloat* val2) :
  AstNode(FileRegion(val1->loc(), val2->loc())),
  mVal1(val1),
  mVal2(val2)
{
}

// @brief デストラクタ
AstVariableRange::~AstVariableRange()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstVariableRange::dump(ostream& s,
		       int indent) const
{
#warning "TODO: 未完"
}

END_NAMESPACE_YM_DOTLIB
