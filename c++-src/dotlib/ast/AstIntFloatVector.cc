
/// @file AstIntFloatVector.cc
/// @brief AstIntFloatVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstIntFloatVector.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloatVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstIntFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstIntFloatVector::AstIntFloatVector(const AstInt* value1,
				     const AstFloatVector* value2)
  : mVal1{val1},
    mVal2{val2}
{
}

// @brief デストラクタ
AstIntFloatVector::~AstIntFloatVector()
{
  delete mVal1;
  delete mVal2;
}

// @brief ファイル上の位置を返す．
FileRegion
AstIntFloatVector::loc() const
{
  return FileRegion(mVal1->loc(), mVal2->loc());
}

// @brief 内容をストリーム出力する．
void
AstIntFloatVector::dump(ostream& s,
			int indent) const
{
  s << "(";
  value1()->dump(s, 0);
  s << ", ";
  value2()->dump(s, 0);
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
