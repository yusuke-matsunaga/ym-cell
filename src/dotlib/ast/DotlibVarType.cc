
/// @file DotlibVarType.cc
/// @brief DotlibVarType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibVarType.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibVarType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
DotlibVarType::DotlibVarType(const FileRegion& loc,
			     ClibVarType value) :
  DotlibNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibVarType::~DotlibVarType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibVarType::dump(ostream& s,
		    int indent) const
{
  switch ( mValue ) {
  case kClibVarInputNetTransition:                  dump_string(s, "input net transition"); break;
  case kClibVarInputTransitionTime:                 dump_string(s, "input transition time"); break;
  case kClibVarTotalOutputNetCapacitance:           dump_string(s, "output net capacitance"); break;
  case kClibVarEqualOrOppositeOutputNetCapacitance: dump_string(s, "equal or opposite output net capacitance"); break;
  case kClibVarOutputNetLength:                     dump_string(s, "output net length"); break;
  case kClibVarOutputNetWireCap:                    dump_string(s, "output net wire cap"); break;
  case kClibVarOutputNetPinCap:                     dump_string(s, "output net pin cap"); break;
  case kClibVarRelatedOutTotalOutputNetCapacitance: dump_string(s, "related out total output net capacitance"); break;
  case kClibVarRelatedOutOutputNetLength:           dump_string(s, "related out output net length"); break;
  case kClibVarRelatedOutOutputNetWireCap:          dump_string(s, "related out output net wire cap"); break;
  case kClibVarRelatedOutOutputNetPinCap:           dump_string(s, "related out output net pin cap"); break;
  case kClibVarConstrainedPinTransition:            dump_string(s, "constrained pin transition"); break;
  case kClibVarRelatedPinTransition:                dump_string(s, "related pin transition"); break;
  case kClibVarNone:                                dump_string(s, "none"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
