
/// @file DotlibTimingType.cc
/// @brief DotlibTimingType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibTimingType.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTimingType::DotlibTimingType(const FileRegion& loc,
				   ClibTimingType value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTimingType::~DotlibTimingType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTimingType::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibTimingCombinational: dump_string(s, "combinational"); break;
  default: dump_string(s, "---"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
