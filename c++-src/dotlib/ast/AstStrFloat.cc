
/// @file AstStrFloat.cc
/// @brief AstStrFloat の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstFloat.h"
#include "dotlib/StrFloatHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, float ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstStrFloat*
AstMgr::new_str_float(const StrFloatHandler& handler)
{
  ++ mStrFloatNum;
  auto node = new AstStrFloat(handler);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstStrFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstStrFloat::AstStrFloat(const StrFloatHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstStrFloat::~AstStrFloat()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStrFloat::dump(ostream& s,
		  int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
