
/// @file CgSingleLogicSig.cc
/// @brief CgSingleLogicSig の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgLogicSig.h"
#include "ym/ClibIOMap.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// 16進数を表す文字を作る．
char
to_hex(
  ymuint8 val
)
{
  if ( val < 10 ) {
    return '0' + val;
  }
  else {
    return 'A' + (val - 10);
  }
}

// 1出力関数用のシグネチャを作る．
string
make_signature(
  const TvFunc& func // 論理関数
)
{
  SizeType ni = func.input_num();
  SizeType nexp = 1U << ni;
  ostringstream buf;
  buf << "C:" << ni << ":1:0:";
  ymuint8 val = 0U;
  for ( SizeType i = 0; i < nexp; ++ i ) {
    val <<= 1;
    if ( func.value(i) ) {
      val |= 1U;
    }
    if ( (i % 8) == 7 ) {
      buf << to_hex(val);
      val = 0U;
    }
  }
  return buf.str();
}

// ClibIOMap から NpnMap を作る．
NpnMap
to_npnmap(
  const ClibIOMap& iomap
)
{
  ASSERT_COND( iomap.output_num() == 1 );
  ASSERT_COND( iomap.inout_num() == 0 );
  SizeType ni = iomap.input_num();
  NpnMap npnmap(ni);
  return npnmap;
}

// NpnMap から ClibIOMap を作る．
ClibIOMap
from_npnmap(
  const NpnMap& npnmap
)
{
  SizeType ni = npnmap.input_num();
  vector<ClibPinMap> input_map(ni);
  for ( SizeType i = 0; i < ni; ++ i ) {
    auto v = npnmap.imap(VarId{i});
    input_map[i] = ClibPinMap{static_cast<SizeType>(v.var().val()), v.inv()};
  }
  return ClibIOMap{input_map};
}

END_NONAMESPACE

// @brief コンストラクタ
CgLogicSig::CgLogicSig(
  const TvFunc& func ///< [in] 対象の論理関数
) : mFunc{func}
{
}

// @brief シグネチャ文字列を返す．
string
CgLogicSig::str() const
{
  return make_signature(mFunc);
}

// @brief 変換を施した後のシグネチャ文字列を求める．
string
CgLogicSig::str(
  const ClibIOMap& iomap ///< [in] 変換マップ
) const
{
  auto npnmap = to_npnmap(iomap);
  auto xfunc = mFunc.xform(npnmap);
  return make_signature(xfunc);
}

// @brief 代表シグネチャに対する変換を求める．
ClibIOMap
CgLogicSig::rep_map() const
{
  auto npnmap = mFunc.npn_cannonical_map();
  return from_npnmap(npnmap);
}

END_NAMESPACE_YM_CLIB
