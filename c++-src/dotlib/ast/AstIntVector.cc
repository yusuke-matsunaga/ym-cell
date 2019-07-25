﻿
/// @file AstIntVector.cc
/// @brief AstIntVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstIntVector.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 整数値のベクタを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstIntVector*
AstMgr::new_int_vector(const FileRegion& loc,
		       const vector<int>& value)
{
  int n = value.size();
  ++ mIntVectNum;
  mIntVectElemSize += n;
  void* p = mAlloc.get_memory(sizeof(AstIntVector) + sizeof(int*) * (n - 1));
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
  mNum(value.size())
{
  for ( auto i: Range(mNum) ) {
    mBody[i] = value[i];
  }
}

// @brief デストラクタ
AstIntVector::~AstIntVector()
{
}

// @brief ベクタを取り出す．
// @param[out] vector ベクタを格納する変数
void
AstIntVector::get_vector(vector<int>& vector) const
{
  vector.clear();
  vector.resize(mNum);
  for ( auto i: Range(mNum) ) {
    vector[i] = value(i);
  }
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstIntVector::dump(ostream& s,
		   int indent) const
{
  const char* comma = "";
  for ( auto i: Range(mNum) ) {
    s << comma << mBody[i];
    comma = ", ";
  }
}

END_NAMESPACE_YM_DOTLIB