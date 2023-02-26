#ifndef YM_CLIB_H
#define YM_CLIB_H

/// @file ym/clib.h
/// @brief ym-clib 用の定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2014, 2016, 2017, 2021 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.

/// @defgroup ClibCellGroup セルライブラリ
///
/// セルライブラリを扱うためのクラスライブラリ

#include "ym_config.h"
#include "ym/BinEnc.h"
#include "ym/BinDec.h"


//////////////////////////////////////////////////////////////////////
// 名前空間を定義するためのマクロ
//////////////////////////////////////////////////////////////////////

/// @brief cell の名前空間の開始
#define BEGIN_NAMESPACE_YM_CLIB \
BEGIN_NAMESPACE_YM \
BEGIN_NAMESPACE(nsClib)

/// @brief cell の名前空間の終了
#define END_NAMESPACE_YM_CLIB \
END_NAMESPACE(nsClib) \
END_NAMESPACE_YM

/// @namespace nsYm::nsClib
/// @brief セルライブラリ関係のクラスが属する名前空間
///
/// ただし，主要なものは nsYm にインポートされている．
/// 実装用のローカルな要素だけがこの名前空間に存在する．


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラスの前方参照
//////////////////////////////////////////////////////////////////////

class ClibArea;
class ClibTime;
class ClibCapacitance;
class ClibResistance;

class ClibCellLibrary;
class ClibCell;
class ClibPin;
class ClibBusType;
class ClibBus;
class ClibBundle;
class ClibTiming;
class ClibLutTemplate;
class ClibLut;

class ClibCellGroup;
class ClibCellClass;
class ClibIOMap;
class ClibPinMap;
class ClibPatGraph;

END_NAMESPACE_YM_CLIB


BEGIN_NAMESPACE_YM

using nsClib::ClibArea;
using nsClib::ClibTime;
using nsClib::ClibCapacitance;
using nsClib::ClibResistance;

using nsClib::ClibCellLibrary;
using nsClib::ClibCell;
using nsClib::ClibPin;
using nsClib::ClibBusType;
using nsClib::ClibBus;
using nsClib::ClibBundle;
using nsClib::ClibTiming;
using nsClib::ClibLutTemplate;
using nsClib::ClibLut;

using nsClib::ClibCellGroup;
using nsClib::ClibCellClass;
using nsClib::ClibIOMap;
using nsClib::ClibPinMap;
using nsClib::ClibPatGraph;


//////////////////////////////////////////////////////////////////////
/// @brief テクノロジを表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibTechnology : ymuint8
{
  cmos,
  fpga,
  none
};


//////////////////////////////////////////////////////////////////////
/// @brief 遅延モデルを表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibDelayModel : ymuint8
{
  generic_cmos,
  table_lookup,
  piecewise_cmos,
  cmos2,
  dcm,
  polynomial,
  none
};


//////////////////////////////////////////////////////////////////////
/// @brief ピンの方向を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibDirection : ymuint8
{
  input,
  output,
  inout,
  internal,
  none
};


//////////////////////////////////////////////////////////////////////
/// @brief タイミングの条件を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibTimingSense : ymuint8
{
  positive_unate = 1,
  negative_unate = 2,
  non_unate  = 3,
  none
};


/////////////////////////////////////////////////////////////////////
/// @brief タイミング情報の型を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibTimingType : ymuint8
{
  combinational            = 0,
  combinational_rise       = 1,
  combinational_fall       = 2,

  three_state_enable       = 3,
  three_state_disable      = 4,
  three_state_enable_rise  = 5,
  three_state_enable_fall  = 6,
  three_state_disable_rise = 7,
  three_state_disable_fall = 8,

  rising_edge              = 9,
  falling_edge             = 10,

  preset                   = 11,
  clear                    = 12,

  hold_rising              = 13,
  hold_falling             = 14,

  setup_rising             = 15,
  setup_falling            = 16,

  recovery_rising          = 17,
  recovery_falling         = 18,

  skew_rising              = 19,
  skew_falling             = 20,

  removal_rising           = 21,
  removal_falling          = 22,

  non_seq_setup_rising     = 23,
  non_seq_setup_falling    = 24,
  non_seq_hold_rising      = 25,
  non_seq_hold_falling     = 26,

  nochange_high_high      = 27,
  nochange_high_low        = 28,
  nochange_low_high        = 29,
  nochange_low_low         = 30,

  none
};


//////////////////////////////////////////////////////////////////////
/// @brief ルックアップテーブルの変数の型
//////////////////////////////////////////////////////////////////////
enum class ClibVarType : ymuint8
{
  input_net_transition,

  total_output_net_capacitance,
  output_net_length,
  output_net_wire_cap,
  output_net_pin_cap,

  equal_or_opposite_output_net_capacitance,
  input_transition_time,

  related_out_total_output_net_capacitance,
  related_out_output_net_length,
  related_out_output_net_wire_cap,
  related_out_output_net_pin_cap,

  constrained_pin_transition,

  related_pin_transition,

  none
};


//////////////////////////////////////////////////////////////////////
/// @brief セルの種類
//////////////////////////////////////////////////////////////////////
enum class ClibCellType : ymuint8
{
  None    = 0, ///< なし(不正値)
  Logic   = 1, ///< 組み合わせ論理
  FF      = 2, ///< master-slave FF
  Latch   = 3, ///< master-slave latch
  FSM     = 4, ///< finite state machine
};


//////////////////////////////////////////////////////////////////////
/// @brief clear_preset_var の値
//////////////////////////////////////////////////////////////////////
enum class ClibCPV : ymuint8
{
  L = 0, ///< low(0)
  H = 1, ///< high(1)
  N = 2, ///< not change
  T = 3, ///< toggle
  X = 4, ///< unknown
};

/// @brief ClibCPV の全ての値のリスト
///
/// @code
/// for ( auto cpv: CPV_list ) {
///    ...
/// }
/// のように用いられることを想定している．
const ClibCPV CPV_LIST[] = {
  ClibCPV::L,
  ClibCPV::H,
  ClibCPV::N,
  ClibCPV::T,
  ClibCPV::X
};


//////////////////////////////////////////////////////////////////////
/// @brief パタングラフのノードの型
//////////////////////////////////////////////////////////////////////
enum class ClibPatType : ymuint8
{
  Input = 0,
  And   = 2,
  Xor   = 3
};

/// @brief 無効なID番号を表す値
const SizeType CLIB_NULLID = -1;


//////////////////////////////////////////////////////////////////////
// ストリーム出力演算子
//////////////////////////////////////////////////////////////////////

/// @brief ClibDelayModel のストリーム出力演算子
/// @return s を返す．
ostream&
operator<<(
  ostream& s,                ///< [in] 出力先のストリーム
  ClibDelayModel delay_model ///< [in] 遅延モデル
);

/// @brief ClibTimingSense のストリーム出力演算子
/// @return s を返す．
ostream&
operator<<(
  ostream& s,                  ///< [in] 出力先のストリーム
  ClibTimingSense timing_sense ///< [in] タイミングセンス
);

/// @brief ClibTimingType のストリーム出力演算子
/// @return s を返す．
ostream&
operator<<(
  ostream& s,                ///< [in] 出力先のストリーム
  ClibTimingType timing_type ///< [in] タイミング条件
);

/// @brief ClibCPV のストリーム出力演算子
/// @return s を返す．
ostream&
operator<<(
  ostream& s,  ///< [in] 出力先のストリーム
  ClibCPV cpv  ///< [in] clear_preset_var の値
);

/// @brief ClibVarType のストリーム出力演算子
/// @return s を返す．
ostream&
operator<<(
  ostream& s,          ///< [in] 出力先のストリーム
  ClibVarType var_type ///< [in] 変数の型
);


//////////////////////////////////////////////////////////////////////
// バイナリ出力演算子
//////////////////////////////////////////////////////////////////////

/// @brief ClibTechnology のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,                ///< [in] 出力先のストリーム
  ClibTechnology technology ///< [in] テクノロジ
)
{
  s << static_cast<ymuint8>(technology);
  return s;
}

/// @brief ClibDelayModel のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,                 ///< [in] 出力先のストリーム
  ClibDelayModel delay_model ///< [in] 遅延モデル
)
{
  s << static_cast<ymuint8>(delay_model);
  return s;
}

/// @brief ClibTimingSense のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,                   ///< [in] 出力先のストリーム
  ClibTimingSense timing_sense ///< [in] タイミングセンス
)
{
  s << static_cast<ymuint8>(timing_sense);
  return s;
}

/// @brief ClibTimingType のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,                 ///< [in] 出力先のストリーム
  ClibTimingType timing_type ///< [in] タイミング条件
)
{
  s << static_cast<ymuint8>(timing_type);
  return s;
}

/// @brief ClibCPV のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,   ///< [in] 出力先のストリーム
  ClibCPV cpv  ///< [in] clear_preset_var の値
)
{
  s << static_cast<ymuint8>(cpv);
  return s;
}

/// @brief ClibVarType のバイナリ出力演算子
/// @return s を返す．
inline
BinEnc&
operator<<(
  BinEnc& s,           ///< [in] 出力先のストリーム
  ClibVarType var_type ///< [in] 変数の型
)
{
  s << static_cast<ymuint8>(var_type);
  return s;
}


//////////////////////////////////////////////////////////////////////
// バイナリ入力演算子
//////////////////////////////////////////////////////////////////////

/// @brief ClibTechnology のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,                 ///< [in] 入力元のストリーム
  ClibTechnology& technology ///< [out] テクノロジ
)
{
  ymuint8 tmp;
  s >> tmp;
  technology = static_cast<ClibTechnology>(tmp);
  return s;
}

/// @brief ClibDelayModel のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,                  ///< [in] 入力元のストリーム
  ClibDelayModel& delay_model ///< [out] 遅延モデル
)
{
  ymuint8 tmp;
  s >> tmp;
  delay_model = static_cast<ClibDelayModel>(tmp);
  return s;
}

/// @brief ClibTimingSense のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,                    ///< [in] 入力元のストリーム
  ClibTimingSense& timing_sense ///< [out] タイミングセンス
)
{
  ymuint8 tmp;
  s >> tmp;
  timing_sense = static_cast<ClibTimingSense>(tmp);
  return s;
}

/// @brief ClibTimingType のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,                  ///< [in] 入力元のストリーム
  ClibTimingType& timing_type ///< [out] タイミング条件
)
{
  ymuint8 tmp;
  s >> tmp;
  timing_type = static_cast<ClibTimingType>(tmp);
  return s;
}

/// @brief ClibCPV のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,    ///< [in] 入力元のストリーム
  ClibCPV& cpv  ///< [out] clear_preset_var の値
)
{
  ymuint8 tmp;
  s >> tmp;
  cpv = static_cast<ClibCPV>(tmp);
  return s;
}

/// @brief ClibVarType のバイナリ入力演算子
/// @return s を返す．
inline
BinDec&
operator>>(
  BinDec& s,            ///< [in] 入力元のストリーム
  ClibVarType& var_type ///< [out] 変数の型
)
{
  ymuint8 tmp;
  s >> tmp;
  var_type = static_cast<ClibVarType>(tmp);
  return s;
}

END_NAMESPACE_YM

#endif // YM_CLIB_H
