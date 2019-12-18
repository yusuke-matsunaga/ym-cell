
/// @file AstTimingSense.cc
/// @brief AstTimingSense の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstTimingSense.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing_sense を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstTimingSense*
AstMgr::new_timing_sense(const FileRegion& loc,
			 ClibTimingSense value)
{
  ++ mTimingSenseNum;
  auto node = new AstTimingSense(loc, value);
  mNodeList.push_back(node);
  return node;
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
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibTimingSense::PosiUnate: tmp = "positive unate"; break;
  case ClibTimingSense::NegaUnate: tmp = "negative unate"; break;
  case ClibTimingSense::NonUnate:  tmp = "non unate";      break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
