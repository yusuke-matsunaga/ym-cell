
/// @file AstFloatStr.cc
/// @brief AstFloatStr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFloatStr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloatStr::AstFloatStr(const AstFloat* value1,
			 const AstString* value2)
  : mVal1{value1},
    mVal2{value2}
{
}

// @brief デストラクタ
AstFloatStr::~AstFloatStr()
{
  delete mVal1;
  delete mVal2;
}

// @brief ファイル上の位置を返す．
FileRegion
AstFloatStr::loc() const
{
  return FileRegion(mVal1->loc(), mVal2->loc());
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloatStr::dump(ostream& s,
		  int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
