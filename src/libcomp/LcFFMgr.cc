
/// @file LcFFMgr.cc
/// @brief LcFFMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcFFMgr.h"
#include "LcGroup.h"
#include "LcClass.h"
#include "LcSignature.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

BEGIN_NONAMESPACE

// has_q, has_xq, has_clear, has_preset をエンコードする．
inline
ymuint
encode(bool has_q,
       bool has_xq,
       bool has_clear,
       bool has_preset)
{
  ymuint ans = 0;
  if ( has_q ) {
    if ( has_xq ) {
      ans = 2;
    }
    else {
      ans = 0;
    }
  }
  else {
    ASSERT_COND( has_xq );
    ans = 1;
  }
  ans <<= 2;
  if ( has_clear ) {
    ans |= 1U;
  }
  if ( has_preset ) {
    ans |= 2U;
  }
  return ans;
}

// 整数から　has_q, has_xq, has_clear, has_preset をデコードする．
inline
void
decode(ymuint val,
       bool& has_q,
       bool& has_xq,
       bool& has_clear,
       bool& has_preset)
{
  ymuint val1 = val >> 2;
  switch ( val1 ) {
  case 0:
    has_q = true;
    has_xq = false;
    break;
  case 1:
    has_q = false;
    has_xq = true;
    break;
  case 2:
    has_q = true;
    has_xq = true;
    break;
  }
  has_clear = static_cast<bool>((val >> 0) & 1U);
  has_preset = static_cast<bool>((val >> 1) & 1U);
}

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラスLcFFMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] libcomp 親の LibComp
LcFFMgr::LcFFMgr(LibComp& libcomp) :
  LcGroupMgr(libcomp)
{
}

// @brief デストラクタ
LcFFMgr::~LcFFMgr()
{
}

// @brief 初期化する．
void
LcFFMgr::init()
{
  clear();

  for (ymuint i = 0; i < 12; ++ i) {
    bool has_q;
    bool has_xq;
    bool has_clear;
    bool has_preset;
    decode(i, has_q, has_xq, has_clear, has_preset);

    LcSignature sig(LcSignature::kFFType, has_q, has_xq, has_clear, has_preset);
    LcGroup* group = find_group(sig, false);
    LcClass* cclass = group->parent();
    mFFClass[i] = cclass->id();
  }
}

// @brief 定義済みのFFクラス番号を返す．
// @param[in] has_q Q端子の有無
// @param[in] has_xq 反転Q端子の有無
// @param[in] has_clear クリア端子の有無
// @param[in] has_preset プリセット端子の有無
//
// has_q == false && has_xq == false は不適
ymuint
LcFFMgr::ff_class(bool has_q,
		  bool has_xq,
		  bool has_clear,
		  bool has_preset)
{
  ymuint i = encode(has_q, has_xq, has_clear, has_preset);
  return mFFClass[i];
}

// @brief 代表関数を求める．
// @param[in] sig シグネチャ
// @param[out] rep_sig 代表シグネチャ
// @param[out] xmap 変換
void
LcFFMgr::find_rep(const LcSignature& sig,
		  LcSignature& rep_sig,
		  NpnMapM& xmap)
{
}

// @brief 同位体変換リストを求める．
// @param[in] sig シグネチャ
// @param[out] idmap_list 同位体変換のリスト
void
LcFFMgr::find_idmap_list(const LcSignature& sig,
			 vector<NpnMapM>& idmap_list)
{
}

END_NAMESPACE_YM_CLIB_LIBCOMP
