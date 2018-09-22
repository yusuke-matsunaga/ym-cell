
/// @file AstStringVector.cc
/// @brief AstStringVector の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStringVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 定数シンボルを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstStringVector*
AstMgr::new_string_vector(const FileRegion& loc,
			  const vector<ShString>& value)
{
  int n = value.size();
  ++ mStrVectNum;
  mStrVectElemSize += n;
  void* p = mAlloc.get_memory(sizeof(AstStringVector) + (n - 1) * sizeof(ShString));
  return new (p) AstStringVector(loc, value);
}


//////////////////////////////////////////////////////////////////////
/// クラス AstStringVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstStringVector::AstStringVector(const FileRegion& loc,
				 const vector<ShString>& value) :
  AstNode(loc),
  mNum(value.size())
{
  for ( auto i: Range(mNum) ) {
    mBody[i] = value[i];
  }
}

// @brief デストラクタ
AstStringVector::~AstStringVector()
{
}

// @brief ベクタを取り出す．
// @param[out] vector ベクタを格納する変数
void
AstStringVector::get_vector(vector<ShString>& vector) const
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
AstStringVector::dump(ostream& s,
		      int indent) const
{
  const char* comma = "";
  for ( auto i: Range(mNum) ) {
    s << comma;
    comma = ", ";
    dump_string(s, mBody[i]);
  }
}

END_NAMESPACE_YM_DOTLIB
