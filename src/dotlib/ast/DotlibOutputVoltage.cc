
/// @file DotlibOutputVoltage.cc
/// @brief DotlibOutputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibOutputVoltage.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibOutputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] vol 'vol'
// @param[in] voh 'voh'
// @param[in] vomin 'vomin'
// @param[in] vomax 'vomax'
DotlibOutputVoltage::DotlibOutputVoltage(const FileRegion& loc,
					 const DotlibString* name,
					 const DotlibExpr* vol,
					 const DotlibExpr* voh,
					 const DotlibExpr* vomin,
					 const DotlibExpr* vomax) :
  DotlibNode(loc),
  mName(name),
  mVol(vol),
  mVoh(voh),
  mVoMin(vomin),
  mVoMax(vomax)
{
}

// @brief デストラクタ
DotlibOutputVoltage::~DotlibOutputVoltage()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibOutputVoltage::dump(ostream& s,
			  int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
