﻿
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellClass.h"
#include "ym/ClibCellLibrary.h"
#include "ym/ClibCellGroup.h"
#include "ym/NpnMapM.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellClass::CiCellClass() :
  mIdmapNum(0),
  mIdmapList(nullptr),
  mGroupNum(0),
  mGroupList(nullptr)
{
}

// @brief デストラクタ
CiCellClass::~CiCellClass()
{
  // mIdmapList, mGroupList は ClibMgr が管理している．
}

// @brief ID番号を返す．
// @note ClibCellLibrary::npn_class(id) で返されるオブジェクトの id() は id となる．
ymuint
CiCellClass::id() const
{
  return mId;
}

// @brief 同位体変換の個数を得る．
// @note 恒等変換は含まない．
ymuint
CiCellClass::idmap_num() const
{
  return mIdmapNum;
}

// @brief 同位体変換を得る．
// @param[in] pos 位置番号 ( 0 <= pos < idmap_num() )
const NpnMapM&
CiCellClass::idmap(ymuint pos) const
{
  ASSERT_COND( pos < mIdmapNum );
  return mIdmapList[pos];
}

// @brief NPN同値類の数を返す．
ymuint
CiCellClass::group_num() const
{
  return mGroupNum;
}

// @brief ClibCellGroup を返す．
// @param[in] pos 位置番号 ( 0 <= pos < func_num() )
const ClibCellGroup*
CiCellClass::cell_group(ymuint pos) const
{
  ASSERT_COND( pos < mGroupNum );
  return mGroupList[pos];
}

// @brief 初期化する．
// @param[in] idmap_list 同位体変換リスト
// @param[in] group_list グループのリスト
// @param[in] alloc メモリアロケータ
void
CiCellClass::init(const vector<NpnMapM>& idmap_list,
		  const vector<const ClibCellGroup*>& group_list,
		  Alloc& alloc)
{
  mIdmapNum = idmap_list.size();
  mGroupNum = group_list.size();
  alloc_array(alloc);

  for (ymuint i = 0; i < mIdmapNum; ++ i) {
    mIdmapList[i] = idmap_list[i];
  }

  for (ymuint i = 0; i < mGroupNum; ++ i) {
    mGroupList[i] = group_list[i];
  }
}

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiCellClass::dump(ODO& bos) const
{
  bos << mIdmapNum
      << mGroupNum;

  // 同位体変換情報のダンプ
  for (ymuint i = 0; i < mIdmapNum; ++ i) {
    bos << mIdmapList[i];
  }

  // グループ情報のダンプ
  for (ymuint j = 0; j < mGroupNum; ++ j) {
    const ClibCellGroup* group = mGroupList[j];
    ymuint group_id = group->id();
    bos << group_id;
  }
}

// @brief バイナリファイルを読み込む．
// @param[in] bis 入力元のストリーム
// @param[in] library セルライブラリ
// @param[in] alloc メモリアロケータ
void
CiCellClass::restore(IDO& bis,
		     const ClibCellLibrary& library,
		     Alloc& alloc)
{
  bis >> mIdmapNum
      >> mGroupNum;
  alloc_array(alloc);

  // 同位体変換情報の設定
  for (ymuint i = 0; i < mIdmapNum; ++ i) {
    bis >> mIdmapList[i];
  }

  // グループ情報の設定
  for (ymuint i = 0; i < mGroupNum; ++ i) {
    ymuint group_id;
    bis >> group_id;
    const ClibCellGroup* group = library.group(group_id);
    mGroupList[i] = group;
  }
}

// @brief 配列領域の確保を行う．
// @param[in] alloc メモリアロケータ
// @note mIdmapNum, mGroupNum が適切に設定されている必要がある．
void
CiCellClass::alloc_array(Alloc& alloc)
{
  if ( mIdmapNum > 0 ) {
    void* p = alloc.get_memory(sizeof(NpnMapM) * mIdmapNum);
    mIdmapList = new (p) NpnMapM[mIdmapNum];
  }
  else {
    mIdmapList = nullptr;
  }

  if ( mGroupNum > 0 ) {
    void* p = alloc.get_memory(sizeof(const ClibCellGroup*) * mGroupNum);
    mGroupList = new (p) const ClibCellGroup*[mGroupNum];
  }
  else {
    mGroupList = nullptr;
  }
}

END_NAMESPACE_YM_CLIB
