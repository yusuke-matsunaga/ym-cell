
/// @file DotlibTemplte.cc
/// @brief DotlibTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibTemplate.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTemplate
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] dimension 次元数
// @param[in] var_1, var_2, var_3 変数のタイプ
// @param[in] index_1, index_2, index_3 インデックスのベクタ
DotlibTemplate::DotlibTemplate(const FileRegion& loc,
			       const DotlibString* name,
			       int dimension,
			       const DotlibVarType* var_1,
			       const DotlibVarType* var_2,
			       const DotlibVarType* var_3,
			       const DotlibFloatVector* index_1,
			       const DotlibFloatVector* index_2,
			       const DotlibFloatVector* index_3) :
  DotlibNode(loc),
  mName(name),
  mDimension(dimension),
  mVar1(var_1),
  mVar2(var_2),
  mVar3(var_3),
  mIndex1(index_1),
  mIndex2(index_2),
  mIndex3(index_3)
{
}

// @brief デストラクタ
DotlibTemplate::~DotlibTemplate()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTemplate::dump(ostream& s,
		     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
