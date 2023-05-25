
/// @file CiPatGraph.cc
/// @brief CiPatGraph の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPatGraph.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatGraph::dump(
  BinEnc& bos
) const
{
  bos.write_64(mRepId);
  bos.write_64(mInputNum);
  bos.write_64(mEdgeList.size());
  for ( auto e: mEdgeList ) {
    bos.write_64(e);
  }
}

END_NAMESPACE_YM_CLIB
