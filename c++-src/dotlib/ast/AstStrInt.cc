
/// @file AstStrInt.cc
/// @brief AstStrInt の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstStrInt.h"
#include "dotlib/AstString.h"
#include "dotlib/AstInt.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstStrInt
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstStrInt::AstStrInt(const AstString* value1,
		     const AstInt* value2)
  : mVal1{value1},
    mVal2{value2}
{
}

// @brief デストラクタ
AstStrInt::~AstStrInt()
{
  delete mVal1;
  delete mVal2;
}

// @brief ファイル上の位置を返す．
FileRegion
AstStrInt::loc() const
{
  return FileRegion(mVal1->loc(), mVal2->loc());
}

// @brief 内容をストリーム出力する．
void
AstStrInt::dump(ostream& s,
		int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
