
/// @file AstStr3.cc
/// @brief AstStr3 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStr3.h"
#include "dotlib/AstString.h"
#include "dotlib/StrStrStrHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, float ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstStr3*
AstMgr::new_str3(const StrStrStrHandler& handler)
{
  ++ mStr3Num;
  void* p = mAlloc.get_memory(sizeof(AstStr3));
  return new (p) AstStr3(handler);
}


//////////////////////////////////////////////////////////////////////
// クラス AstStr3
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstStr3::AstStr3(const StrStrStrHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2()),
  mVal3(handler.value3())
{
}

// @brief デストラクタ
AstStr3::~AstStr3()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStr3::dump(ostream& s,
	      int indent) const
{
  s << "(" << value1()->value()
    << ", " << value2()->value()
    << ", " << value3()->value()
    << ")";
}

END_NAMESPACE_YM_DOTLIB
