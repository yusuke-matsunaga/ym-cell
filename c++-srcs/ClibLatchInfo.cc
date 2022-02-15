
/// @file ClibLatchInfo.cc
/// @brief ClibLatchInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibLatchInfo.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

const int OUTPUT1 = 0;
const int OUTPUT2 = 1;
const int INPUT   = 2;
const int ENABLE  = 3;
const int CLEAR   = 4;
const int PRESET  = 5;

inline
ymuint32
encode(
  ymuint32 val,
  int idx
)
{
  return val << (5 * idx);
}

inline
int
get_sense(
  ymuint32 bits,
  int idx
)
{
  return (bits >> (5 * idx + 3)) & 3U;
}

inline
int
get_pos(
  ymuint32 bits,
  int idx
)
{
  return (bits >> (5 * idx)) & 7U;
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス ClibLatchInfo
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
ClibLatchInfo::ClibLatchInfo(
  int pos_array[]
)
{
  mBits |= encode(pos_array[0], INPUT);
  mBits |= encode(pos_array[1], ENABLE);
  mBits |= encode(pos_array[2], CLEAR);
  mBits |= encode(pos_array[3], PRESET);
  mBits |= encode(pos_array[4], OUTPUT1);
  mBits |= encode(pos_array[5], OUTPUT2);
}

// @brief イネーブル入力のタイプを返す．
// @retval 0 なし
// @retval 1 positive edge
// @retval 2 negative edge
int
ClibLatchInfo::enable_sense() const
{
  return get_sense(mBits, ENABLE);
}

// @brief クリア入力のタイプを返す．
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
int
ClibLatchInfo::clear_sense() const
{
  return get_sense(mBits, CLEAR);
}

// @brief プリセット入力のタイプを返す．
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
int
ClibLatchInfo::preset_sense() const
{
  return get_sense(mBits, PRESET);
}

// @brief 反転出力を持つタイプの時に true を返す．
bool
ClibLatchInfo::has_xq() const
{
  return get_sense(mBits, OUTPUT2) != 0;
}

// @brief データ入力を持つとき true を返す．
bool
ClibLatchInfo::has_data() const
{
  return get_sense(mBits, INPUT) != 0;
}

// @brief イネーブル入力を持つとき true を返す．
bool
ClibLatchInfo::has_enable() const
{
  return enable_sense() != 0;
}

// @brief クリア入力を持つタイプの時に true を返す．
bool
ClibLatchInfo::has_clear() const
{
  return clear_sense() != 0;
}

// @brief プリセット入力を持つタイプの時に true を返す．
bool
ClibLatchInfo::has_preset() const
{
  return preset_sense() != 0;
}

// @brief データ入力のピン番号を返す．
int
ClibLatchInfo::data_pos() const
{
  return get_pos(mBits, INPUT);
}

// @brief クロック入力のピン番号を返す．
int
ClibLatchInfo::enable_pos() const
{
  return get_pos(mBits, ENABLE);
}

// @brief クリア入力のピン番号を返す．
// @note クリア入力がない場合の値は不定
int
ClibLatchInfo::clear_pos() const
{
  return get_pos(mBits, CLEAR);
}

// @brief プリセット入力のピン番号を返す．
// @note プリセット入力がない場合の値は不定
int
ClibLatchInfo::preset_pos() const
{
  return get_pos(mBits, PRESET);
}

// @brief 肯定出力のピン番号を返す．
int
ClibLatchInfo::q_pos() const
{
  return get_pos(mBits, OUTPUT1);
}

// @brief 否定出力のピン番号を返す．
int
ClibLatchInfo::xq_pos() const
{
  return get_pos(mBits, OUTPUT2);
}

// @brief バイナリダンプを行う．
// @param[in] s 出力先のストリーム
void
ClibLatchInfo::dump(ostream& s) const
{
  s.write(reinterpret_cast<const char*>(&mBits), sizeof(mBits));
}

// @brief バイナリファイルを読み込む．
// @param[in] s 入力元のストリーム
void
ClibLatchInfo::restore(istream& s)
{
  s.read(reinterpret_cast<char*>(&mBits), sizeof(mBits));
}

END_NAMESPACE_YM_CLIB
