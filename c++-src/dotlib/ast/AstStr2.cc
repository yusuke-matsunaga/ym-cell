
/// @file AstStr2.cc
/// @brief AstStr2 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStr2.h"
#include "dotlib/AstString.h"
#include "dotlib/StrStrHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, float ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstStr2*
AstMgr::new_str2(const StrStrHandler& handler)
{
  ++ mStr2Num;
  auto node = new AstStr2(handler);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstStr2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstStr2::AstStr2(const StrStrHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstStr2::~AstStr2()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStr2::dump(ostream& s,
	      int indent) const
{
  s << "(" << value1()->value() << ", " << value2()->value() << ")";
}

END_NAMESPACE_YM_DOTLIB
