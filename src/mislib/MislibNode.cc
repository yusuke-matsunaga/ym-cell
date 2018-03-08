
/// @file MislibNode.cc
/// @brief MislibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibNode
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
MislibNode::MislibNode(const FileRegion& loc) :
  mLoc(loc)
{
}

// デストラクタ
MislibNode::~MislibNode()
{
}

// 位置を出力する．
void
MislibNode::dump_loc(ostream& s) const
{
  s << "<LOC>" << loc() << "</LOC>" << endl;
}

END_NAMESPACE_YM_MISLIB
