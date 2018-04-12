
/// @file AstAttr.cc
/// @brief AstAttr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstAttr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] attr_type 属性
// @param[in] value 値
AstAttr::AstAttr(const FileRegion& loc,
		 AttrType attr_type,
		 const AstNode* value) :
  AstNode(loc),
  mAttrType(attr_type),
  mValue(value)
{
}

// @brief デストラクタ
AstAttr::~AstAttr()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstAttr::dump(ostream& s,
	      int indent) const
{
  dump_indent(s, indent);
  s << attr_type() << ": ";
  attr_value()->dump(s, indent);
#if 0
  if ( attr_value()->type() != AstNode::kGroup ) {
    s << ";";
  }
#endif
  s << endl;
}

END_NAMESPACE_YM_DOTLIB
