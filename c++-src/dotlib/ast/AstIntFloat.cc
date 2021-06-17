
/// @file AstIntFloat.cc
/// @brief AstIntFloat の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstIntFloat.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstIntFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstIntFloat::AstIntFloat(const AstInt* value1,
			 const AstFloat* value2)
  : mValue1{value1},
    mValue2{value2}
{
}

// @brief デストラクタ
AstIntFloat::~AstIntFloat()
{
  delete mValue1;
  delete mValue2;
}

// @brief ファイル上の位置を返す．
FileRegion
AstIntFloat::loc() const
{
  return FileRegion(mValue1->loc(), mValue2->loc());
}

// @brief 内容をストリーム出力する．
void
AstIntFloat::dump(ostream& s,
		  int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
