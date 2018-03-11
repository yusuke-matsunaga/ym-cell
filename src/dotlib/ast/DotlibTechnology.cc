
/// @file DotlibTechnology.cc
/// @brief DotlibTechnology の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibTechnology.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTechnology::DotlibTechnology(const FileRegion& loc,
				   ClibTechnology value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTechnology::~DotlibTechnology()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTechnology::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibTechCmos: dump_string(s, "cmos"); break;
  case kClibTechFpga: dump_string(s, "fpga"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
