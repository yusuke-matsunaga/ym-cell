
/// @file AstCell.cc
/// @brief AstCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstNameNode.h"
#include "dotlib/StrHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstNameNode
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
AstNameNode::AstNameNode(const FileRegion& loc,
			 const StrHandler& header) :
  AstNode{loc},
  mName{header.value()}
{
}

// @brief デストラクタ
AstNameNode::~AstNameNode()
{
}

END_NAMESPACE_YM_DOTLIB
