
/// @file AstFloat2.cc
/// @brief AstFloat2 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloat.h"
#include "dotlib/Float2Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, float ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstFloat2*
AstMgr::new_float2(const Float2Handler& handler)
{
  ++ mFloat2Num;
  void* p = mAlloc.get_memory(sizeof(AstFloat2));
  return new (p) AstFloat2(handler);
}


//////////////////////////////////////////////////////////////////////
// クラス AstFloat2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstFloat2::AstFloat2(const Float2Handler& handler) :
  AstNode(handler.header_loc()),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstFloat2::~AstFloat2()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloat2::dump(ostream& s,
		int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
