
/// @file AstFloat.cc
/// @brief AstNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstFloat.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 実数値を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstFloat*
AstMgr::new_float(const FileRegion& loc,
		  double value)
{
  ++ mFloatNum;
  void* p = mAlloc.get_memory(sizeof(AstFloat));
  return new (p) AstFloat(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstFloat::AstFloat(const FileRegion& loc,
		   double value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstFloat::~AstFloat()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloat::dump(ostream& s,
	       int indent) const
{
  s << value();
}

END_NAMESPACE_YM_DOTLIB
