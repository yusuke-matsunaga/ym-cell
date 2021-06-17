
/// @file AstTemplte.cc
/// @brief AstTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstTemplate.h"
#include "dotlib/StrHandler.h"
#include "dotlib/TemplateHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstTemplate
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダのハンドラ
// @param[in] group グループ本体のハンドラ
AstTemplate::AstTemplate(const FileRegion& attr_loc,
			 const StrHandler& header,
			 const TemplateHandler& group) :
  AstNode(FileRegion{attr_loc, group.group_loc()}),
  mName{header.value()}
#if 0
  mDimension{group.mDimension},
  mVar1{group.mVar1},
  mVar2{group.mVar2},
  mVar3{group.mVar3},
  mIndex1{group.mIndex1},
  mIndex2{group.mIndex2},
  mIndex3{group.mIndex3},
  mDomain{group.mDomain}
#endif
{
}

// @brief デストラクタ
AstTemplate::~AstTemplate()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTemplate::dump(ostream& s,
		     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
