
/// @file MislibPin.cc
/// @brief MislibPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibPin.h"
#include "MislibStr.h"
#include "MislibNum.h"
#include "MislibPhase.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibPin
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibPin::MislibPin(const FileRegion& loc,
		     const MislibStr* name,
		     const MislibPhase* phase,
		     const MislibNum* input_load,
		     const MislibNum* max_load,
		     const MislibNum* rise_block_delay,
		     const MislibNum* rise_fanout_delay,
		     const MislibNum* fall_block_delay,
		     const MislibNum* fall_fanout_delay) :
  MislibNode(loc),
  mName(name),
  mPhase(phase),
  mInputLoad(input_load),
  mMaxLoad(max_load),
  mRiseBlockDelay(rise_block_delay),
  mRiseFanoutDelay(rise_fanout_delay),
  mFallBlockDelay(fall_block_delay),
  mFallFanoutDelay(fall_fanout_delay)
{
  mNext = nullptr;
}

// デストラクタ
MislibPin::~MislibPin()
{
}

// 内容を出力する．
// デバッグ用
void
MislibPin::dump(ostream& s) const
{
  s << "<PIN>" << endl;
  dump_loc(s);

  s << "<NAME>" << endl;
  if ( name() ) {
    name()->dump(s);
  }
  else {
    s << "*" << endl;
  }
  s << "</NAME>" << endl;

  s << "<PHASE>" << endl;
  phase()->dump(s);
  s << "</PHASE>" << endl;

  s << "<INPUT_LOAD>" << endl;
  input_load()->dump(s);
  s << "</INPUT_LOAD>" << endl;

  s << "<MAX_LOAD>" << endl;
  max_load()->dump(s);
  s << "</MAX_LOAD>" << endl;

  s << "<RISE_BLOCK_DELAY>" << endl;
  rise_block_delay()->dump(s);
  s << "</RISE_BLOCK_DELAY>" << endl;

  s << "<RISE_FANOUT_DELAY>" << endl;
  rise_fanout_delay()->dump(s);
  s << "</RISE_FANOUT_DELAY>" << endl;

  s << "<FALL_BLOCK_DELAY>" << endl;
  fall_block_delay()->dump(s);
  s << "</FALL_BLOCK_DELAY>" << endl;

  s << "<FALLE_FANOUT_DELAY>" << endl;
  fall_fanout_delay()->dump(s);
  s << "</FALL_FANOUT_DELAY>" << endl;

  s << "</PIN>" << endl;
}

END_NAMESPACE_YM_MISLIB
