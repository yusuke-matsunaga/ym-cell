
/// @file AstDomain.cc
/// @brief AstDomain の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstDomain.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief domain を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] calc_mode calc_mode 属性
// @param[in] coefs coefs 属性
// @param[in] orders orders 属性
// @param[in] var1_range variable_1_range 属性
// @param[in] var2_range variable_2_range 属性
// @param[in] var3_range variable_3_range 属性
// @param[in] value1, value2 値
AstDomain*
AstMgr::new_domain(const FileRegion& loc,
		   const AstString* name,
		   const AstString* calc_mode,
		   const AstString* coefs,
		   const AstString* orders,
		   const AstVariableRange* var1_range,
		   const AstVariableRange* var2_range,
		   const AstVariableRange* var3_range)
{
  ++ mDomainNum;
  void* p = mAlloc.get_memory(sizeof(AstDomain));
  return new (p) AstDomain(loc, name, calc_mode, coefs, orders,
			   var1_range, var2_range, var3_range);
}

//////////////////////////////////////////////////////////////////////
// クラス AstDomain
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] calc_mode calc_mode 属性
// @param[in] coefs coefs 属性
// @param[in] orders orders 属性
// @param[in] var1_range variable_1_range 属性
// @param[in] var2_range variable_2_range 属性
// @param[in] var3_range variable_3_range 属性
AstDomain::AstDomain(const FileRegion& loc,
		     const AstString* name,
		     const AstString* calc_mode,
		     const AstString* coefs,
		     const AstString* orders,
		     const AstVariableRange* var1_range,
		     const AstVariableRange* var2_range,
		     const AstVariableRange* var3_range) :
  AstNode(loc),
  mName(name),
  mCalcMode(calc_mode),
  mCoefs(coefs),
  mOrders(orders),
  mVar1Range(var1_range),
  mVar2Range(var2_range),
  mVar3Range(var3_range)
{
}

// @brief デストラクタ
AstDomain::~AstDomain()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstDomain::dump(ostream& s,
		int indent) const
{
#warning "TODO: 未完"
}

END_NAMESPACE_YM_DOTLIB
