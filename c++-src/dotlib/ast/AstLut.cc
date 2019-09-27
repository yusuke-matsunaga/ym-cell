
/// @file AstLut.cc
/// @brief AstLut
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstLut.h"

#include "dotlib/StrHandler.h"
#include "dotlib/TableHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief lut を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダのハンドラ
// @param[in] group グループ本体のハンドラ
const AstLut*
AstMgr::new_lut(const FileRegion& attr_loc,
		const StrHandler& header,
		const TableHandler& group)
{
  ++ mLutNum;
  void* p = mAlloc.get_memory(sizeof(AstLut));
  return new (p) AstLut(attr_loc, header, group);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLut
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダのハンドラ
// @param[in] group グループ本体のハンドラ
AstLut::AstLut(const FileRegion& attr_loc,
	       const StrHandler& header,
	       const TableHandler& group) :
  AstNode{FileRegion(attr_loc, group.group_loc())},
  mName{header.value()},
  mIndex1{group.index_1()},
  mIndex2{group.index_2()},
  mIndex3{group.index_3()},
  mValueList{group.values()},
  mCoefs{group.coefs()},
  mOrders{group.orders()},
  mVar1Range{group.variable_1_range()},
  mVar2Range{group.variable_2_range()},
  mVar3Range{group.variable_3_range()},
  mDomain{group.domain()}
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
