
/// @file DotlibGenGroup.cc
/// @brief DotlibGenGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibGenGroup.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibGenGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
DotlibGenGroup::DotlibGenGroup(const FileRegion& loc,
			       const DotlibList* value_list,
			       const DotlibAttr* attr_top) :
  DotlibNode(loc),
  mValueList(value_list),
  mAttrTop(attr_top)
{
}

// @brief デストラクタ
DotlibGenGroup::~DotlibGenGroup()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibGenGroup::dump(ostream& s,
		     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
