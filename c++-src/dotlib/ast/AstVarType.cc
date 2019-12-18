
/// @file AstVarType.cc
/// @brief AstVarType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstVarType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief var_type を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstVarType*
AstMgr::new_var_type(const FileRegion& loc,
		     ClibVarType value)
{
  ++ mVarTypeNum;
  auto node = new AstVarType(loc, value);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstVarType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstVarType::AstVarType(const FileRegion& loc,
		       ClibVarType value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstVarType::~AstVarType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstVarType::dump(ostream& s,
		 int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibVarType::InputNetTransition:                  tmp = "input net transition"; break;
  case ClibVarType::InputTransitionTime:                 tmp = "input transition time"; break;
  case ClibVarType::TotalOutputNetCapacitance:           tmp = "output net capacitance"; break;
  case ClibVarType::EqualOrOppositeOutputNetCapacitance: tmp = "equal or opposite output net capacitance"; break;
  case ClibVarType::OutputNetLength:                     tmp = "output net length"; break;
  case ClibVarType::OutputNetWireCap:                    tmp = "output net wire cap"; break;
  case ClibVarType::OutputNetPinCap:                     tmp = "output net pin cap"; break;
  case ClibVarType::RelatedOutTotalOutputNetCapacitance: tmp = "related out total output net capacitance"; break;
  case ClibVarType::RelatedOutOutputNetLength:           tmp = "related out output net length"; break;
  case ClibVarType::RelatedOutOutputNetWireCap:          tmp = "related out output net wire cap"; break;
  case ClibVarType::RelatedOutOutputNetPinCap:           tmp = "related out output net pin cap"; break;
  case ClibVarType::ConstrainedPinTransition:            tmp = "constrained pin transition"; break;
  case ClibVarType::RelatedPinTransition:                tmp = "related pin transition"; break;
  case ClibVarType::None:                                tmp = "none"; break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
