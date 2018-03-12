
/// @file DotlibDelayModel.cc
/// @brief DotlibDelayModel の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibDelayModel.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibDelayModel::DotlibDelayModel(const FileRegion& loc,
				   ClibDelayModel value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibDelayModel::~DotlibDelayModel()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibDelayModel::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibDelayGenericCmos:   dump_string(s, "generic cmos"); break;
  case kClibDelayTableLookup:   dump_string(s, "table lookup"); break;
  case kClibDelayPiecewiseCmos: dump_string(s, "piesewise cmos"); break;
  case kClibDelayCmos2:         dump_string(s, "cmos2"); break;
  case kClibDelayDcm:           dump_string(s, "dcm"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
