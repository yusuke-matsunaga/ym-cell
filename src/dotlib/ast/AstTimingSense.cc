
/// @file AstTimingSense.cc
/// @brief AstTimingSense の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstMgr.h"
#include "AstTimingSense.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing_sense を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTimingSense*
AstMgr::new_timing_sense(const FileRegion& loc,
			 ClibTimingSense value)
{
  ++ mTimingSenseNum;
  void* p = mAlloc.get_memory(sizeof(AstTimingSense));
  return new (p) AstTimingSense(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingSense
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTimingSense::AstTimingSense(const FileRegion& loc,
			       ClibTimingSense value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstTimingSense::~AstTimingSense()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTimingSense::dump(ostream& s,
		     int indent) const
{
  switch ( mValue ) {
  case kClibPosiUnate: dump_string(s, "positive unate"); break;
  case kClibNegaUnate: dump_string(s, "negative unate"); break;
  case kClibNonUnate:  dump_string(s, "non unate");      break;
  }
}

END_NAMESPACE_YM_DOTLIB
