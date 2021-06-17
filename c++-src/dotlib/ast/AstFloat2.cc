
/// @file AstFloat2.cc
/// @brief AstFloat2 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloat.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFloat2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloat2::AstFloat2(const AstFloat* value1,
		     const AstFloat* value2)
  : mVal1{value1},
    mVal2{value2}
{
}

// @brief デストラクタ
AstFloat2::~AstFloat2()
{
}

// @brief ファイル上の位置を返す．
FileRegion
AstFloat2::loc() const
{
  return FileRegion(mVal1->loc(), mVal2->loc());
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloat2::dump(ostream& s,
		int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
