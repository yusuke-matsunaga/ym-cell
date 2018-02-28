
/// @file ClibFFInfo.cc
/// @brief ClibFFInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibFFInfo.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// mBits には各要素に 5bit を割り当てる．
// 全部で 5 * 6 = 30bit
const int OUTPUT1 = 0;
const int OUTPUT2 = 1;
const int INPUT   = 2;
const int CLOCK   = 3;
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
int
get_sense(ymuint bits,
	  int idx)
{
  return (bits >> (5 * idx + 3)) & 3U;
}

inline
int
get_pos(ymuint bits,
	int idx)
{
  return (bits >> (5 * idx)) & 7U;
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス ClibFFInfo
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
// @note 内容は不定
ClibFFInfo::ClibFFInfo() :
  mBits(0U)
{
}

// @brief コンストラクタ
// @param[in] pos_array ピン位置と極性情報の配列
// @note pos_array の意味は以下の通り
//  - pos_array[0] : データ入力のピン番号     (3bit)
//  - pos_array[1] : クロック入力のピン番号   (3bit) | 極性情報 (1bit)
//  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
//  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
//  - pos_array[4] : 肯定出力のピン番号       (3bit)
//  - pos_array[5] : 否定出力のピン番号       (3bit) | あるかないか(1bit)
ClibFFInfo::ClibFFInfo(int pos_array[]) :
  mBits(0U)
{
  mBits |= encode(pos_array[0], INPUT);
  mBits |= encode(pos_array[1], CLOCK);
  mBits |= encode(pos_array[2], CLEAR);
  mBits |= encode(pos_array[3], PRESET);
  mBits |= encode(pos_array[4], OUTPUT1);
  mBits |= encode(pos_array[5], OUTPUT2);
}

// @brief デストラクタ
ClibFFInfo::~ClibFFInfo()
{
}

// @brief クロック入力のタイプを返す．
// @retval 1 positive edge
// @retval 2 negative edge
int
ClibFFInfo::clock_sense() const
{
  return get_sense(mBits, CLOCK);
}

// @brief クリア入力のタイプを返す．
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
int
ClibFFInfo::clear_sense() const
{
  return get_sense(mBits, CLEAR);
}

// @brief プリセット入力のタイプを返す．
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
int
ClibFFInfo::preset_sense() const
{
  return get_sense(mBits, PRESET);
}

// @brief 反転出力を持つタイプの時に true を返す．
bool
ClibFFInfo::has_xq() const
{
  return get_sense(mBits, OUTPUT2) != 0;
}

// @brief クリア入力を持つタイプの時に true を返す．
bool
ClibFFInfo::has_clear() const
{
  return clear_sense() != 0;
}

// @brief プリセット入力を持つタイプの時に true を返す．
bool
ClibFFInfo::has_preset() const
{
  return preset_sense() != 0;
}

// @brief データ入力のピン番号を返す．
int
ClibFFInfo::data_pos() const
{
  return get_pos(mBits, INPUT);
}

// @brief クロック入力のピン番号を返す．
int
ClibFFInfo::clock_pos() const
{
  return get_pos(mBits, CLOCK);
}

// @brief クリア入力のピン番号を返す．
// @note クリア入力がない場合の値は不定
int
ClibFFInfo::clear_pos() const
{
  return get_pos(mBits, CLEAR);
}

// @brief プリセット入力のピン番号を返す．
// @note プリセット入力がない場合の値は不定
int
ClibFFInfo::preset_pos() const
{
  return get_pos(mBits, PRESET);
}

// @brief 肯定出力のピン番号を返す．
int
ClibFFInfo::q_pos() const
{
  return get_pos(mBits, OUTPUT1);
}

// @brief 否定出力のピン番号を返す．
int
ClibFFInfo::xq_pos() const
{
  return get_pos(mBits, OUTPUT2);
}

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
// @param[in] ffinfo 対象の ClibFFInfo
// @return ストリームを返す．
ODO&
operator<<(ODO& bos,
	   const ClibFFInfo& ffinfo)
{
  return bos << ffinfo.mBits;
}

// @brief バイナリファイルを読み込む．
// @param[in] bis 入力元のストリーム
// @param[out] ffinfo 結果を格納する変数
// @return ストリームを返す．
IDO&
operator>>(IDO& bis,
	   ClibFFInfo& ffinfo)
{
  return bis >> ffinfo.mBits;
}

END_NAMESPACE_YM_CLIB
