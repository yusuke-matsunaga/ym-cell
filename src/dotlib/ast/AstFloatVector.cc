﻿
/// @file AstFloatVector.cc
/// @brief AstFloatVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstFloatVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ベクタを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
AstFloatVector*
AstMgr::new_vector(const FileRegion& loc,
		   const vector<double>& value_list)
{
  int n = value_list.size();
  ++ mVectNum;
  mVectElemSize += (n - 1);
  void* p = mAlloc.get_memory(sizeof(AstFloatVector) + (n - 1) * sizeof(double));
  return new (p) AstFloatVector(loc, value_list);
}


//////////////////////////////////////////////////////////////////////
// クラス AstFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
AstFloatVector::AstFloatVector(const FileRegion& loc,
			       const vector<double>& value_list) :
  AstNode(loc),
  mNum(value_list.size())
{
  for ( int i = 0; i < mNum; ++ i ) {
    mBody[i] = value_list[i];
  }
}

// @brief デストラクタ
AstFloatVector::~AstFloatVector()
{
}

// @brief ベクタの全体を取り出す．
// @param[out] vector 結果を格納する変数
void
AstFloatVector::get_vector(vector<double>& vector) const
{
  vector.clear();
  vector.resize(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    vector[i] = mBody[i];
  }
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloatVector::dump(ostream& s,
		     int indent) const
{
  const char* comma = "";
  s << "(";
  for ( int i = 0; i < mNum; ++ i ) {
    s << comma << mBody[i];
    comma = ", ";
  }
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
