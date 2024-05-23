
/// @file CiFFCell.cc
/// @brief CiFFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "CiFFCell.h"
#include "cgmgr/CgSignature.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief master/slave型のFFセルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_FF(
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& clocked_on,
  const Expr& clocked_on_also,
  const Expr& next_state,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* ptr = nullptr;
  if ( clocked_on_also.is_valid() ) {
    ptr = new CiFF2Cell{
      name, area,
      var1, var2,
      clocked_on, clocked_on_also,
      next_state,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  else {
    ptr = new CiFFCell{
      name, area,
      var1, var2,
      clocked_on,
      next_state,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  return unique_ptr<CiCell>{ptr};
}

//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiFFCell::type() const
{
  return ClibCellType::FF;
}

// @brief 組み合わせ論理タイプの時 true を返す．
bool
CiFFCell::is_logic() const
{
  return false;
}

// @brief FFセルの時に true を返す．
bool
CiFFCell::is_ff() const
{
  return true;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
Expr
CiFFCell::clock_expr() const
{
  return mClock;
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
Expr
CiFFCell::next_state_expr() const
{
  return mNextState;
}

// @brief シグネチャを返す．
CgSignature
CiFFCell::make_signature() const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb + 2;
  SizeType no2 = no + nb;
  vector<TvFunc> logic_list(no2);
  vector<TvFunc> tristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto opin = output(i);
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  TvFunc clock = clock_expr().make_tv(ni2);
  TvFunc clock2 = clock2_expr().make_tv(ni2);
  TvFunc next = next_state_expr().make_tv(ni2);
  TvFunc clear = clear_expr().make_tv(ni2);
  TvFunc preset = preset_expr().make_tv(ni2);
  return CgSignature::make_ff_sig(ni, no, nb,
				  logic_list, tristate_list,
				  clock, clock2, next,
				  clear, preset,
				  clear_preset_var1(),
				  clear_preset_var2());
}

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump(
  Serializer& s
) const
{
  s.out().write_8(1);
  dump_FF(s);
}

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump_FF(
  Serializer& s
) const
{
  dump_FL(s);
  mClock.dump(s.out());
  mNextState.dump(s.out());
}

// @brief 内容を復元する．
void
CiFFCell::_restore(
  Deserializer& s
)
{
  restore_FF(s);
}

// @brief 内容を復元する．
void
CiFFCell::restore_FF(
  Deserializer& s
)
{
  restore_FL(s);
  mClock.restore(s.in());
  mNextState.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFF2Cell::clock2_expr() const
{
  return mClock2;
}

// @brief 内容をバイナリダンプする．
void
CiFF2Cell::dump(
  Serializer& s
) const
{
  s.out().write_8(2);
  dump_FF(s);
  mClock2.dump(s.out());
}

// @brief 内容を復元する．
void
CiFF2Cell::_restore(
  Deserializer& s
)
{
  restore_FF(s);
  mClock2.restore(s.in());
}

END_NAMESPACE_YM_CLIB
