#ifndef CGSIGREP_H
#define CGSIGREP_H

/// @file CgSigRep.h
/// @brief CgSigRep のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibIOMap.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgSigRep CgSigRep.h "CgSigRep.h"
/// @brief CgSignature の中身を表す純粋仮想基底クラス
//////////////////////////////////////////////////////////////////////
class CgSigRep
{
public:

  /// @brief デストラクタ
  virtual
  ~CgSigRep() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャ文字列を返す．
  virtual
  string
  str() const = 0;

  /// @brief 変換を施した後のシグネチャを返す．
  virtual
  unique_ptr<const CgSigRep>
  xform(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const = 0;

  /// @brief 代表シグネチャに対する変換を求める．
  ClibIOMap
  rep_map() const;

  /// @brief 同位体変換のリストを求める．
  vector<ClibIOMap>
  idmap_list() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 正規形への変換を求める．
  virtual
  vector<ClibIOMap>
  gen_cannonical_map() const = 0;

  /// @brief 関数の内容を文字列に変換する．
  static
  string
  hex_str(
    const TvFunc& func
  );

  /// @brief 4ビットの整数値を16進数表記の文字に変換する
  static
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

  /// @brief ClibIOMap から NpnMap を作る．
  static
  NpnMap
  to_npnmap(
    const ClibIOMap& iomap, ///< [in] 対象の ClibIOMap
    SizeType opos           ///< [in] 出力ピン番号
                            ///<      入出力ピンも含む
  );

  /// @brief NpnMap から ClibIOMap を作る．
  static
  ClibIOMap
  from_npnmap(
    const NpnMap& npnmap
  );

};

END_NAMESPACE_YM_CLIB

#endif // CGSIGREP_H
