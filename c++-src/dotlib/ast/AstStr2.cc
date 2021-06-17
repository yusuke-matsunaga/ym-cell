
/// @file AstStr2.cc
/// @brief AstStr2 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstStr2.h"
#include "dotlib/AstString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstStr2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstStr2::AstStr2(const AstString* value1,
		 const AstString* value2)
  : mVal1{value1},
    mVal2{value2}
{
}

// @brief デストラクタ
AstStr2::~AstStr2()
{
  delete mVal1;
  delete mVal2;
}

// @brief 内容をストリーム出力する．
void
AstStr2::dump(ostream& s,
	      int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
