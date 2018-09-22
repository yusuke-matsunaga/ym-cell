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
class ClibTimingList;
class ClibLutTemplate;
class ClibLutTemplateList;
class ClibLut;

class ClibReader;
class ClibMislibReader;
class ClibDotlibReader;

class ClibDumper;
class ClibRestorer;

class ClibCellGroup;
class ClibCellGroupList;
class ClibCellClass;
class ClibCellClassList;
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
enum class ClibTechnology
  {
   cmos,
   fpga
  };


//////////////////////////////////////////////////////////////////////
/// @brief 遅延モデルを表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibDelayModel
  {
   GenericCmos,
   TableLookup,
   PiecewiseCmos,
   Cmos2,
   Dcm
  };


//////////////////////////////////////////////////////////////////////
/// @brief ピンの方向を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibDirection
  {
   Input,
   Output,
   Inout,
   Internal
  };


//////////////////////////////////////////////////////////////////////
/// @brief タイミングの条件を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibTimingSense
  {
   PosiUnate = 1,
   NegaUnate = 2,
   NonUnate  = 3
  };


/////////////////////////////////////////////////////////////////////
/// @brief タイミング情報の型を表す列挙型
//////////////////////////////////////////////////////////////////////
enum class ClibTimingType
  {
   Combinational          = 0,
   CombinationalRise      = 1,
   CombinationalFall      = 2,

   ThreeStateEnable       = 3,
   ThreeStateDisable      = 4,
   ThreeStateEnableRise   = 5,
   ThreeStateEnableFall   = 6,
   ThreeStateDisableRise  = 7,
   ThreeStateDisableFall  = 8,

   RisingEdge             = 9,
   FallingEdge            = 10,

   Preset                 = 11,
   Clear                  = 12,

   HoldRising             = 13,
   HoldFalling            = 14,

   SetupRising            = 15,
   SetupFalling           = 16,

   RecoveryRising         = 17,
   RecoveryFalling        = 18,

   SkewRising             = 19,
   SkewFalling            = 20,

   RemovalRising          = 21,
   RemovalFalling         = 22,

   NonSeqSetupRising      = 23,
   NonSeqSetupFalling     = 24,
   NonSeqHoldRising       = 25,
   NonSeqHoldFalling      = 26,

   NochangeHighHigh       = 27,
   NochangeHighLow        = 28,
   NochangeLowHigh        = 29,
   NochangeLowLow         = 30
  };


//////////////////////////////////////////////////////////////////////
/// @brief ルックアップテーブルの変数の型
//////////////////////////////////////////////////////////////////////
enum class ClibVarType
  {
   InputNetTransition,

   TotalOutputNetCapacitance,
   OutputNetLength,
   OutputNetWireCap,
   OutputNetPinCap,

   EqualOrOppositeOutputNetCapacitance,
   InputTransitionTime,

   RelatedOutTotalOutputNetCapacitance,
   RelatedOutOutputNetLength,
   RelatedOutOutputNetWireCap,
   RelatedOutOutputNetPinCap,

   ConstrainedPinTransition,

   RelatedPinTransition,

   None
  };


//////////////////////////////////////////////////////////////////////
/// @brief パタングラフのノードの型
//////////////////////////////////////////////////////////////////////
enum class ClibPatType
  {
   Input = 0,
   And   = 2,
   Xor   = 3
  };


//////////////////////////////////////////////////////////////////////
// ストリーム出力演算子
//////////////////////////////////////////////////////////////////////

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
