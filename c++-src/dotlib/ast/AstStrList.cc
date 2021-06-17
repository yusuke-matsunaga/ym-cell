
/// @file AstStrList.cc
/// @brief AstStrList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstStrList.h"
#include "dotlib/AstString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス AstStrList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstStrList::AstStrList(const vector<AstString*>& str_list,
		       const FileRegion& loc)
  : mBody{str_list},
    mLoc{loc}
{
}

// @brief デストラクタ
AstStrList::~AstStrList()
{
}

// @brief ファイル上の位置を返す．
FileRegion
AstStrList::loc() const
{
  return mLoc;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStrList::dump(ostream& s,
		 int indent) const
{
  const char* comma = "";
  for ( auto str: mBody ) {
    s << comma;
    comma = ", ";
    dump_string(s, str->value());
  }
}

END_NAMESPACE_YM_DOTLIB
