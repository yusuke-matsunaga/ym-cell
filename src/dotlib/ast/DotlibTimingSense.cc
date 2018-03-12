
/// @file DotlibTimingSense.cc
/// @brief DotlibTimingSense の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibTimingSense.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTimingSense
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibTimingSense::DotlibTimingSense(const FileRegion& loc,
				     ClibTimingSense value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTimingSense::~DotlibTimingSense()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTimingSense::dump(ostream& s,
			int indent) const
{
  switch ( mValue ) {
  case kClibPosiUnate: dump_string(s, "positive unate"); break;
  case kClibNegaUnate: dump_string(s, "negative unate"); break;
  case kClibNonUnate:  dump_string(s, "non unate");      break;
  }
}

END_NAMESPACE_YM_DOTLIB
