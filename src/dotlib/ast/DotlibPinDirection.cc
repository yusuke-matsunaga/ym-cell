
/// @file DotlibPinDirection.cc
/// @brief DotlibPinDirection の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibPinDirection.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibPinDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibPinDirection::DotlibPinDirection(const FileRegion& loc,
				       ClibCellPinDirection value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibPinDirection::~DotlibPinDirection()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibPinDirection::dump(ostream& s,
			 int indent) const
{
  switch ( mValue ) {
  case kClibCellPinInput:    dump_string(s, "input");    break;
  case kClibCellPinOutput:   dump_string(s, "output");   break;
  case kClibCellPinInout:    dump_string(s, "inout");    break;
  case kClibCellPinInternal: dump_string(s, "internal"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
