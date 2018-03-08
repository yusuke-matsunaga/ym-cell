
/// @file MislibStr.cc
/// @brief MislibStr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibStr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibStr
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibStr::MislibStr(const FileRegion& loc,
		     ShString str) :
  MislibNode(loc),
  mStr(str)
{
}

// デストラクタ
MislibStr::~MislibStr()
{
}

// 内容を出力する．
// デバッグ用
void
MislibStr::dump(ostream& s) const
{
  s << "<STR>" << endl;
  dump_loc(s);
  s << str() << endl
    << "</STR>" << endl;
}

END_NAMESPACE_YM_MISLIB
