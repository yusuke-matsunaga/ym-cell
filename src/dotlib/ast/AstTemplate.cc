
/// @file AstTemplte.cc
/// @brief AstTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstTemplate.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief lut template を表す AstNode を生成する．
AstTemplate*
AstMgr::new_template(const FileRegion& loc,
		     const AstString* name,
		     int dimension,
		     const AstVarType* var_1,
		     const AstVarType* var_2,
		     const AstVarType* var_3,
		     const AstFloatVector* index_1,
		     const AstFloatVector* index_2,
		     const AstFloatVector* index_3)
{
  ++ mTemplateNum;
  void* p = mAlloc.get_memory(sizeof(AstTemplate));
  return new (p) AstTemplate(loc, name, dimension,
			     var_1, var_2, var_3,
			     index_1, index_2, index_3);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTemplate
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] dimension 次元数
// @param[in] var_1, var_2, var_3 変数のタイプ
// @param[in] index_1, index_2, index_3 インデックスのベクタ
AstTemplate::AstTemplate(const FileRegion& loc,
			 const AstString* name,
			 int dimension,
			 const AstVarType* var_1,
			 const AstVarType* var_2,
			 const AstVarType* var_3,
			 const AstFloatVector* index_1,
			 const AstFloatVector* index_2,
			 const AstFloatVector* index_3) :
  AstNode(loc),
  mName(name),
  mDimension(dimension),
  mVar1(var_1),
  mVar2(var_2),
  mVar3(var_3),
  mIndex1(index_1),
  mIndex2(index_2),
  mIndex3(index_3)
{
}

// @brief デストラクタ
AstTemplate::~AstTemplate()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTemplate::dump(ostream& s,
		     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
