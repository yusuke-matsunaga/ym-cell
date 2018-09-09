
/// @file AstIntVector.cc
/// @brief AstIntVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstIntVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 整数値を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstIntVector*
AstMgr::new_int_vector(const FileRegion& loc,
		       const vector<int>& value)
{
  ++ mIntVectNum;
  mIntVectElemSize += value.size();
  void* p = mAlloc.get_memory(sizeof(AstIntVector));
  return new (p) AstIntVector(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstIntVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstIntVector::AstIntVector(const FileRegion& loc,
			   const vector<int>& value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstIntVector::~AstIntVector()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstIntVector::dump(ostream& s,
		   int indent) const
{
  const char* comma = "";
  for ( auto val: value() ) {
    s << comma << val;
    comma = ", ";
  }
}

END_NAMESPACE_YM_DOTLIB
