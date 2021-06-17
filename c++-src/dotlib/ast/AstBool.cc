
/// @file AstBool.cc
/// @brief AstBool の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstBool.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス AstBool
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstBool::AstBool(bool value,                 ///< [in] 値
		 const FileRegion& val_loc)  ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 内容をストリーム出力する．
void
AstBool::dump(ostream& s,
	      int indent) const
{
  const char* tmp = value() ? "true" : "false";
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
