
/// @file AstIntFloatVector.cc
/// @brief AstIntFloatVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstIntFloatVector.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/IntFloatVectorHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ( float, float ) 型の AstNode を生成する．
// @param[in] handler ハンドラ
const AstIntFloatVector*
AstMgr::new_int_float_vector(const IntFloatVectorHandler& handler)
{
  ++ mIntFloatVectorNum;
  auto node = new AstIntFloatVector(handler);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstIntFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstIntFloatVector::AstIntFloatVector(const IntFloatVectorHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mVal1(handler.value1()),
  mVal2(handler.value2())
{
}

// @brief デストラクタ
AstIntFloatVector::~AstIntFloatVector()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstIntFloatVector::dump(ostream& s,
			int indent) const
{
  s << "(";
  value1()->dump(s, 0);
  s << ", ";
  value2()->dump(s, 0);
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
