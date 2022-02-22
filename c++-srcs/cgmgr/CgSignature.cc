
/// @file CgSignature.cc
/// @brief CgSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "cgmgr/CgSignature.h"
#include "ym/ClibIOMap.h"
#include "CgSigRep.h"
#include "CgLogicSig.h"
#include "CgTriLogicSig.h"
#include "CgGenLogicSig.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CgSignature
//
// 基本的にはただ CgSigRep の同名の関数を呼んでいるだけなのだが，
// CgSigRep.h が必要なのでヘッダファイル中では定義できない．
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
CgSignature::CgSignature()
{
}

// @brief コンストラクタ
CgSignature::CgSignature(
  unique_ptr<const CgSigRep>&& ptr
) : mRepPtr{std::move(ptr)}
{
}

// @brief ムーブコンストラクタ
CgSignature::CgSignature(
  CgSignature&& src
) : mRepPtr{std::move(src.mRepPtr)}
{
}

// @brief ムーブ代入演算子
CgSignature&
CgSignature::operator=(
  CgSignature&& src
)
{
  if ( this != &src ) {
    mRepPtr.swap(src.mRepPtr);
  }
  return *this;
}

// @brief デストラクタ
CgSignature::~CgSignature()
{
}

// @brief 1出力論理関数用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  const TvFunc& func
)
{
  return CgSignature{CgLogicSig::make_signature(func)};
}

// @brief 1出力tristate関数用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  const TvFunc& func,
  const TvFunc& tristate
)
{
  return CgSignature{CgTriLogicSig::make_signature(func, tristate)};
}

// @brief 一般的な組み合わせ回路用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list
)
{
  return CgSignature{CgGenLogicSig::make_signature(ni, no, nb, func_list, tristate_list)};
}

// @brief シグネチャ文字列を返す．
string
CgSignature::str() const
{
  if ( is_valid() ) {
    return mRepPtr->str();
  }
  else {
    return string{};
  }
}

// @brief 変換を施したシグネチャを返す．
CgSignature
CgSignature::xform(
  const ClibIOMap& iomap ///< [in] 変換マップ
) const
{
  CgSignature ans;
  if ( is_valid() ) {
    auto tmp_ptr = mRepPtr->xform(iomap);
    ans.mRepPtr.swap(tmp_ptr);
  }
  return ans;
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgSignature::rep_map() const
{
  if ( is_valid() ) {
    return mRepPtr->rep_map();
  }
  else {
    return ClibIOMap{};
  }
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgSignature::idmap_list() const
{
  if ( is_valid() ) {
    return mRepPtr->idmap_list();
  }
  else {
    return vector<ClibIOMap>{};
  }
}

END_NAMESPACE_YM_CLIB
