
/// @file DotlibDelayModel.cc
/// @brief DotlibDelayModel の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstDelayModel.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstDelayModel::AstDelayModel(ClibDelayModel value,
			     const FileRegion& val_loc)
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstDelayModel::dump(ostream& s,
		    int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibDelayModel::GenericCmos:   tmp = "generic cmos"; break;
  case ClibDelayModel::TableLookup:   tmp = "table lookup"; break;
  case ClibDelayModel::PiecewiseCmos: tmp = "piesewise cmos"; break;
  case ClibDelayModel::Cmos2:         tmp = "cmos2"; break;
  case ClibDelayModel::Dcm:           tmp = "dcm"; break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
