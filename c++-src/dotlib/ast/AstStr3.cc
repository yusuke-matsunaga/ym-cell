
/// @file AstStr3.cc
/// @brief AstStr3 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstStr3.h"
#include "dotlib/AstString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstStr3
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstStr3::AstStr3(const AstString* value1,
		 const AstString* value2,
		 const AstString* value3)
  : mVal1{value1},
    mVal2{value2},
    mVal3{value3}
{
}

// @brief デストラクタ
AstStr3::~AstStr3()
{
  delete mVal1;
  delete mVal2;
  delete mVal3;
}

// @brief 内容をストリーム出力する．
void
AstStr3::dump(ostream& s,
	      int indent) const
{
  s << "(" << value1()->value()
    << ", " << value2()->value()
    << ", " << value3()->value()
    << ")";
}

END_NAMESPACE_YM_DOTLIB
