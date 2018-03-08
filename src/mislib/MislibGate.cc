
/// @file MislibGate.cc
/// @brief MislibGate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibGate.h"
#include "MislibStr.h"
#include "MislibNum.h"
#include "MislibExpr.h"
#include "MislibPin.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibGate
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] name 名前を表すパース木
// @param[in] area 面積を表すパース木
// @param[in] opin_name 出力ピン名を表すパース木
// @param[in] opin_expr 出力の論理式を表すパース木
// @param[in] ipin_top 先頭の入力ピンを表すパース木
MislibGate::MislibGate(const FileRegion& loc,
		       const MislibStr* name,
		       const MislibNum* area,
		       const MislibStr* opin_name,
		       const MislibExpr* opin_expr,
		       const MislibPin* ipin_top) :
  MislibNode(loc),
  mName(name),
  mArea(area),
  mOpinName(opin_name),
  mOpinExpr(opin_expr),
  mIpinTop(ipin_top)
{
}

// @brief デストラクタ
MislibGate::~MislibGate()
{
}

// @brief 内容を出力する．
void
MislibGate::dump(ostream& s) const
{
  s << "<GATE>" << endl;
  dump_loc(s);

  s << "<NAME>" << endl;
  name()->dump(s);
  s << "</NAME>" << endl;

  s << "<AREA>" << endl;
  area()->dump(s);
  s << "</AREA>" << endl;

  s << "<OPIN_NAME>" << endl;
  opin_name()->dump(s);
  s << "</OPIN_NAME>" << endl;

  s << "<OPIN_EXPR>" << endl;
  opin_expr()->dump(s);
  s << "</OPIN_EXPR>" << endl;

  s << "<IPIN_LIST>" << endl;
  for ( auto pin = ipin_top(); pin != nullptr; pin = pin->next() ) {
    pin->dump(s);
  }
  s << "</IPIN_LIST>" << endl;

  s << "</GATE>" << endl;
}

END_NAMESPACE_YM_MISLIB
