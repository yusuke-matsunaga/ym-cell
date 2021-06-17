
/// @file AstInputVoltage.cc
/// @brief AstInputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstInputVoltage.h"

#include "dotlib/StrHandler.h"
#include "dotlib/InputVoltageHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstInputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstInputVoltage::AstInputVoltage(const FileRegion& attr_loc,
				 const StrHandler& header,
				 const InputVoltageHandler& group) :
  AstNode(FileRegion(attr_loc, group.group_loc())),
  mName{header.value()}
#if 0
  mVil{group.vil()},
  mVih{group.vih()},
  mViMin{group.vimin()},
  mViMax{group.vimax()}
#endif
{
}

// @brief デストラクタ
AstInputVoltage::~AstInputVoltage()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstInputVoltage::dump(ostream& s,
		      int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
