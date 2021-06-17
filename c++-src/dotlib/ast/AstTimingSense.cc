
/// @file AstTimingSense.cc
/// @brief AstTimingSense の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstTimingSense.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstTimingSense
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstTimingSense::AstTimingSense(ClibTimingSense value,       ///< [in] 値
			       const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTimingSense::dump(ostream& s,
		     int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibTimingSense::PosiUnate: tmp = "positive unate"; break;
  case ClibTimingSense::NegaUnate: tmp = "negative unate"; break;
  case ClibTimingSense::NonUnate:  tmp = "non unate";      break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
