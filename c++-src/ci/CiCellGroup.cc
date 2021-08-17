
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
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
encode(ymuint val,
       int idx)
{
  return val << (5 * idx);
}

inline
ymuint
get_sense(ymuint bits,
	  int idx)
{
  return (bits >> (5 * idx + 3)) & 3U;
}

inline
ymuint
get_pos(ymuint bits,
	int idx)
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

// @brief FFセルの場合のピン情報を返す．
// @note FFセル以外の場合には返り値は不定
ClibFFInfo
CiCellGroup::ff_info() const
{
  // 本当はバイナリレベルでコピーすればOKだけど
  // キレイにコピーする．
  int pos_array[6];
  pos_array[0] = data_pos();
  pos_array[1] = clock_pos() | (clock_sense() << 3);
  pos_array[2] = clear_pos() | (clear_sense() << 3);
  pos_array[3] = preset_pos() | (preset_sense() << 3);
  pos_array[4] = q_pos();
  pos_array[5] = xq_pos() | (static_cast<ymuint>(has_xq()) << 3);
  return ClibFFInfo(pos_array);
}

// @brief ラッチセルの場合のピン情報を返す．
// @note ラッチセル以外の場合には返り値は不定
ClibLatchInfo
CiCellGroup::latch_info() const
{
  // 本当はバイナリレベルでコピーすればOKだけど
  // キレイにコピーする．
  int pos_array[6];
  if ( has_data() ) {
    pos_array[0] = data_pos() | 8U;
  }
  else {
    pos_array[0] = 0;
  }
  pos_array[1] = enable_pos() | (enable_sense() << 3);
  pos_array[2] = clear_pos() | (clear_sense() << 3);
  pos_array[3] = preset_pos() | (preset_sense() << 3);
  pos_array[4] = q_pos();
  return ClibLatchInfo(pos_array);
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

// @brief クロック入力のタイプを返す．
// @retval 0 該当しない
// @retval 1 positive edge
// @retval 2 negative edge
int
CiCellGroup::clock_sense() const
{
  return get_sense(mPinInfo, CLOCK);
}

// @brief クロック入力のピン番号を返す．
SizeType
CiCellGroup::clock_pos() const
{
  return get_pos(mPinInfo, CLOCK);
}

// @brief イネーブル入力を持つとき true を返す．
bool
CiCellGroup::has_enable() const
{
  return enable_sense() != 0;
}

// @brief イネーブル入力のタイプを返す．
// @retval 0 なし
// @retval 1 positive edge
// @retval 2 negative edge
int
CiCellGroup::enable_sense() const
{
  return get_sense(mPinInfo, ENABLE);
}

// @brief イネーブル入力のピン番号を返す．
SizeType
CiCellGroup::enable_pos() const
{
  return get_pos(mPinInfo, ENABLE);
}

// @brief クリア入力を持つタイプの時に true を返す．
bool
CiCellGroup::has_clear() const
{
  return clear_sense() != 0;
}

// @brief クリア入力のタイプを返す．
int
CiCellGroup::clear_sense() const
{
  return get_sense(mPinInfo, CLEAR);
}

// @brief クリア入力のピン番号を返す．
SizeType
CiCellGroup::clear_pos() const
{
  return get_pos(mPinInfo, CLEAR);
}

// @brief プリセット入力を持つタイプの時に true を返す．
bool
CiCellGroup::has_preset() const
{
  return preset_sense() != 0;
}

// @brief プリセット入力のタイプを返す．
int
CiCellGroup::preset_sense() const
{
  return get_sense(mPinInfo, PRESET);
}

// @brief プリセット入力のピン番号を返す．
SizeType
CiCellGroup::preset_pos() const
{
  return get_pos(mPinInfo, PRESET);
}

// @brief 肯定出力のピン番号を返す．
SizeType
CiCellGroup::q_pos() const
{
  return get_pos(mPinInfo, OUTPUT1);
}

// @brief 否定出力のピン番号を返す．
SizeType
CiCellGroup::xq_pos() const
{
  return get_pos(mPinInfo, OUTPUT2);
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
