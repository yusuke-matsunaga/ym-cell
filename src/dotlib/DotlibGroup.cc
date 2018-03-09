
/// @file DotlibNodeImpl.cc
/// @brief DotlibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNodeImpl.h"
#include "DotlibAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

// インデント用の空白文字列を作る．
string
indent_str(int indent)
{
  string ans;
  for (int i = 0; i < indent; ++ i) {
    ans += ' ';
  }
  return ans;
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス DotlibGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibGroup::DotlibGroup(const DotlibNode* value,
			 const FileRegion& loc) :
  DotlibBase(loc),
  mValue(value),
  mAttrTop(nullptr),
  mAttrTail(nullptr)
{
}

// @brief デストラクタ
DotlibGroup::~DotlibGroup()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibGroup::dump(ostream& s,
		  int indent) const
{
  s << ' ';
  group_value()->dump(s, 0);
  s << " {" << endl;
  for ( const DotlibAttr* attr = attr_top(); attr; attr = attr->next() ) {
    attr->dump(s, indent + 2);
  }
  s << indent_str(indent) << "}";
}

END_NAMESPACE_YM_DOTLIB
