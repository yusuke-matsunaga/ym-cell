
/// @file AstFFBank.cc
/// @brief AstFFBank の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFFBank.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrStrIntHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ff_bank を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstFFBank*
AstMgr::new_ff_bank(const FileRegion& attr_loc,
		    const StrStrIntHandler& header,
		    const FFHandler& group)
{
  ++ mFFBankNum;
  auto node = new AstFFBank(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstFFBank
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFFBank::AstFFBank(const FileRegion& attr_loc,
		     const StrStrIntHandler& header,
		     const FFHandler& group) :
  AstFF(attr_loc, header, group),
  mBits{header.value3()}
{
}

// @brief デストラクタ
AstFFBank::~AstFFBank()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFFBank::dump(ostream& s,
		int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
