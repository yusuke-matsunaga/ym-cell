
/// @file AstAttr.cc
/// @brief AstAttr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
AstAttr::AstAttr(AttrType attr_type,
		 const FileRegion& attr_loc,
		 const AstValue* value)
  : mAttrType{attr_typr},
    mAttrLoc{attr_loc},
    mValue{value}
{
}

// @brief 全体のファイル上の位置を返す．
FileRegion
AstAttr::loc() const
{
  return FileRegion{mAttrLoc, mValue->loc());
}

// @brief 内容をストリーム出力する．
void
AstAttr::dump(ostream& s,
	      int indent) const
{
  // 未完
}

END_NAMESPACE_YM_DOTLIB
