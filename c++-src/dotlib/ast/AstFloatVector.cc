
/// @file AstFloatVector.cc
/// @brief AstFloatVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFloatVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloatVector::AstFloatVector(const vector<double>& value_list,
			       const FileRegion& loc)
  : mBody{value_list},
    mLoc{loc}
{
}

// @brief デストラクタ
AstFloatVector::~AstFloatVector()
{
}

// @brief ファイル上の位置を返す．
FileRegion
AstFloatVector::loc() const
{
  return mLoc;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloatVector::dump(ostream& s,
		     int indent) const
{
  const char* comma = "";
  s << "(";
  for ( auto flt: mBody ) {
    s << comma << flt;
    comma = ", ";
  }
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
