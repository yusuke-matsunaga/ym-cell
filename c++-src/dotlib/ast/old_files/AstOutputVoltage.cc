
/// @file AstOutputVoltage.cc
/// @brief AstOutputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstOutputVoltage.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrHandler.h"
#include "dotlib/OutputVoltageHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstOutputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstOutputVoltage::AstOutputVoltage(const FileRegion& attr_loc,
				   const StrHandler& header,
				   const OutputVoltageHandler& group) :
  AstNode{FileRegion(attr_loc, group.group_loc())},
  mName{header.value()}
#if 0
  mVol{group.vol()},
  mVoh{group.voh()},
  mVoMin{group.vomin()},
  mVoMax{group.vomax()}
#endif
{
}

// @brief デストラクタ
AstOutputVoltage::~AstOutputVoltage()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstOutputVoltage::dump(ostream& s,
		       int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
