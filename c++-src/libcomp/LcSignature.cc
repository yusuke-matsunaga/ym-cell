
/// @file LcSignature.cc
/// @brief LcSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/LcSignature.h"
#include "ym/ClibCell.h"
#include "ym/Expr.h"
#include "ym/NpnMapM.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcSignature
//////////////////////////////////////////////////////////////////////

// @brief 変換付きのコピーコンストラクタ
LcSignature::LcSignature(
  const LcSignature& src,
  const NpnMap& xmap
) : mTypeBits{src.mTypeBits},
    mInputNum{src.mInputNum},
    mOutputNum{src.mOutputNum},
    mOutputBits{src.mOutputBits},
    mClockFunc{src.mClockFunc},
    mNextStateFunc{src.mNextStateFunc},
    mClearFunc{src.mClearFunc},
    mPresetFunc{src.mPresetFunc},
    mOutputFunc{src.mOutputFunc},
    mTristateFunc{src.mTristateFunc}
{
  ASSERT_COND( mOutputNum == 1 &&
	       src.type() == LcType::Logic &&
	       !src.is_tristate(0) );
  mOutputFunc[0] = mOutputFunc[0].xform(xmap);
}

// @brief 1出力の論理セルのシグネチャを作るコンストラクタ
// @param[in] expr 論理式
LcSignature::LcSignature(
  const Expr& expr
) : mInputNum{expr.input_size()},
    mOutputNum{1},
    mOutputBits{0U},
    mOutputFunc{expr.make_tv()},
    mTristateFunc{TvFunc::make_zero(mInputNum)}
{
  set_Logic();
}

// @brief 単純なFFセル/ラッチセルのシグネチャを作るコンストラクタ
LcSignature::LcSignature(
  LcType type,
  bool has_q,
  bool has_xq,
  bool has_clear,
  bool has_preset
) : mOutputNum{has_q ? (has_xq ? 2U : 1U) : (has_xq ? 1U : 0U)},
    mOutputBits(mOutputNum, 0U),
    mOutputFunc(mOutputNum),
    mTristateFunc(mOutputNum)
{
  if ( type == LcType::FF ) {
    set_FF();
  }
  else if ( type == LcType::Latch ) {
    set_Latch();
  }
  else {
    ASSERT_NOT_REACHED;
  }

  VarId iq_var(0);
  VarId iqn_var(1);
  VarId clock_var(2);
  VarId data_var(3);
  VarId clear_var;
  VarId preset_var;
  SizeType ni = 4;
  if ( has_clear ) {
    clear_var = VarId(ni);
    ++ ni;
    mTypeBits.set(2, 1);
  }
  if ( has_preset ) {
    preset_var = VarId(ni);
    ++ ni;
    mTypeBits.set(3, 1);
  }
  mInputNum = ni - 2; // q と xq の入力を除く
  mClockFunc = TvFunc::make_posi_literal(ni, clock_var);
  mNextStateFunc = TvFunc::make_posi_literal(ni, data_var);
  if ( has_clear ) {
    mClearFunc = TvFunc::make_posi_literal(ni, clear_var);
  }
  if ( has_preset ) {
    mPresetFunc = TvFunc::make_posi_literal(ni, preset_var);
  }
  int no = 0;
  if ( has_q ) {
    mOutputBits[no][0] = true;
    mOutputBits[no][1] = false;
    mOutputFunc[no] = TvFunc::make_posi_literal(ni, iq_var);
    ++ no;
  }
  if ( has_xq ) {
    mOutputBits[no][0] = true;
    mOutputBits[no][1] = false;
    mOutputFunc[no] = TvFunc::make_nega_literal(ni, iq_var);
    ++ no;
  }
}

// @brief コンストラクタ
LcSignature::LcSignature(
  const ClibCell* cell
) : mInputNum{cell->input_num()},
    mOutputNum{cell->output_num()},
    mOutputBits(mOutputNum, 0U),
    mOutputFunc(mOutputNum),
    mTristateFunc(mOutputNum)
{
  auto ni = mInputNum;
  if ( cell->is_logic() ) {
    set_Logic();
  }
  else {
    ni += 2;
    if ( cell->is_ff() ) {
      set_FF();
      mClockFunc = cell->clock_expr().make_tv(ni);
      mNextStateFunc = cell->next_state_expr().make_tv(ni);
    }
    if ( cell->is_latch() ) {
      set_Latch();
      mClockFunc = cell->enable_expr().make_tv(ni);
      mNextStateFunc = cell->data_in_expr().make_tv(ni);
    }
    if ( cell->has_clear() ) {
      mTypeBits.set(2, 1);
      mClearFunc = cell->clear_expr().make_tv(ni);
    }
    if ( cell->has_preset() ) {
      mTypeBits.set(3, 1);
      mPresetFunc = cell->preset_expr().make_tv(ni);
    }
  }

  for ( auto i = 0; i < mOutputNum; ++ i ) {
    if ( cell->has_logic(i) ) {
      mOutputBits[i].set(0);
      mOutputFunc[i] = cell->logic_expr(i).make_tv(ni);
    }
    if ( cell->has_tristate(i) ) {
      mOutputBits[i].set(1);
      mTristateFunc[i] = cell->tristate_expr(i).make_tv(ni);
    }
  }
}


BEGIN_NONAMESPACE

void
tvfunc_to_str(
  const TvFunc& f,
  ostream& buf
)
{
  // 単純に内部の64ビット符号なし整数を
  // 16進数で出力する．
  auto n = f.nblk();
  for ( auto i = 0; i < n; ++ i ) {
    ymuint64 b = f.raw_data(i);
    buf << hex << b << dec;
  }
}

END_NONAMESPACE

// @brief 内容を表す文字列を作る．
string
LcSignature::str() const
{
  ostringstream buf;
  buf << mTypeBits << ":"
      << mInputNum << ":" << mOutputNum << ":";
  if ( type() != LcType::Logic ) {
    tvfunc_to_str(mClockFunc, buf);
    buf << ":";
    tvfunc_to_str(mNextStateFunc, buf);
    buf << ":";
    if ( has_clear() ) {
      tvfunc_to_str(mClearFunc, buf);
    }
    buf << ":";
    if ( has_preset() ) {
      tvfunc_to_str(mPresetFunc, buf);
    }
    buf << ":";
  }
  for ( int i = 0; i < mOutputNum; ++ i ) {
    if ( has_logic(i) ) {
      tvfunc_to_str(mOutputFunc[i], buf);
    }
    buf << ":";
    if ( is_tristate(i) ) {
      tvfunc_to_str(mTristateFunc[i], buf);
    }
    buf << ":";
  }
  return buf.str();
}

// @brief 等価比較演算子
bool
LcSignature::operator==(
  const LcSignature& right
) const
{
  if ( mTypeBits != right.mTypeBits ) {
    return false;
  }
  if ( input_num() != right.input_num() ) {
    return false;
  }
  if ( output_num() != right.output_num() ) {
    return false;
  }

  if ( mClockFunc != right.mClockFunc ) {
    return false;
  }

  if ( mNextStateFunc != right.mNextStateFunc ) {
    return false;
  }

  if ( mClearFunc != right.mClearFunc ) {
    return false;
  }

  if ( mPresetFunc != right.mPresetFunc ) {
    return false;
  }

  for ( SizeType i = 0; i < mOutputNum; ++ i ) {
    if ( mOutputBits[i] != right.mOutputBits[i] ) {
      return false;
    }
    if ( mOutputFunc[i] != right.mOutputFunc[i] ) {
      return false;
    }
    if ( mTristateFunc[i] != right.mTristateFunc[i] ) {
      return false;
    }
  }

  return true;
}

END_NAMESPACE_YM_CLIB_LIBCOMP
