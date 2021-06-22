
/// @file AstAttr.cc
/// @brief AstAttr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 内容をストリーム出力する．
void
AstAttr::dump(ostream& s,
	      int ilevel) const
{
  dump_indent(s, ilevel);
  s << attr().type();
  value().dump(s, ilevel);
}

END_NAMESPACE_YM_DOTLIB
