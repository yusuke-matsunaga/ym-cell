
/// @file CiLatchCell.cc
/// @brief CiLatchCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "CiLatchCell.h"
#include "cgmgr/CgSignature.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief single-stage 型のラッチセルを生成するクラスメソッド
unique_ptr<CiCell>
CiCell::new_Latch(
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& enable,
  const Expr& enable_also,
  const Expr& data_in,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* ptr = nullptr;
  if ( enable_also.is_valid() ) {
    ptr = new CiLatch2Cell{
      name, area,
      var1, var2,
      enable, enable_also,
      data_in,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  else {
    ptr = new CiLatchCell{
      name, area,
      var1, var2,
      enable,
      data_in,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    };
  }
  return unique_ptr<CiCell>{ptr};
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiLatchCell::type() const
{
  return ClibCellType::Latch;
}

// @brief ラッチセルの時に true を返す．
bool
CiLatchCell::is_latch() const
{
  return true;
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
Expr
CiLatchCell::data_in_expr() const
{
  return mDataIn;
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
Expr
CiLatchCell::enable_expr() const
{
  return mEnable;
}

// @brief シグネチャを返す．
CgSignature
CiLatchCell::make_signature() const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb + 2;
  SizeType no2 = no + nb + 2;
  vector<TvFunc> logic_list(no2);
  vector<TvFunc> tristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto opin = output(i);
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  TvFunc enable = enable_expr().make_tv(ni2);
  TvFunc enable2 = enable2_expr().make_tv(ni2);
  TvFunc data_in = data_in_expr().make_tv(ni2);
  TvFunc clear = clear_expr().make_tv(ni2);
  TvFunc preset = preset_expr().make_tv(ni2);
  return CgSignature::make_latch_sig(ni, no, nb, logic_list, tristate_list,
				     enable, enable2, data_in,
				     clear, preset,
				     clear_preset_var1(),
				     clear_preset_var2());
}

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump(
  Serializer& s
) const
{
  s.dump(static_cast<std::uint8_t>(3));
  dump_Latch(s);
}

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump_Latch(
  Serializer& s
) const
{
  dump_FL(s);
  s.dump(mEnable);
  s.dump(mDataIn);
}

// @brief 内容を復元する．
void
CiLatchCell::_restore(
  Deserializer& s
)
{
  restore_Latch(s);
}

// @brief 内容を読み込む．
void
CiLatchCell::restore_Latch(
  Deserializer& s
)
{
  restore_FL(s);
  s.restore(mEnable);
  s.restore(mDataIn);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatch2Cell::enable2_expr() const
{
  return mEnable2;
}

// @brief 内容をバイナリダンプする．
void
CiLatch2Cell::dump(
  Serializer& s
) const
{
  s.dump(static_cast<std::uint8_t>(4));
  dump_Latch(s);
  s.dump(mEnable2);
}

// @brief 内容を復元する．
void
CiLatch2Cell::_restore(
  Deserializer& s
)
{
  restore_Latch(s);
  s.restore(mEnable2);
}

END_NAMESPACE_YM_CLIB
