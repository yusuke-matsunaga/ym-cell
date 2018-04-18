
/// @file AstPieceWise.cc
/// @brief AstPieceWise の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstPieceWise.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief piece wise パラメータを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] val1 インデックス
// @param[in] val2 値
AstPieceWise*
AstMgr::new_piecewise(const FileRegion& loc,
		      int val1,
		      double val2)
{
  ++ mPieceWiseNum;
  void* p = mAlloc.get_memory(sizeof(AstPieceWise));
  return new (p) AstPieceWise(loc, val1, val2);
}


//////////////////////////////////////////////////////////////////////
// クラス AstPieceWise
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value1
// @param[in] value2
AstPieceWise::AstPieceWise(const FileRegion& loc,
			   int value1,
			   double value2) :
  AstNode(loc),
  mValue1(value1),
  mValue2(value2)
{
}

// @brief デストラクタ
AstPieceWise::~AstPieceWise()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstPieceWise::dump(ostream& s,
		   int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
