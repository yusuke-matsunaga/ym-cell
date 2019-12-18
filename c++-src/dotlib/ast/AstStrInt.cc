
/// @file AstStrInt.cc
/// @brief AstStrInt の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStrInt.h"
#include "dotlib/AstString.h"
#include "dotlib/AstInt.h"
#include "dotlib/StrIntHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( string, int ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstStrInt*
AstMgr::new_str_int(const StrIntHandler& handler)
{
  ++ mStrIntNum;
  auto node = new AstStrInt(handler);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstStrInt
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstStrInt::AstStrInt(const StrIntHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstStrInt::~AstStrInt()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStrInt::dump(ostream& s,
		int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
