
/// @file AstFF.cc
/// @brief AstFF の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFF.h"
#include "dotlib/AstMgr.h"
#include "dotlib/FFHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ff を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstFF*
AstMgr::new_ff(const FileRegion& attr_loc,
	       const StrStrHandler& header,
	       const FFHandler& group)
{
  ++ mFFNum;
  void* p = mAlloc.get_memory(sizeof(AstFF));
  return new (p) AstFF(attr_loc, header, group);
}


//////////////////////////////////////////////////////////////////////
// クラス AstFF
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFF::AstFF(const FileRegion& attr_loc,
	     const StrStrHandler& header,
	     const FFHandler& group) :
  AstFL(attr_loc, header, group),
  mClockedOn(group.clocked_on()),
  mClockedOnAlso(group.clocked_on_also()),
  mNextState(group.next_state())
{
}

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstFF::AstFF(const FileRegion& attr_loc,
	     const StrStrIntHandler& header,
	     const FFHandler& group) :
  AstFL(attr_loc, header, group),
  mClockedOn(group.clocked_on()),
  mClockedOnAlso(group.clocked_on_also()),
  mNextState(group.next_state())
{
}

// @brief デストラクタ
AstFF::~AstFF()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFF::dump(ostream& s,
	    int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
