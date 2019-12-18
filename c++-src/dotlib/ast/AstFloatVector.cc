
/// @file AstFloatVector.cc
/// @brief AstFloatVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstFloatVector.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief float のベクタ型の AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
const AstFloatVector*
AstMgr::new_float_vector(const FileRegion& loc,
			 const vector<double>& value_list)
{
  int n = value_list.size();
  ++ mFloatVectNum;
  mFloatVectElemSize += (n - 1);
  auto node = new AstFloatVector(loc, value_list);
  mNodeList.push_back(node);
  return node;
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
  for ( auto i: Range(mNum) ) {
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
  for ( auto i: Range(mNum) ) {
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
  for ( auto i: Range(mNum) ) {
    s << comma << mBody[i];
    comma = ", ";
  }
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
