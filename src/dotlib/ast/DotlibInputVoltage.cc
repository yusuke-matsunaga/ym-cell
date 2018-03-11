
/// @file DotlibInputVoltage.cc
/// @brief DotlibInputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibInputVoltage.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibInputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] vil 'vil'
// @param[in] vih 'vih'
// @param[in] vimin 'vimin'
// @param[in] vimax 'vimax'
DotlibInputVoltage::DotlibInputVoltage(const FileRegion& loc,
				       const DotlibString* name,
				       const DotlibExpr* vil,
				       const DotlibExpr* vih,
				       const DotlibExpr* vimin,
				       const DotlibExpr* vimax) :
  DotlibNode(loc),
  mName(name),
  mVil(vil),
  mVih(vih),
  mViMin(vimin),
  mViMax(vimax)
{
}

// @brief デストラクタ
DotlibInputVoltage::~DotlibInputVoltage()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibInputVoltage::dump(ostream& s,
			 int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
