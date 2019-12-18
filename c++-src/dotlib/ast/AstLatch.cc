
/// @file AstLatch.cc
/// @brief AstLatch の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstLatch.h"
#include "dotlib/AstMgr.h"

#include "dotlib/StrStrHandler.h"
#include "dotlib/LatchHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief latch を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstLatch*
AstMgr::new_latch(const FileRegion& attr_loc,
		  const StrStrHandler& header,
		  const LatchHandler& group)
{
  ++ mLatchNum;
  auto node = new AstLatch(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstLatch
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstLatch::AstLatch(const FileRegion& attr_loc,
		   const StrStrHandler& header,
		   const LatchHandler& group) :
  AstFL(attr_loc, header, group),
  mEnable{group.enable_on()},
  mEnableAlso{group.enable_on_also()},
  mDataIn{group.data_in()}
{
}

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstLatch::AstLatch(const FileRegion& attr_loc,
		   const StrStrIntHandler& header,
		   const LatchHandler& group) :
  AstFL(attr_loc, header, group),
  mEnable{group.enable_on()},
  mEnableAlso{group.enable_on_also()},
  mDataIn{group.data_in()}
{
}

// @brief デストラクタ
AstLatch::~AstLatch()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLatch::dump(ostream& s,
	       int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
