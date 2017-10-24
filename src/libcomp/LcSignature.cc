
/// @file LcSignature.cc
/// @brief LcSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "LcSignature.h"
#include "ym/ClibCell.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcSignature
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LcSignature::LcSignature()
{
  mTypeBits = 0;
  mInputNum = 0;
  mOutputNum = 0;
}

// @brief コピーコンストラクタ
// @param[in] src コピー元のオブジェクト
LcSignature::LcSignature(const LcSignature& src) :
  mTypeBits(src.mTypeBits),
  mInputNum(src.mInputNum),
  mOutputNum(src.mOutputNum),
  mOutputBits(src.mOutputBits),
  mClockFunc(src.mClockFunc),
  mNextStateFunc(src.mNextStateFunc),
  mClearFunc(src.mClearFunc),
  mPresetFunc(src.mPresetFunc),
  mOutputFunc(src.mOutputFunc),
  mTristateFunc(src.mTristateFunc)
{
}

// @brief 変換付きのコピーコンストラクタ
// @param[in] src コピー元のオブジェクト
// @param[in] xmap 変換マップ
LcSignature::LcSignature(const LcSignature& src,
			 const NpnMapM& xmap) :
  mTypeBits(src.mTypeBits),
  mInputNum(src.mInputNum),
  mOutputNum(src.mOutputNum),
  mOutputBits(src.mOutputBits),
  mClockFunc(src.mClockFunc),
  mNextStateFunc(src.mNextStateFunc),
  mClearFunc(src.mClearFunc),
  mPresetFunc(src.mPresetFunc),
  mOutputFunc(src.mOutputFunc),
  mTristateFunc(src.mTristateFunc)
{
}

// @brief 1出力の論理セルのシグネチャを作るコンストラクタ
// @param[in] expr 論理式
LcSignature::LcSignature(const Expr& expr) :
  mInputNum(expr.input_size()),
  mOutputNum(1),
  mOutputBits(mOutputNum, 0U),
  mOutputFunc(mOutputNum),
  mTristateFunc(mOutputNum)
{
  mTypeBits = kLogicType;
  mOutputBits[0] = 1U;
  mOutputFunc[0] = expr.make_tv();
}

// @brief 単純なFFセル/ラッチセルのシグネチャを作るコンストラクタ
// @param[in] type 種類 (kFFType/kLatchType)
// @param[in] has_q Q出力の有無
// @param[in] has_xq 反転Q出力の有無
// @param[in] has_clear クリア端子の有無
// @param[in] has_preset プリセット端子の有無
LcSignature::LcSignature(Type type,
			 bool has_q,
			 bool has_xq,
			 bool has_clear,
			 bool has_preset) :
  mTypeBits(type),
  mOutputNum(has_q ? (has_xq ? 2 : 1) : (has_xq ? 1 : 0)),
  mOutputBits(mOutputNum, 0U),
  mOutputFunc(mOutputNum),
  mTristateFunc(mOutputNum)
{
  ASSERT_COND( type != kLogicType );

  VarId iq_var(0);
  VarId iqn_var(1);
  VarId clock_var(2);
  VarId data_var(3);
  VarId clear_var;
  VarId preset_var;
  ymuint ni = 4;
  if ( has_clear ) {
    clear_var = VarId(ni);
    ++ ni;
    mTypeBits |= 4U;
  }
  if ( has_preset ) {
    preset_var = VarId(ni);
    ++ ni;
    mTypeBits |= 8U;
  }
  mInputNum = ni - 2;
  mClockFunc = TvFunc::posi_literal(ni, clock_var);
  mNextStateFunc = TvFunc::posi_literal(ni, data_var);
  if ( has_clear ) {
    mClearFunc = TvFunc::posi_literal(ni, clear_var);
  }
  if ( has_preset ) {
    mPresetFunc = TvFunc::posi_literal(ni, preset_var);
  }
  ymuint no = 0;
  if ( has_q ) {
    mOutputBits[no] = 1U;
    mOutputFunc[no] = TvFunc::posi_literal(ni, iq_var);
    ++ no;
  }
  if ( has_xq ) {
    mOutputBits[no] = 1U;
    mOutputFunc[no] = TvFunc::posi_literal(ni, iqn_var);
    ++ no;
  }
}

// @brief コンストラクタ
// @param[in] cell セル
LcSignature::LcSignature(const ClibCell* cell) :
  mInputNum(cell->input_num()),
  mOutputNum(cell->output_num()),
  mOutputBits(mOutputNum, 0U),
  mOutputFunc(mOutputNum),
  mTristateFunc(mOutputNum)
{
  ymuint ni = mInputNum;
  if ( cell->is_logic() ) {
    mTypeBits = kLogicType;
  }
  else {
    ni += 2;
    if ( cell->is_ff() ) {
      mTypeBits = kFFType;
      mClockFunc = cell->clock_expr().make_tv(ni);
      mNextStateFunc = cell->next_state_expr().make_tv(ni);
    }
    if ( cell->is_latch() ) {
      mTypeBits = kLatchType;
      mClockFunc = cell->enable_expr().make_tv(ni);
      mNextStateFunc = cell->data_in_expr().make_tv(ni);
    }
    if ( cell->has_clear() ) {
      mTypeBits |= 4U;
      mClearFunc = cell->clear_expr().make_tv(ni);
    }
    if ( cell->has_preset() ) {
      mTypeBits |= 8U;
      mPresetFunc = cell->preset_expr().make_tv(ni);
    }
  }

  for (ymuint i = 0; i < mOutputNum; ++ i) {
    if ( cell->has_logic(i) ) {
      mOutputBits[i] |= 1U;
      mOutputFunc[i] = cell->logic_expr(i).make_tv(ni);
    }
    if ( cell->has_tristate(i) ) {
      mOutputBits[i] |= 2U;
      mTristateFunc[i] = cell->tristate_expr(i).make_tv(ni);
    }
  }
}

// @brief デストラクタ
LcSignature::~LcSignature()
{
}


BEGIN_NONAMESPACE

void
tvfunc_to_str(const TvFunc& f,
	      ostream& buf)
{
  ymuint n = f.nblk();
  for (ymuint i = 0; i < n; ++ i) {
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
  if ( type() != kLogicType ) {
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
  for (ymuint i = 0; i < mOutputNum; ++ i) {
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
LcSignature::operator==(const LcSignature& right) const
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

  for (ymuint i = 0; i < mOutputNum; ++ i ) {
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
