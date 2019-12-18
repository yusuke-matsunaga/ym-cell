
/// @file AstLatchBank.cc
/// @brief AstLatchBank の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstLatchBank.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrStrIntHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief latch_bank を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstLatchBank*
AstMgr::new_latch_bank(const FileRegion& attr_loc,
		       const StrStrIntHandler& header,
		       const LatchHandler& group)
{
  ++ mLatchBankNum;
  auto node = new AstLatchBank(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstLatchBank
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstLatchBank::AstLatchBank(const FileRegion& attr_loc,
			   const StrStrIntHandler& header,
			   const LatchHandler& group) :
  AstLatch(attr_loc, header, group),
  mBits{header.value3()}
{
}

// @brief デストラクタ
AstLatchBank::~AstLatchBank()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLatchBank::dump(ostream& s,
		   int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
