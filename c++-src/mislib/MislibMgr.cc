
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
MislibMgr::MislibMgr() :
  mAlloc(4096)
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
  mAlloc.destroy();
}

// 文字列ノードを生成する．
MislibStr*
MislibMgr::new_str(const FileRegion& loc,
		   ShString str)
{
  void* p = mAlloc.get_memory(sizeof(MislibStr));
  return new (p) MislibStr(loc, str);
}

// 数値ノードを生成する．
MislibNum*
MislibMgr::new_num(const FileRegion& loc,
		   double num)
{
  void* p = mAlloc.get_memory(sizeof(MislibNum));
  return new (p) MislibNum(loc, num);
}

// NONINV ノードを生成する．
MislibPhase*
MislibMgr::new_noninv(const FileRegion& loc)
{
  void* p = mAlloc.get_memory(sizeof(MislibNoninv));
  return new (p) MislibNoninv(loc);
}

// INV ノードを生成する．
MislibPhase*
MislibMgr::new_inv(const FileRegion& loc)
{
  void* p = mAlloc.get_memory(sizeof(MislibInv));
  return new (p) MislibInv(loc);
}

// UNKNOWN ノードを生成する．
MislibPhase*
MislibMgr::new_unknown(const FileRegion& loc)
{
  void* p = mAlloc.get_memory(sizeof(MislibUnknown));
  return new (p) MislibUnknown(loc);
}

// 定数0ノードを生成する．
MislibExpr*
MislibMgr::new_const0(const FileRegion& loc)
{
  void* p = mAlloc.get_memory(sizeof(MislibConst0));
  return new (p) MislibConst0(loc);
}

// 定数1ノードを生成する．
MislibExpr*
MislibMgr::new_const1(const FileRegion& loc)
{
  void* p = mAlloc.get_memory(sizeof(MislibConst1));
  return new (p) MislibConst1(loc);
}

// NOT ノードを生成する．
MislibExpr*
MislibMgr::new_not(const FileRegion& loc,
		   const MislibExpr* child1)
{
  void* p = mAlloc.get_memory(sizeof(MislibNot));
  return new (p) MislibNot(loc, child1);
}

// AND ノードを生成する．
MislibExpr*
MislibMgr::new_and(const FileRegion& loc,
		   const MislibExpr* child1,
		   const MislibExpr* child2)
{
  void* p = mAlloc.get_memory(sizeof(MislibAnd));
  return new (p) MislibAnd(loc, child1, child2);
}

// OR ノードを生成する．
MislibExpr*
MislibMgr::new_or(const FileRegion& loc,
		  const MislibExpr* child1,
		  const MislibExpr* child2)
{
  void* p = mAlloc.get_memory(sizeof(MislibOr));
  return new (p) MislibOr(loc, child1, child2);
}

// XOR ノードを生成する．
MislibExpr*
MislibMgr::new_xor(const FileRegion& loc,
		   const MislibExpr* child1,
		   const MislibExpr* child2)
{
  void* p = mAlloc.get_memory(sizeof(MislibXor));
  return new (p) MislibXor(loc, child1, child2);
}

// @brief 変数ノードを生成する．
MislibExpr*
MislibMgr::new_varname(const FileRegion& loc,
		       ShString str)
{
  void* p = mAlloc.get_memory(sizeof(MislibVarName));
  return new (p) MislibVarName(loc, str);
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
  void* p = mAlloc.get_memory(sizeof(MislibPin));
  return new (p) MislibPin(loc, name, phase,
			   input_load, max_load,
			   rise_block_delay, rise_fanout_delay,
			   fall_block_delay, fall_fanout_delay);
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

  void* p = mAlloc.get_memory(sizeof(MislibGate));
  return new (p) MislibGate(loc, name, area,
			    oname, expr,
			    ipin_top);
}

END_NAMESPACE_YM_MISLIB
