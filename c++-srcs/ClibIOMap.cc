
/// @file ClibIOMap.cc
/// @brief ClibIOMap の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibIOMap.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

void
dump_map_list(
  BinEnc& s,
  const vector<ClibPinMap>& map_list
)
{
  ymuint8 n = map_list.size();
  s << n;
  for ( auto map: map_list ) {
    map.dump(s);
  }
}

vector<ClibPinMap>
restore_map_list(
  BinDec& s
)
{
  ymuint8 n;
  s >> n;
  vector<ClibPinMap> tmp_list;
  for ( SizeType i = 0; i < n; ++ i ) {
    ClibPinMap map;
    map.restore(s);
    tmp_list.push_back(map);
  }
  return tmp_list;
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス ClibIOMap
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
ClibIOMap::dump(
  BinEnc& bos ///< [in] 出力先のストリーム
) const
{
  dump_map_list(bos, input_map_list());
  dump_map_list(bos, output_map_list());
  dump_map_list(bos, inout_map_list());
}

// @brief バイナリダンプされた内容を読み込む．
void
ClibIOMap::restore(
  BinDec& bis ///< [in] 入力元のストリーム
)
{
  mInputMap = restore_map_list(bis);
  mOutputMap = restore_map_list(bis);
  mInoutMap = restore_map_list(bis);
}

/// @relates ClibIOMap
/// @brief ClibIOMap のストリーム出力演算子
ostream&
operator<<(
  ostream& s, ///< [in] 出力先のストリーム
  const ClibIOMap& iomap ///< [in] 入出力のマッピング
)
{
  s << "Input[";
  for ( auto pinmap: iomap.input_map_list() ) {
    s << " " << pinmap;
  }
  s << "]";
  if ( iomap.output_num() > 0 ) {
    s << ", Output[";
    for ( auto pinmap: iomap.output_map_list() ) {
      s << " " << pinmap;
    }
    s << "]";
  }
  if ( iomap.inout_num() > 0 ) {
    s << ", Inout[";
    for ( auto pinmap: iomap.inout_map_list() ) {
      s << " " << pinmap;
    }
    s << "]";
  }
  return s;
}


//////////////////////////////////////////////////////////////////////
// クラス ClibPinMap
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
ClibPinMap::dump(
  BinEnc& bos ///< [in] 出力先のストリーム
) const
{
  bos << mBody;
}

// @brief バイナリダンプされた内容を読み込む．
void
ClibPinMap::restore(
  BinDec& bis ///< [in] 入力元のストリーム
)
{
  bis >> mBody;
}

END_NAMESPACE_YM_CLIB
