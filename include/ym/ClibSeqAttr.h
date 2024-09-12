#ifndef CLIBSEQATTR_H
#define CLIBSEQATTR_H

/// @file ClibSeqAttr.h
/// @brief ClibSeqAttr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibSeqAttr ClibSeqAttr.h "ClibSeqAttr.h"
/// @brief 順序セルの属性を表すクラス
///
/// 主にライブラリに対して当該のセルグループ(セルクラス)の問い合わせ
/// を行うときに用いられる．
///
/// 以下の情報を持つ．
///
/// - slave clock の有無
/// - 非同期 clear の有無
/// - 非同期 preset の有無
/// - clear_preset_var1/var2 の値
///
/// clear_preset_var1/var2 は 5x5 = 25 種類ある．
/// あとは3bitで表せるので全部で8bitで表せる．
//////////////////////////////////////////////////////////////////////
class ClibSeqAttr
{
public:

  /// @brief コンストラクタ
  ///
  /// clear と preset は両方 true ではない．
  ClibSeqAttr(
    bool slave_clock, ///< [in] slave clock の有無
    bool clear,       ///< [in] clear の有無
    bool preset       ///< [in] preset の有無
  )
  {
    if ( clear && preset ) {
      throw std::invalid_argument{"clear and preset should not be true at once"};
    }
    if ( slave_clock ) {
      mPackedVal |= (1U << 0);
    }
    if ( clear ) {
      mPackedVal |= (1U << 1);
    }
    if ( preset ) {
      mPackedVal |= (1U << 2);
    }
    std::uint8_t val = 0;
    val += static_cast<std::uint8_t>(ClibCPV::X);
    val += static_cast<std::uint8_t>(ClibCPV::X) * 5;
    mPackedVal |= (val << 3);
  }

  /// @brief コンストラクタ
  ///
  /// clear と preset を持つ場合
  ClibSeqAttr(
    bool slave_clock, ///< [in] slave clock の有無
    ClibCPV cpv1,     ///< [in] clear_preset_var1 の値
    ClibCPV cpv2      ///< [in] clear_preset_var2 の値
  )
  {
    if ( slave_clock ) {
      mPackedVal |= (1U << 0);
    }
    mPackedVal |= (1U << 1);
    mPackedVal |= (1U << 2);
    std::uint8_t val = 0;
    val += static_cast<std::uint8_t>(cpv1);
    val += static_cast<std::uint8_t>(cpv2) * 5;
    mPackedVal |= (val << 3);
  }

  /// @brief デストラクタ
  ~ClibSeqAttr() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief slave clock の有無
  bool
  has_slave_clock() const
  {
    return static_cast<bool>((mPackedVal >> 0) & 1);
  }

  /// @brief 非同期clearの有無
  bool
  has_clear() const
  {
    return static_cast<bool>((mPackedVal >> 1) & 1);
  }

  /// @brief 非同期presetの有無
  bool
  has_preset() const
  {
    return static_cast<bool>((mPackedVal >> 2) & 1);
  }

  /// @brief clear と preset が同時にアサートされたときの var1 の値
  ClibCPV
  cpv1() const
  {
    auto val = mPackedVal >> 3;
    return static_cast<ClibCPV>(val % 5);
  }

  /// @brief clear と preset が同時にアサートされたときの var2 の値
  ClibCPV
  cpv2() const
  {
    auto val = mPackedVal >> 3;
    return static_cast<ClibCPV>(val / 5);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // すべての値をパックしたもの
  // 0: slave_clock
  // 1: clear
  // 2: preset
  // 3-7: cpv1/cpv2 の組み合わせ
  std::uint8_t mPackedVal{0};

};

END_NAMESPACE_YM_CLIB

#endif // CLIBSEQATTR_H
