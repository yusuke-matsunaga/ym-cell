
/// @file CgSigRep.cc
/// @brief CgSigRep の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgSigRep::rep_map() const
{
  auto map_list = gen_cannonical_map();
  return map_list.front();
}

// @brief 同位体変換のリストを求める．
vector<ClibIOMap>
CgSigRep::idmap_list() const
{
  auto map_list = gen_cannonical_map();
  vector<ClibIOMap> ans_list;
  const auto& map0 = map_list.front();
  auto invmap = map0.inverse();
  for ( const auto& map: map_list ) {
    ans_list.push_back(map * invmap);
  }
  return ans_list;
}

// @brief 関数の内容を文字列に変換する．
string
CgSigRep::hex_str(
  const TvFunc& func
)
{
  if ( func.is_invalid() ) {
    return string{};
  }
  SizeType ni = func.input_num();
  SizeType nexp = 1U << ni;
  ymuint8 val = 0U;
  ostringstream buf;
  for ( SizeType i = 0; i < nexp; ++ i ) {
    val <<= 1;
    if ( func.value(i) ) {
      val |= 1U;
    }
    if ( (i % 4) == 3 ) {
      buf << to_hex(val);
      val = 0U;
    }
  }
  if ( nexp <= 3 ) {
    buf << to_hex(val);
  }
  return buf.str();
}

// ClibIOMap から NpnMap を作る．
NpnMap
CgSigRep::to_npnmap(
  const ClibIOMap& iomap,
  SizeType opos
)
{
  SizeType ni = iomap.input_num();
  SizeType no = iomap.output_num();
  SizeType nb = iomap.inout_num();
  SizeType ni2 = ni + nb;
  NpnMap npnmap(ni2);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto ipinmap = iomap.input_map(i);
    npnmap.set(VarId{i}, VarId{ipinmap.id()}, ipinmap.inv());
  }
  for ( SizeType i = 0; i < nb; ++ i ) {
    auto bpinmap = iomap.inout_map(i);
    npnmap.set(VarId{i + ni}, VarId{bpinmap.id() + ni}, bpinmap.inv());
  }
  if ( opos < no ) {
    npnmap.set_oinv(iomap.output_map(opos).inv());
  }
  return npnmap;
}

// NpnMap から ClibIOMap を作る．
ClibIOMap
CgSigRep::from_npnmap(
  const NpnMap& npnmap
)
{
  SizeType ni = npnmap.input_num();
  vector<ClibPinMap> input_map(ni);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto v = npnmap.imap(VarId{i});
    input_map[i] = ClibPinMap{static_cast<SizeType>(v.var().val()), v.inv()};
  }
  return ClibIOMap{input_map, npnmap.oinv()};
}

END_NAMESPACE_YM_CLIB
