
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

// @brief input voltage を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstInputVoltage*
AstMgr::new_input_voltage(const FileRegion& attr_loc,
			  const StrHandler& header,
			  const InputVoltageHandler& group)
{
  ++ mInputVolNum;
  auto node = new AstInputVoltage(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


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
  mName{header.value()},
  mVil{group.vil()},
  mVih{group.vih()},
  mViMin{group.vimin()},
  mViMax{group.vimax()}
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
