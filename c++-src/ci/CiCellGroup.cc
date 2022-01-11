
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiCell.h"
#include "ci/CiCellClass.h"

#include "ym/ClibFFInfo.h"
#include "ym/ClibLatchInfo.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

const int OUTPUT1 = 0;
const int OUTPUT2 = 1;
const int INPUT   = 2;
const int CLOCK   = 3;
const int ENABLE  = 3;
const int CLEAR   = 4;
const int PRESET  = 5;

inline
ymuint
encode(
  ymuint val,
  int idx
)
{
  return val << (5 * idx);
}

inline
ymuint
get_sense(
  ymuint bits,
  int idx
)
{
  return (bits >> (5 * idx + 3)) & 3U;
}

inline
ymuint
get_pos(
  ymuint bits,
  int idx
)
{
  return (bits >> (5 * idx)) & 7U;
}

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellGroup::CiCellGroup(
  SizeType id,
  const NpnMapM& map,
  int pininfo,
  const vector<CiCell*>& cell_list
) : mId{id},
    mMap{map},
    mPinInfo{pininfo},
    mCellList{cell_list}
{
}

// @brief ID番号を返す．
SizeType
CiCellGroup::id() const
{
  return mId;
}

// @brief 代表クラスに対する変換マップを返す．
const NpnMapM&
CiCellGroup::map() const
{
  return mMap;
}

// @brief 反転出力を持つ時 true を返す．
bool
CiCellGroup::has_xq() const
{
  return get_sense(mPinInfo, OUTPUT2) != 0;
}

// @brief データ入力を持つとき true を返す．
bool
CiCellGroup::has_data() const
{
  return get_sense(mPinInfo, INPUT) != 0;
}

// @brief データ入力のピン番号を返す．
SizeType
CiCellGroup::data_pos() const
{
  return get_pos(mPinInfo, INPUT);
}

// @brief クリア入力を持つタイプの時に true を返す．
bool
CiCellGroup::has_clear() const
{
  //return clear_sense() != 0;
}

// @brief プリセット入力を持つタイプの時に true を返す．
bool
CiCellGroup::has_preset() const
{
  //return preset_sense() != 0;
}

// @brief セル数を返す．
SizeType
CiCellGroup::cell_num() const
{
  return mCellList.size();
}

// @brief セルを返す．
const ClibCell&
CiCellGroup::cell(
  SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
) const
{
  ASSERT_COND( 0 <= pos && pos < cell_num() );
  return *mCellList[pos];
}

// @brief FFのピン情報を設定する．
void
CiCellGroup::set_ff_info(
  SizeType pos_array[]
)
{
  mPinInfo = 0U;
  mPinInfo |= encode(pos_array[0], INPUT);
  mPinInfo |= encode(pos_array[1], CLOCK);
  mPinInfo |= encode(pos_array[2], CLEAR);
  mPinInfo |= encode(pos_array[3], PRESET);
  mPinInfo |= encode(pos_array[4], OUTPUT1);
  mPinInfo |= encode(pos_array[5], OUTPUT2);
}

// @brief ラッチのピン情報を設定する．
void
CiCellGroup::set_latch_info(
  SizeType pos_array[]
)
{
  mPinInfo = 0U;
  mPinInfo |= encode(pos_array[0], INPUT);
  mPinInfo |= encode(pos_array[1], ENABLE);
  mPinInfo |= encode(pos_array[2], CLEAR);
  mPinInfo |= encode(pos_array[3], PRESET);
  mPinInfo |= encode(pos_array[4], OUTPUT1);
  mPinInfo |= encode(pos_array[5], OUTPUT2);
}

END_NAMESPACE_YM_CLIB
