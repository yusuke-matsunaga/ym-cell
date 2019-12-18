
/// @file MislibMgr.cc
/// @brief MislibMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibMgr.h"
#include "MislibGate.h"
#include "MislibPin.h"
#include "MislibPhase.h"
#include "MislibConst.h"
#include "MislibNot.h"
#include "MislibBop.h"
#include "MislibVarName.h"
#include "MislibNum.h"
#include "MislibStr.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibMgr
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibMgr::MislibMgr()
{
}

// デストラクタ
MislibMgr::~MislibMgr()
{
  clear();
}

// 今までに生成したすべてのオブジェクトを解放する．
void
MislibMgr::clear()
{
  for ( auto node: mNodeList ) {
    delete node;
  }
  mNodeList.clear();
}

// 文字列ノードを生成する．
MislibStr*
MislibMgr::new_str(const FileRegion& loc,
		   ShString str)
{
  auto node = new MislibStr(loc, str);
  mNodeList.push_back(node);
  return node;
}

// 数値ノードを生成する．
MislibNum*
MislibMgr::new_num(const FileRegion& loc,
		   double num)
{
  auto node = new MislibNum(loc, num);
  mNodeList.push_back(node);
  return node;
}

// NONINV ノードを生成する．
MislibPhase*
MislibMgr::new_noninv(const FileRegion& loc)
{
  auto node = new MislibNoninv(loc);
  mNodeList.push_back(node);
  return node;
}

// INV ノードを生成する．
MislibPhase*
MislibMgr::new_inv(const FileRegion& loc)
{
  auto node = new MislibInv(loc);
  mNodeList.push_back(node);
  return node;
}

// UNKNOWN ノードを生成する．
MislibPhase*
MislibMgr::new_unknown(const FileRegion& loc)
{
  auto node = new MislibUnknown(loc);
  mNodeList.push_back(node);
  return node;
}

// 定数0ノードを生成する．
MislibExpr*
MislibMgr::new_const0(const FileRegion& loc)
{
  auto node = new MislibConst0(loc);
  mNodeList.push_back(node);
  return node;
}

// 定数1ノードを生成する．
MislibExpr*
MislibMgr::new_const1(const FileRegion& loc)
{
  auto node = new MislibConst1(loc);
  mNodeList.push_back(node);
  return node;
}

// NOT ノードを生成する．
MislibExpr*
MislibMgr::new_not(const FileRegion& loc,
		   const MislibExpr* child1)
{
  auto node = new MislibNot(loc, child1);
  mNodeList.push_back(node);
  return node;
}

// AND ノードを生成する．
MislibExpr*
MislibMgr::new_and(const FileRegion& loc,
		   const MislibExpr* child1,
		   const MislibExpr* child2)
{
  auto node = new MislibAnd(loc, child1, child2);
  mNodeList.push_back(node);
  return node;
}

// OR ノードを生成する．
MislibExpr*
MislibMgr::new_or(const FileRegion& loc,
		  const MislibExpr* child1,
		  const MislibExpr* child2)
{
  auto node = new MislibOr(loc, child1, child2);
  mNodeList.push_back(node);
  return node;
}

// XOR ノードを生成する．
MislibExpr*
MislibMgr::new_xor(const FileRegion& loc,
		   const MislibExpr* child1,
		   const MislibExpr* child2)
{
  auto node = new MislibXor(loc, child1, child2);
  mNodeList.push_back(node);
  return node;
}

// @brief 変数ノードを生成する．
MislibExpr*
MislibMgr::new_varname(const FileRegion& loc,
		       ShString str)
{
  auto node = new MislibVarName(loc, str);
  mNodeList.push_back(node);
  return node;
}

// PIN ノードを生成する．
MislibPin*
MislibMgr::new_pin(const FileRegion& loc,
		   const MislibStr* name,
		   const MislibPhase* phase,
		   const MislibNum* input_load,
		   const MislibNum* max_load,
		   const MislibNum* rise_block_delay,
		   const MislibNum* rise_fanout_delay,
		   const MislibNum* fall_block_delay,
		   const MislibNum* fall_fanout_delay)
{
  auto node = new MislibPin(loc, name, phase,
			    input_load, max_load,
			    rise_block_delay, rise_fanout_delay,
			    fall_block_delay, fall_fanout_delay);
  mNodeList.push_back(node);
  return node;
}

// GATE ノードを生成する．
MislibGate*
MislibMgr::new_gate(const FileRegion& loc,
		    const MislibStr* name,
		    const MislibNum* area,
		    const MislibStr* oname,
		    const MislibExpr* expr,
		    const MislibPin* ipin_top)
{
  ASSERT_COND( name != nullptr );
  ASSERT_COND( area != nullptr );
  ASSERT_COND( oname != nullptr );
  ASSERT_COND( expr != nullptr );

  auto node = new MislibGate(loc, name, area,
			     oname, expr,
			     ipin_top);
  mNodeList.push_back(node);
  return node;
}

END_NAMESPACE_YM_MISLIB
