#ifndef YM_CLIB_H
#define YM_CLIB_H

/// @file ym/clib.h
/// @brief ym-clib 用の定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2014, 2016, 2017 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.

/// @defgroup ClibCellGroup セルライブラリ
///
/// セルライブラリを扱うためのクラスライブラリ

#include "ym_config.h"


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
class ClibCellList;
class ClibCellPin;
class ClibCellPinList;
class ClibBusType;
class ClibBus;
class ClibBundle;
class ClibTiming;
class ClibLutTemplate;
class ClibLut;

class ClibReader;
class ClibMislibReader;
class ClibDotlibReader;

class ClibDumper;
class ClibRestorer;

class ClibCellGroup;
class ClibCellGroupList;
class ClibCellClass;
class ClibFFInfo;
class ClibLatchInfo;
class ClibPatGraph;
class ClibPat2Graph;

END_NAMESPACE_YM_CLIB


BEGIN_NAMESPACE_YM

using nsClib::ClibArea;
using nsClib::ClibTime;
using nsClib::ClibCapacitance;
using nsClib::ClibResistance;

using nsClib::ClibCellLibrary;
using nsClib::ClibCell;
using nsClib::ClibCellPin;
using nsClib::ClibBusType;
using nsClib::ClibBus;
using nsClib::ClibBundle;
using nsClib::ClibTiming;
using nsClib::ClibLutTemplate;
using nsClib::ClibLut;

using nsClib::ClibReader;
using nsClib::ClibMislibReader;
using nsClib::ClibDotlibReader;

using nsClib::ClibDumper;
using nsClib::ClibRestorer;

using nsClib::ClibCellGroup;
using nsClib::ClibCellClass;
using nsClib::ClibFFInfo;
using nsClib::ClibLatchInfo;
using nsClib::ClibPatGraph;


//////////////////////////////////////////////////////////////////////
/// @brief テクノロジを表す列挙型
//////////////////////////////////////////////////////////////////////
enum ClibTechnology {
  kClibTechCmos,
  kClibTechFpga
};


//////////////////////////////////////////////////////////////////////
/// @brief 遅延モデルを表す列挙型
//////////////////////////////////////////////////////////////////////
enum ClibDelayModel {
  kClibDelayGenericCmos,
  kClibDelayTableLookup,
  kClibDelayPiecewiseCmos,
  kClibDelayCmos2,
  kClibDelayDcm
};


//////////////////////////////////////////////////////////////////////
/// @brief ピンの方向を表す列挙型
//////////////////////////////////////////////////////////////////////
enum ClibCellPinDirection {
  kClibCellPinInput,
  kClibCellPinOutput,
  kClibCellPinInout,
  kClibCellPinInternal
};


//////////////////////////////////////////////////////////////////////
/// @brief タイミングの条件を表す列挙型
//////////////////////////////////////////////////////////////////////
enum ClibTimingSense {
  kClibPosiUnate = 1,
  kClibNegaUnate = 2,
  kClibNonUnate  = 3
};


/////////////////////////////////////////////////////////////////////
/// @brief タイミング情報の型を表す列挙型
//////////////////////////////////////////////////////////////////////
enum ClibTimingType {
  kClibTimingCombinational          = 0,
  kClibTimingCombinationalRise      = 1,
  kClibTimingCombinationalFall      = 2,

  kClibTimingThreeStateEnable       = 3,
  kClibTimingThreeStateDisable      = 4,
  kClibTimingThreeStateEnableRise   = 5,
  kClibTimingThreeStateEnableFall   = 6,
  kClibTimingThreeStateDisableRise  = 7,
  kClibTimingThreeStateDisableFall  = 8,

  kClibTimingRisingEdge             = 9,
  kClibTimingFallingEdge            = 10,

  kClibTimingPreset                 = 11,
  kClibTimingClear                  = 12,

  kClibTimingHoldRising             = 13,
  kClibTimingHoldFalling            = 14,

  kClibTimingSetupRising            = 15,
  kClibTimingSetupFalling           = 16,

  kClibTimingRecoveryRising         = 17,
  kClibTimingRecoveryFalling        = 18,

  kClibTimingSkewRising             = 19,
  kClibTimingSkewFalling            = 20,

  kClibTimingRemovalRising          = 21,
  kClibTimingRemovalFalling         = 22,

  kClibTimingNonSeqSetupRising      = 23,
  kClibTimingNonSeqSetupFalling     = 24,
  kClibTimingNonSeqHoldRising       = 25,
  kClibTimingNonSeqHoldFalling      = 26,

  kClibTimingNochangeHighHigh       = 27,
  kClibTimingNochangeHighLow        = 28,
  kClibTimingNochangeLowHigh        = 29,
  kClibTimingNochangeLowLow         = 30
};


//////////////////////////////////////////////////////////////////////
/// @brief ルックアップテーブルの変数の型
//////////////////////////////////////////////////////////////////////
enum ClibVarType {
  kClibVarInputNetTransition,

  kClibVarTotalOutputNetCapacitance,
  kClibVarOutputNetLength,
  kClibVarOutputNetWireCap,
  kClibVarOutputNetPinCap,

  kClibVarRelatedOutTotalOutputNetCapacitance,
  kClibVarRelatedOutOutputNetLength,
  kClibVarRelatedOutOutputNetWireCap,
  kClibVarRelatedOutOutputNetPinCap,

  kClibVarConstrainedPinTransition,

  kClibVarRelatedPinTransition,

  kClibVarNone
};


//////////////////////////////////////////////////////////////////////
/// @brief パタングラフのノードの型
//////////////////////////////////////////////////////////////////////
enum ClibPatType {
  kClibPatInput = 0,
  kClibPatAnd   = 2,
  kClibPatXor   = 3
};

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] delay_model 遅延モデル
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibDelayModel delay_model);

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] timing_sense タイミングセンス
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibTimingSense timing_sense);


/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] timing_type タイミング条件
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibTimingType timing_type);

/// @brief ストリーム出力演算子
/// @param[in] s 出力先のストリーム
/// @param[in] var_type 変数の型
/// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibVarType var_type);


END_NAMESPACE_YM

#endif // YM_CLIB_H
