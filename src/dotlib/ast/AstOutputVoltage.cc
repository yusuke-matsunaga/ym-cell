
/// @file AstOutputVoltage.cc
/// @brief AstOutputVoltage の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstOutputVoltage.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief output voltage を表す AstNode を生成する．．
// @param[in] loc ファイル上の位置
// @param[in] vol 'voil'
// @param[in] voh 'voh'
// @param[in] vomin 'vomin'
// @param[in] vomax 'vomax'
AstOutputVoltage*
AstMgr::new_output_voltage(const FileRegion& loc,
			   const AstString* name,
			   const AstExpr* vol,
			   const AstExpr* voh,
			   const AstExpr* vomin,
			   const AstExpr* vomax)
{
  ++ mOutputVolNum;
  void* p = mAlloc.get_memory(sizeof(AstOutputVoltage));
  return new (p) AstOutputVoltage(loc, name, vol, voh, vomin, vomax);
}


//////////////////////////////////////////////////////////////////////
// クラス AstOutputVoltage
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] vol 'vol'
// @param[in] voh 'voh'
// @param[in] vomin 'vomin'
// @param[in] vomax 'vomax'
AstOutputVoltage::AstOutputVoltage(const FileRegion& loc,
				   const AstString* name,
				   const AstExpr* vol,
				   const AstExpr* voh,
				   const AstExpr* vomin,
				   const AstExpr* vomax) :
  AstNode(loc),
  mName(name),
  mVol(vol),
  mVoh(voh),
  mVoMin(vomin),
  mVoMax(vomax)
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
