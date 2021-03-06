
/// @file AstNameListNode.cc
/// @brief AstNameListNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2019 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstNameListNode.h"
#include "dotlib/StrListHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstNameListNode
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
AstNameListNode::AstNameListNode(const FileRegion& loc,
				 const StrListHandler& header) :
  AstNode{loc},
  mNameList{header.value()}
{
}

// @brief デストラクタ
AstNameListNode::~AstNameListNode()
{
}

END_NAMESPACE_YM_DOTLIB
