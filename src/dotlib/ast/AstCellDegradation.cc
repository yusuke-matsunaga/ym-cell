
/// @file AstCellDegradation.cc
/// @brief AstCellDegradation
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstCellDegradation.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief lut を表す AstNode を生成する．
AstCellDegradation*
AstMgr::new_cell_degradation(const FileRegion& loc,
			     const AstString* name,
			     const AstString* calc_mode,
			     const AstFloatVector* index_1,
			     const AstFloatVector* value_list,
			     const AstFloatVector* coefs,
			     const AstIntVector* orders,
			     const AstVariableRange* variable_1_range,
			     const AstDomain* domain)
{
  ++ mLutNum;
  void* p = mAlloc.get_memory(sizeof(AstCellDegradation));
  return new (p) AstCellDegradation(loc, name, calc_mode, index_1, value_list,
				    coefs, orders, variable_1_range, domain);
}


//////////////////////////////////////////////////////////////////////
// クラス AstCellDegradation
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] calc_mode 'calc_mode' 属性
// @param[in] index_1 インデックスのベクタ
// @param[in] value_list 値のリスト
// @param[in] coefs 'coefs' 属性
// @param[in] orders 'orders' 属性
// @param[in] variable_1_range 'variable_1_range' 属性
// @param[in] domain 'domain'
AstCellDegradation::AstCellDegradation(const FileRegion& loc,
				       const AstString* name,
				       const AstString* calc_mode,
				       const AstFloatVector* index_1,
				       const AstFloatVector* value_list,
				       const AstFloatVector* coefs,
				       const AstIntVector* orders,
				       const AstVariableRange* variable_1_range,
				       const AstDomain* domain) :
  AstNode(loc),
  mName(name),
  mCalcMode(calc_mode),
  mIndex1(index_1),
  mValueList(value_list),
  mCoefs(coefs),
  mOrders(orders),
  mVar1Range(variable_1_range),
  mDomain(domain)
{
}

// @brief デストラクタ
AstCellDegradation::~AstCellDegradation()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstCellDegradation::dump(ostream& s,
			 int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
