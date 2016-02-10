#ifndef YM_YM_CELL_H
#define YM_YM_CELL_H

/// @file ym/ym_cell.h
/// @brief ym-cell 用の定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2014, 2016 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.

/// @defgroup Cell セルライブラリ
///
/// セルライブラリを扱うためのクラスライブラリ

#include "ym_config.h"


//////////////////////////////////////////////////////////////////////
// 名前空間を定義するためのマクロ
//////////////////////////////////////////////////////////////////////

/// @brief cell の名前空間の開始
#define BEGIN_NAMESPACE_YM_CELL \
BEGIN_NAMESPACE_YM \
BEGIN_NAMESPACE(nsCell)

/// @brief cell の名前空間の終了
#define END_NAMESPACE_YM_CELL \
END_NAMESPACE(nsCell) \
END_NAMESPACE_YM

/// @namespace nsYm::nsCell
/// @brief セルライブラリ関係のクラスが属する名前空間
///
/// ただし，主要なものは nsYm にインポートされている．
/// 実装用のローカルな要素だけがこの名前空間に存在する．


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
// クラスの前方参照
//////////////////////////////////////////////////////////////////////

class CellArea;
class CellTime;
class CellCapacitance;
class CellResistance;

class CellLibrary;
class Cell;
class CellPin;
class CellBusType;
class CellBus;
class CellBundle;
class CellTiming;
class CellLutTemplate;
class CellLut;

class CellReader;
class CellMislibReader;
class CellDotlibReader;

class CellDumper;
class CellRestorer;

class CellGroup;
class CellClass;
class CellFFInfo;
class CellLatchInfo;
class CellPatGraph;
class CellPat2Graph;

END_NAMESPACE_YM_CELL


BEGIN_NAMESPACE_YM

using nsCell::CellArea;
using nsCell::CellTime;
using nsCell::CellCapacitance;
using nsCell::CellResistance;

using nsCell::CellLibrary;
using nsCell::Cell;
using nsCell::CellPin;
using nsCell::CellBusType;
using nsCell::CellBus;
using nsCell::CellBundle;
using nsCell::CellTiming;
using nsCell::CellLutTemplate;
using nsCell::CellLut;

using nsCell::CellReader;
using nsCell::CellMislibReader;
using nsCell::CellDotlibReader;

using nsCell::CellDumper;
using nsCell::CellRestorer;

using nsCell::CellGroup;
using nsCell::CellClass;
using nsCell::CellFFInfo;
using nsCell::CellLatchInfo;
using nsCell::CellPatGraph;


//////////////////////////////////////////////////////////////////////
/// @brief テクノロジを表す列挙型
//////////////////////////////////////////////////////////////////////
enum CellTechnology {
  kCellTechCmos,
  kCellTechFpga
};


//////////////////////////////////////////////////////////////////////
/// @brief 遅延モデルを表す列挙型
//////////////////////////////////////////////////////////////////////
enum CellDelayModel {
  kCellDelayGenericCmos,
  kCellDelayTableLookup,
  kCellDelayPiecewiseCmos,
  kCellDelayCmos2,
  kCellDelayDcm
};


//////////////////////////////////////////////////////////////////////
/// @brief ピンの方向を表す列挙型
//////////////////////////////////////////////////////////////////////
enum CellPinDirection {
  kCellPinInput,
  kCellPinOutput,
  kCellPinInout,
  kCellPinInternal
};


//////////////////////////////////////////////////////////////////////
/// @brief タイミングの条件を表す列挙型
//////////////////////////////////////////////////////////////////////
enum CellTimingSense {
  kCellPosiUnate = 1,
  kCellNegaUnate = 2,
  kCellNonUnate  = 3
};


/////////////////////////////////////////////////////////////////////
/// @brief タイミング情報の型を表す列挙型
//////////////////////////////////////////////////////////////////////
enum CellTimingType {
  kCellTimingCombinational          = 0,
  kCellTimingCombinationalRise      = 1,
  kCellTimingCombinationalFall      = 2,

  kCellTimingThreeStateEnable       = 3,
  kCellTimingThreeStateDisable      = 4,
  kCellTimingThreeStateEnableRise   = 5,
  kCellTimingThreeStateEnableFall   = 6,
  kCellTimingThreeStateDisableRise  = 7,
  kCellTimingThreeStateDisableFall  = 8,

  kCellTimingRisingEdge             = 9,
  kCellTimingFallingEdge            = 10,

  kCellTimingPreset                 = 11,
  kCellTimingClear                  = 12,

  kCellTimingHoldRising             = 13,
  kCellTimingHoldFalling            = 14,

  kCellTimingSetupRising            = 15,
  kCellTimingSetupFalling           = 16,

  kCellTimingRecoveryRising         = 17,
  kCellTimingRecoveryFalling        = 18,

  kCellTimingSkewRising             = 19,
  kCellTimingSkewFalling            = 20,

  kCellTimingRemovalRising          = 21,
  kCellTimingRemovalFalling         = 22,

  kCellTimingNonSeqSetupRising      = 23,
  kCellTimingNonSeqSetupFalling     = 24,
  kCellTimingNonSeqHoldRising       = 25,
  kCellTimingNonSeqHoldFalling      = 26,

  kCellTimingNochangeHighHigh       = 27,
  kCellTimingNochangeHighLow        = 28,
  kCellTimingNochangeLowHigh        = 29,
  kCellTimingNochangeLowLow         = 30
};


//////////////////////////////////////////////////////////////////////
/// @brief ルックアップテーブルの変数の型
//////////////////////////////////////////////////////////////////////
enum CellVarType {
  kCellVarInputNetTransition,

  kCellVarTotalOutputNetCapacitance,
  kCellVarOutputNetLength,
  kCellVarOutputNetWireCap,
  kCellVarOutputNetPinCap,

  kCellVarRelatedOutTotalOutputNetCapacitance,
  kCellVarRelatedOutOutputNetLength,
  kCellVarRelatedOutOutputNetWireCap,
  kCellVarRelatedOutOutputNetPinCap,

  kCellVarConstrainedPinTransition,

  kCellVarRelatedPinTransition,

  kCellVarNone
};


//////////////////////////////////////////////////////////////////////
/// @brief パタングラフのノードの型
//////////////////////////////////////////////////////////////////////
enum CellPatType {
  kCellPatInput = 0,
  kCellPatAnd   = 2,
  kCellPatXor   = 3
};

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] delay_model 遅延モデル
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   CellDelayModel delay_model);

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] timing_sense タイミングセンス
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   CellTimingSense timing_sense);


/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] timing_type タイミング条件
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   CellTimingType timing_type);

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] var_type 変数の型
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   CellVarType var_type);


END_NAMESPACE_YM

#endif // YM_YM_CELL_H
