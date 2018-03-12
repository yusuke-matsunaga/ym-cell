
/// @file DotlibNum.cc
/// @brief DotlibNum の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibNum.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibNum
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
DotlibNum::DotlibNum(const FileRegion& loc) :
  DotlibNode(loc)
{
}

// @brief デストラクタ
DotlibNum::~DotlibNum()
{
}

END_NAMESPACE_YM_DOTLIB
