
/// @file AstDomain.cc
/// @brief AstDomain の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstDomain.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrHandler.h"
#include "dotlib/DomainHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief domain を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstDomain*
AstMgr::new_domain(const FileRegion& attr_loc,
		   const StrHandler& header,
		   const DomainHandler& group)
{
  ++ mDomainNum;
  auto node = new AstDomain(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDomain
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstDomain::AstDomain(const FileRegion& attr_loc,
		     const StrHandler& header,
		     const DomainHandler& group) :
  AstNode{FileRegion{attr_loc, group.group_loc()}},
  mName{header.value()},
  mCalcMode{group.calc_mode()},
  mCoefs{group.coefs()},
  mOrders{group.orders()},
  mVar1Range{group.variable_1_range()},
  mVar2Range{group.variable_2_range()},
  mVar3Range{group.variable_3_range()}
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
