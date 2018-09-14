
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
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstDomain*
AstMgr::new_domain(const Str1HeaderHandler& header,
		   const DomainHandler& group)
{
  ++ mDomainNum;
  void* p = mAlloc.get_memory(sizeof(AstDomain));
  return new (p) AstDomain(header, group);
}


//////////////////////////////////////////////////////////////////////
// クラス AstDomain
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstDomain::AstDomain(const Str1HeaderHandler& header,
		     const DomainHandler& group) :
  AstNode(FileRegion(header.header_loc(), group.group_loc())),
  mName(header.value()),
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
