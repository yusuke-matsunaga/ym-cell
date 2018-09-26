
/// @file AstFloatStr.cc
/// @brief AstFloatStr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/FloatStrHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, string ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstFloatStr*
AstMgr::new_float_str(const FloatStrHandler& handler)
{
  ++ mFloatStrNum;
  void* p = mAlloc.get_memory(sizeof(AstFloatStr));
  return new (p) AstFloatStr(handler);
}


//////////////////////////////////////////////////////////////////////
// クラス AstFloatStr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstFloatStr::AstFloatStr(const FloatStrHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstFloatStr::~AstFloatStr()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloatStr::dump(ostream& s,
		  int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
