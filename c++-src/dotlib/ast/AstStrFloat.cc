
/// @file AstStrFloat.cc
/// @brief AstStrFloat の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstFloat.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstStrFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstStrFloat::AstStrFloat(const AstString* value1,
			 const AstFloat* value2)
  : mVal1{value1},
    mVal2{value2}
{
}

// @brief デストラクタ
AstStrFloat::~AstStrFloat()
{
  delete mVal1;
  delete mVal2;
}

// @brief 内容をストリーム出力する．
void
AstStrFloat::dump(ostream& s,
		  int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
