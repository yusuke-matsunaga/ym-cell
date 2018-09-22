
/// @file AstInputVoltage.cc
/// @brief AstInputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstInputVoltage.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief input voltage を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] vil 'vil'
// @param[in] vih 'vih'
// @param[in] vimin 'vimin'
// @param[in] vimax 'vimax'
AstInputVoltage*
AstMgr::new_input_voltage(const FileRegion& loc,
			  const AstString* name,
			  const AstExpr* vil,
			  const AstExpr* vih,
			  const AstExpr* vimin,
			  const AstExpr* vimax)
{
  ++ mInputVolNum;
  void* p = mAlloc.get_memory(sizeof(AstInputVoltage));
  return new (p) AstInputVoltage(loc, name, vil, vih, vimin, vimax);
}


//////////////////////////////////////////////////////////////////////
// クラス AstInputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] vil 'vil'
// @param[in] vih 'vih'
// @param[in] vimin 'vimin'
// @param[in] vimax 'vimax'
AstInputVoltage::AstInputVoltage(const FileRegion& loc,
				 const AstString* name,
				 const AstExpr* vil,
				 const AstExpr* vih,
				 const AstExpr* vimin,
				 const AstExpr* vimax) :
  AstNode(loc),
  mName(name),
  mVil(vil),
  mVih(vih),
  mViMin(vimin),
  mViMax(vimax)
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
