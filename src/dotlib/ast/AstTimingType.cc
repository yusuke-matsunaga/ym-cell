
/// @file AstTimingType.cc
/// @brief AstTimingType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstMgr.h"
#include "AstTimingType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing_type を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTimingType*
AstMgr::new_timing_type(const FileRegion& loc,
			ClibTimingType value)
{
  ++ mTimingTypeNum;
  void* p = mAlloc.get_memory(sizeof(AstTimingType));
  return new (p) AstTimingType(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTimingType::AstTimingType(const FileRegion& loc,
			     ClibTimingType value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstTimingType::~AstTimingType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTimingType::dump(ostream& s,
		    int indent) const
{
  switch ( mValue ) {
  case kClibTimingCombinational: dump_string(s, "combinational"); break;
  default: dump_string(s, "---"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
