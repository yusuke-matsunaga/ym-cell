
/// @file CgSignature.cc
/// @brief CgSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "cgmgr/CgSignature.h"
#include "ym/ClibIOMap.h"
#include "ym/Expr.h"
#include "CgSigRep.h"


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
  // CgSigRep の定義をヘッダファイルから隠すために
  // ヘッダでは定義できない．
}

// @brief 1出力論理関数用のシグネチャを作る．
CgSignature
CgSignature::make_logic_sig(
  SizeType ni,
  const Expr& expr
)
{
  string prefix{"C"};
  SizeType no = 1;
  SizeType nb = 0;
  auto func = expr.make_tv(ni);
  auto rep = new CgSigRep{prefix, ni, no, nb, {func}, {TvFunc::make_invalid()}, expr};
  return CgSignature{unique_ptr<CgSigRep>{rep}};
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
  string prefix{"C"};
  auto rep = new CgSigRep{prefix, ni, no, nb, func_list, tristate_list};
  return CgSignature{unique_ptr<CgSigRep>{rep}};
}

BEGIN_NONAMESPACE

// clear_preset_var1/var2 の値をエンコードする．
inline
string
encode_cpv(
  ClibCPV clear_preset_var
)
{
  switch ( clear_preset_var ) {
  case ClibCPV::L: return "L";
  case ClibCPV::H: return "H";
  case ClibCPV::N: return "N";
  case ClibCPV::T: return "T";
  case ClibCPV::X: return "X";
  }
  return string{};
}

END_NONAMESPACE

// @brief FF用のシグネチャを作る．
CgSignature
CgSignature::make_ff_sig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const TvFunc& clocked_on,
  const TvFunc& clocked_on_also,
  const TvFunc& next_state,
  const TvFunc& clear,
  const TvFunc& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;
  SizeType ni3 = ni2 + 2;
  SizeType no3 = no2 + 5;
  vector<TvFunc> sig_func_list(no3, TvFunc::make_invalid());
  vector<TvFunc> sig_tristate_list(no3, TvFunc::make_invalid());
  for ( SizeType i = 0; i < no2; ++ i ) {
    sig_func_list[i] = func_list[i];
    sig_tristate_list[i] = tristate_list[i];
  }
  sig_func_list[no2 + 0] = clocked_on;
  sig_func_list[no2 + 1] = clocked_on_also;
  sig_func_list[no2 + 2] = next_state;
  sig_func_list[no2 + 3] = clear;
  sig_func_list[no2 + 4] = preset;
  auto prefix = string{"F"} + encode_cpv(clear_preset_var1) + encode_cpv(clear_preset_var2);
  auto rep = new CgSigRep{prefix, ni, no, nb, sig_func_list, sig_tristate_list};
  return CgSignature{unique_ptr<CgSigRep>{rep}};
}

// @brief ラッチ用のシグネチャを作る．
CgSignature
CgSignature::make_latch_sig(
  SizeType ni,
  SizeType no,
  SizeType nb,
  const vector<TvFunc>& func_list,
  const vector<TvFunc>& tristate_list,
  const TvFunc& enable_on,
  const TvFunc& enable_on_also,
  const TvFunc& data_in,
  const TvFunc& clear,
  const TvFunc& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  SizeType ni2 = ni + nb;
  SizeType no2 = no + nb;
  SizeType ni3 = ni2 + 2;
  SizeType no3 = no2 + 5;
  vector<TvFunc> sig_func_list(no3, TvFunc::make_invalid());
  vector<TvFunc> sig_tristate_list(no3, TvFunc::make_invalid());
  for ( SizeType i = 0; i < no2; ++ i ) {
    sig_func_list[i] = func_list[i];
    sig_tristate_list[i] = tristate_list[i];
  }
  sig_func_list[no2 + 0] = enable_on;
  sig_func_list[no2 + 1] = enable_on_also;
  sig_func_list[no2 + 2] = data_in;
  sig_func_list[no2 + 3] = clear;
  sig_func_list[no2 + 4] = preset;
  auto prefix = string{"L"} + encode_cpv(clear_preset_var1) + encode_cpv(clear_preset_var2);
  auto rep = new CgSigRep{prefix, ni, no, nb, sig_func_list, sig_tristate_list};
  return CgSignature{unique_ptr<CgSigRep>{rep}};
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

// @brief 単一の論理式を持つ時その式を返す．
Expr
CgSignature::expr() const
{
  if ( is_valid() ) {
    return mRepPtr->expr();
  }
  else {
    return Expr::make_invalid();
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
