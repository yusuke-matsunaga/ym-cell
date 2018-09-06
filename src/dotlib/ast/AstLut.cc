
/// @file AstLut.cc
/// @brief AstLut
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstLut.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief lut を表す AstNode を生成する．
AstLut*
AstMgr::new_lut(const FileRegion& loc,
		const AstString* name,
		const AstFloatVector* index_1,
		const AstFloatVector* index_2,
		const AstFloatVector* index_3,
		const AstFloatVector* value_list,
		const AstDomain* domain)
{
  ++ mLutNum;
  void* p = mAlloc.get_memory(sizeof(AstLut));
  return new (p) AstLut(loc, name, index_1, index_2, index_3, value_list, domain);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLut
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] index_1, index_2, index_3 インデックスのベクタ
// @param[in] value_list 値のリスト
AstLut::AstLut(const FileRegion& loc,
	       const AstString* name,
	       const AstFloatVector* index_1,
	       const AstFloatVector* index_2,
	       const AstFloatVector* index_3,
	       const AstFloatVector* value_list,
	       const AstDomain* domain) :
  AstNode(loc),
  mName(name),
  mIndex1(index_1),
  mIndex2(index_2),
  mIndex3(index_3),
  mValueList(value_list),
  mDomain(domain)
{
}

// @brief デストラクタ
AstLut::~AstLut()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLut::dump(ostream& s,
	     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
