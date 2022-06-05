#ifndef CISEQINFO_H
#define CISEQINFO_H

/// @file CiSeqInfo.h
/// @brief CiSeqInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiSeqInfo CiSeqInfo.h "CiSeqInfo.h"
/// @brief シンプルなFF/Latch の種類を表すクラス
//////////////////////////////////////////////////////////////////////
class CiSeqInfo
{
public:

  /// @brief コンストラクタ
  CiSeqInfo(
    bool slave_clock = false,
    bool clear = false,
    bool preset = false,
    ClibCPV clear_preset_var1 = ClibCPV::X,
    ClibCPV clear_preset_var2 = ClibCPV::X
  ) : mSlaveClock{slave_clock},
      mClear{clear},
      mPreset{preset},
      mCpv1{clear_preset_var1},
      mCpv2{clear_preset_var2}
  {
  }

  /// @brief デストラクタ
  ~CiSeqInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief slave clock を持つ時 true を返す．
  bool
  has_slave_clock() const
  {
    return mSlaveClock;
  }

  /// @brief clear 端子を持つ時 true を返す．
  bool
  has_clear() const
  {
    return mClear;
  }

  /// @brief preset 端子を持つ時 true を返す．
  bool
  has_preset() const
  {
    return mPreset;
  }

  /// @brief clear/preset が同時に与えられたときの出力の値1
  ClibCPV
  clear_preset_var1() const
  {
    return mCpv1;
  }

  /// @brief clear/preset が同時に与えられたときの出力の値2
  ClibCPV
  clear_preset_var2() const
  {
    return mCpv2;
  }

  /// @brief エンコードしたインデックス値
  SizeType
  encode_val() const
  {
    SizeType index = 0;
    if ( has_slave_clock() ) {
      index += 1;
    }
    if ( has_clear() ) {
      index += 2;
    }
    if ( has_preset() ) {
      index += 4;
    }
    if ( index >= 6 ) {
      // clear/preset ありの場合
      index += encode_cpv(mCpv1) * 2;
      index += encode_cpv(mCpv2) * 10;
    }
    return index;
  }

  /// @brief インデックス値から値を作る．
  static
  CiSeqInfo
  decode_index(
    SizeType index
  )
  {
    if ( index < 6 ) {
      bool slave_clock = static_cast<bool>((index >> 0) & 1);
      bool clear = static_cast<bool>((index >> 1) & 1);
      bool preset = static_cast<bool>((index >> 2) & 1);
      auto cpv1 = ClibCPV::X;
      auto cpv2 = ClibCPV::X;
      return CiSeqInfo{slave_clock, clear, preset, cpv1, cpv2};
    }
    else {
      bool slave_clock = static_cast<bool>(index & 1);
      index -= 6;
      index /= 2;
      SizeType index1 = index % 5;
      auto cpv1 = decode_cpv(index1);
      SizeType index2 = index / 5;
      auto cpv2 = decode_cpv(index2);
      return CiSeqInfo{slave_clock, true, true, cpv1, cpv2};
    }
  }

  /// @brief インデックス値の総数を返す．
  static
  SizeType
  max_index()
  {
    return 56;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCPV をエンコードする．
  static
  SizeType
  encode_cpv(
    ClibCPV cpv
  )
  {
    switch ( cpv ) {
    case ClibCPV::L: return 0;
    case ClibCPV::H: return 1;
    case ClibCPV::N: return 2;
    case ClibCPV::T: return 3;
    case ClibCPV::X: return 4;
    }
    ASSERT_NOT_REACHED;
    return 0;
  }

  /// @brief 整数値から ClibCPv に変換する．
  static
  ClibCPV
  decode_cpv(
    SizeType index
  )
  {
    switch ( index ) {
    case 0: return ClibCPV::L;
    case 1: return ClibCPV::H;
    case 2: return ClibCPV::N;
    case 3: return ClibCPV::T;
    case 4: return ClibCPV::X;
    }
    ASSERT_NOT_REACHED;
    return ClibCPV::X;
  }

private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // slave clock の有無
  bool mSlaveClock;

  // clear 端子の有無
  bool mClear;

  // preset 端子の有無
  bool mPreset;

  // cpv1
  ClibCPV mCpv1;

  // pcv2
  ClibCPV mCpv2;

};

END_NAMESPACE_YM_CLIB

#endif // CISEQINFO_H
