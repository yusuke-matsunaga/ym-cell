
/// @file AstTechnology.cc
/// @brief AstTechnology の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstTechnology.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstTechnology::AstTechnology(ClibTechnology value,      ///< [in] 値
			     const FileRegion& val_loc) ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTechnology::dump(ostream& s,
		    int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibTechnology::cmos: tmp = "cmos"; break;
  case ClibTechnology::fpga: tmp = "fpga"; break;
  default: break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
