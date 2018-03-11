
/// @file DotlibUnit.cc
/// @brief DotlibUnit の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibUnit.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibUnit
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] unit_val 数値
// @param[in] unit_str 単位を表す文字列
DotlibUnit::DotlibUnit(const FileRegion& loc,
		       double unit_val,
		       const ShString& unit_str) :
  DotlibNode(loc),
  mVal(unit_val),
  mStr(unit_str)
{
}

// @brief デストラクタ
DotlibUnit::~DotlibUnit()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibUnit::dump(ostream& s,
		 int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
