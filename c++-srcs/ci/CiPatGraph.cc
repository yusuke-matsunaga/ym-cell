
/// @file CiPatGraph.cc
/// @brief CiPatGraph の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPatGraph.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatGraph::dump(
  Serializer& s
) const
{
  s.dump(mRepClass);
  s.dump(mInputNum);
  s.dump(mEdgeList);
}

END_NAMESPACE_YM_CLIB
