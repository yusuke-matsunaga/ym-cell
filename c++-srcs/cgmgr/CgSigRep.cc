
/// @file CgSigRep.cc
/// @brief CgSigRep の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief 関数の内容を文字列に変換する．
string
CgSigRep::hex_str(
  const TvFunc& func
)
{
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
  const ClibIOMap& iomap
)
{
  ASSERT_COND( iomap.output_num() == 1 );
  ASSERT_COND( iomap.inout_num() == 0 );
  SizeType ni = iomap.input_num();
  NpnMap npnmap(ni);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto ipinmap = iomap.input_map(i);
    npnmap.set(VarId{i}, VarId{ipinmap.id()}, ipinmap.inv());
  }
  npnmap.set_oinv(iomap.output_map(0).inv());
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
  return ClibIOMap{input_map, ClibPinMap{0, npnmap.oinv()}};
}

END_NAMESPACE_YM_CLIB
