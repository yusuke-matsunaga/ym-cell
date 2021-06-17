
/// @file AstIntVector.cc
/// @brief AstIntVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstIntVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス AstIntVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstIntVector::AstIntVector(const vector<int>& value,
			   const FileRegion& loc)
  : mBody{value},
    mLoc{loc}
{
}

// @brief デストラクタ
AstIntVector::~AstIntVector()
{
}

// @brief ファイル上の位置を返す．
FileRegion
AstIntVector::loc() const
{
  return mLoc;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstIntVector::dump(ostream& s,
		   int indent) const
{
  const char* comma = "";
  for ( auto i: mBody ) {
    s << comma << i;
    comma = ", ";
  }
}

END_NAMESPACE_YM_DOTLIB
