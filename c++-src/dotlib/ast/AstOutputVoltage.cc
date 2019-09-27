
/// @file AstOutputVoltage.cc
/// @brief AstOutputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstOutputVoltage.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrHandler.h"
#include "dotlib/OutputVoltageHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief output voltage を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstOutputVoltage*
AstMgr::new_output_voltage(const FileRegion& attr_loc,
			   const StrHandler& header,
			   const OutputVoltageHandler& group)
{
  ++ mOutputVolNum;
  void* p = mAlloc.get_memory(sizeof(AstOutputVoltage));
  return new (p) AstOutputVoltage(attr_loc, header, group);
}


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
  mName{header.value()},
  mVol{group.vol()},
  mVoh{group.voh()},
  mVoMin{group.vomin()},
  mVoMax{group.vomax()}
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
