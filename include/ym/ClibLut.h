#ifndef YM_CLIBLUT_H
#define YM_CLIBLUT_H

/// @file ym/ClibLut.h
/// @brief ClibLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

class CiLut;

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLut ClibLut.h "ym/ClibLut.h"
/// @brief ルックアップテーブル(LUT)を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibLut
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibLut() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibLut(
    const CiLut* impl ///< [in] 本体
  );

  /// @brief デストラクタ
  ~ClibLut();


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 属性の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief 次元数の取得
  SizeType
  dimension() const;

  /// @brief 変数型の取得
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const;

  /// @brief インデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] pos_array 格子点座標
  ) const;

  /// @brief 値の取得
  ///
  /// @note val_array のサイズは dimension() と同じ
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
  ) const;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  // mImpl に関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 適正な値を持っている時 true を返す．
  bool
  is_valid() const
  {
    return mImpl != nullptr;
  }

  /// @brief 不正値の時 true を返す．
  bool
  is_invalid() const
  {
    return !is_valid();
  }

  /// @brief 等価比較
  bool
  operator==(
    const ClibLut& right
  ) const
  {
    return mImpl == right.mImpl;
  }

  /// @brief 非等価比較
  bool
  operator!=(
    const ClibLut& right
  ) const
  {
    return !operator==(right);
  }

  /// @brief 適正な値を持っているかチェックする．
  void
  _check_valid() const
  {
    if ( !is_valid() ) {
      throw std::invalid_argument{"not having a valid data"};
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 実装
  const CiLut* mImpl;


};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLUT_H
