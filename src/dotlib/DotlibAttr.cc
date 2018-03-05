
/// @file DotlibAttr.cc
/// @brief DotlibAttr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibAttr.h"
#include "DotlibNode.h"


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
// クラス DotlibAttr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_type 属性
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibAttr::DotlibAttr(AttrType attr_type,
		       const DotlibNode* value,
		       const FileRegion& loc) :
  mLoc(loc),
  mAttrType(attr_type),
  mValue(value),
  mNext(nullptr)
{
}

// @brief デストラクタ
DotlibAttr::~DotlibAttr()
{
}

// @brief ファイル上の位置を返す．
FileRegion
DotlibAttr::loc() const
{
  return mLoc;
}

// @brief 属性を得る．
AttrType
DotlibAttr::attr_type() const
{
  return mAttrType;
}

// @brief 属性の値を得る．
const DotlibNode*
DotlibAttr::attr_value() const
{
  return mValue;
}

// @brief 次の要素を得る．
const DotlibAttr*
DotlibAttr::next() const
{
  return mNext;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibAttr::dump(ostream& s,
		 int indent) const
{
  s << indent_str(indent) << attr_type() << ": ";
  attr_value()->dump(s, indent);
  if ( attr_value()->type() != DotlibNode::kGroup ) {
    s << ";";
  }
  s << endl;
}

END_NAMESPACE_YM_DOTLIB
