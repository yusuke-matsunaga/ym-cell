
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
AstStringVector*
AstMgr::new_string_vector(const FileRegion& loc,
			  const vector<ShString>& value)
{
  ++ mStrVectNum;
  mStrVectElemSize += value.size();
  void* p = mAlloc.get_memory(sizeof(AstStringVector));
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
  mValue(value)
{
}

// @brief デストラクタ
AstStringVector::~AstStringVector()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStringVector::dump(ostream& s,
		      int indent) const
{
  const char* comma = "";
  for ( auto str: value() ) {
    s << comma;
    comma = ", ";
    dump_string(s, str);
  }
}

END_NAMESPACE_YM_DOTLIB
