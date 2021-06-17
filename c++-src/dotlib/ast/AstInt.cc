
/// @file AstInt.cc
/// @brief AstInt の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstInt.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// クラス AstInt
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstInt::AstInt(int value,                   ///< [in] 値
	       const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstInt::dump(ostream& s,
	     int indent) const
{
  s << value();
}

END_NAMESPACE_YM_DOTLIB
