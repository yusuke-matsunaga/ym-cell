
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "CiCellGroup.h"

#include "ym/ClibCellLibrary.h"
#include "ym/ClibCellClass.h"
#include "ym/ClibCell.h"
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
CiCellGroup::CiCellGroup() :
  mRepClass(nullptr),
  mPinInfo(0U),
  mClibNum(0),
  mClibList(nullptr)
{
}

// @brief デストラクタ
CiCellGroup::~CiCellGroup()
{
  // mClibList は ClibMgr が管理する．
}

// @brief ID番号を返す．
// @note ClibCellLibrary::group(id) で返されるオブジェクトの id() は id となる．
ymuint
CiCellGroup::id() const
{
  return mId;
}

// @brief 代表クラスを返す．
const ClibCellClass*
CiCellGroup::rep_class() const
{
  return mRepClass;
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
  ymuint pos_array[6];
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
  ymuint pos_array[6];
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
ymuint
CiCellGroup::data_pos() const
{
  return get_pos(mPinInfo, INPUT);
}

// @brief クロック入力のタイプを返す．
// @retval 0 該当しない
// @retval 1 positive edge
// @retval 2 negative edge
ymuint
CiCellGroup::clock_sense() const
{
  return get_sense(mPinInfo, CLOCK);
}

// @brief クロック入力のピン番号を返す．
ymuint
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
ymuint
CiCellGroup::enable_sense() const
{
  return get_sense(mPinInfo, ENABLE);
}

// @brief イネーブル入力のピン番号を返す．
ymuint
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
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
ymuint
CiCellGroup::clear_sense() const
{
  return get_sense(mPinInfo, CLEAR);
}

// @brief クリア入力のピン番号を返す．
// @note クリア入力がない場合の値は不定
ymuint
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
// @retval 0 なし
// @retval 1 High sensitive
// @retval 2 Low sensitive
ymuint
CiCellGroup::preset_sense() const
{
  return get_sense(mPinInfo, PRESET);
}

// @brief プリセット入力のピン番号を返す．
// @note プリセット入力がない場合の値は不定
ymuint
CiCellGroup::preset_pos() const
{
  return get_pos(mPinInfo, PRESET);
}

// @brief 肯定出力のピン番号を返す．
ymuint
CiCellGroup::q_pos() const
{
  return get_pos(mPinInfo, OUTPUT1);
}

// @brief 否定出力のピン番号を返す．
ymuint
CiCellGroup::xq_pos() const
{
  return get_pos(mPinInfo, OUTPUT2);
}

// @brief セル数を返す．
ymuint
CiCellGroup::cell_num() const
{
  return mClibNum;
}

// @brief セルを返す．
// @param[in] pos 位置番号 ( 0 <= pos < cell_num() )
const ClibCell*
CiCellGroup::cell(ymuint pos) const
{
  ASSERT_COND( pos < mClibNum );
  return mClibList[pos];
}

// @brief 初期化する．
// @param[in] cell_class 代表クラス
// @param[in] map 変換マップ
// @param[in] cell_list セルのリスト
// @param[in] alloc メモリアロケータ
void
CiCellGroup::init(const ClibCellClass* cell_class,
		  const NpnMapM& map,
		  const vector<ClibCell*>& cell_list,
		  Alloc& alloc)
{
  mRepClass = cell_class;
  mMap = map;
  mClibNum = cell_list.size();

  alloc_array(alloc);
  for (ymuint i = 0; i < mClibNum; ++ i) {
    ClibCell* cell = cell_list[i];
    mClibList[i] = cell;
    cell->set_group(this);
  }
}

// @brief FFのピン情報を設定する．
// @param[in] pos_array ピン位置と極性情報の配列
// @note pos_array の意味は以下の通り
//  - pos_array[0] : データ入力のピン番号     (3bit)
//  - pos_array[1] : クロック入力のピン番号   (3bit) | 極性情報 (1bit)
//  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
//  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
//  - pos_array[4] : 肯定出力のピン番号       (3bit)
//  - pos_array[5] : 否定出力のピン番号       (3bit) | あるかないか (1bit)
void
CiCellGroup::set_ff_info(ymuint pos_array[])
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
// @param[in] pos_array ピン位置と極性情報の配列
// @note pos_array の意味は以下の通り
//  - pos_array[0] : データ入力のピン番号     (3bit)
//  - pos_array[1] : イネーブル入力のピン番号 (3bit) | 極性情報 (2bit)
//  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
//  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
//  - pos_array[4] : 肯定出力のピン番号       (3bit)
//  - pos_array[5] : 否定出力のピン番号       (3bit)
void
CiCellGroup::set_latch_info(ymuint pos_array[])
{
  mPinInfo = 0U;
  mPinInfo |= encode(pos_array[0], INPUT);
  mPinInfo |= encode(pos_array[1], ENABLE);
  mPinInfo |= encode(pos_array[2], CLEAR);
  mPinInfo |= encode(pos_array[3], PRESET);
  mPinInfo |= encode(pos_array[4], OUTPUT1);
}

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiCellGroup::dump(ODO& bos) const
{
  ymuint parent_id = mRepClass->id();
  bos << parent_id
      << mMap
      << mPinInfo
      << mClibNum;
  for (ymuint i = 0; i < mClibNum; ++ i) {
    ymuint cell_id = mClibList[i]->id();
    bos << cell_id;
  }
}

// @brief バイナリファイルを読み込む．
// @param[in] bis 入力元のストリーム
// @param[in] library セルライブラリ
// @param[in] alloc メモリアロケータ
void
CiCellGroup::restore(IDO& bis,
		     ClibCellLibrary& library,
		     Alloc& alloc)
{
  ymuint parent_id;
  bis >> parent_id
      >> mMap
      >> mPinInfo
      >> mClibNum;
  mRepClass = library.npn_class(parent_id);

  alloc_array(alloc);
  for (ymuint i = 0; i < mClibNum; ++ i) {
    ymuint cell_id;
    bis >> cell_id;
    ClibCell* cell = library.cell(cell_id);
    mClibList[i] = cell;
    cell->set_group(this);
  }
}

// @brief メモリ領域の確保を行う．
// @param[in] alloc メモリアロケータ
void
CiCellGroup::alloc_array(Alloc& alloc)
{
  if ( mClibNum > 0 ) {
    void* p = alloc.get_memory(sizeof(const ClibCell*) * mClibNum);
    mClibList = new (p) const ClibCell*[mClibNum];
  }
  else {
    mClibList = nullptr;
  }
}

END_NAMESPACE_YM_CLIB
