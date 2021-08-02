#ifndef YM_CLIBFFINFO_H
#define YM_CLIBFFINFO_H

/// @file ym/ClibFFInfo.h
/// @brief ClibFFInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibFFInfo ClibFFInfo.h "ym/ClibFFInfo.h"
/// @brief FFセルのピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibFFInfo
{
public:

  /// @brief 空のコンストラクタ
  /// @note 内容は不定
  ClibFFInfo();

  /// @brief コンストラクタ
  ///
  /// pos_array の意味は以下の通り
  ///  - pos_array[0] : データ入力のピン番号     (3bit)
  ///  - pos_array[1] : クロック入力のピン番号   (3bit) | 極性情報 (1bit)
  ///  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
  ///  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
  ///  - pos_array[4] : 肯定出力のピン番号       (3bit)
  ///  - pos_array[5] : 否定出力のピン番号       (3bit) | あるかないか(1bit)
  ClibFFInfo(int pos_array[]); ///< [in] ピン位置と極性情報の配列

  /// @brief デストラクタ
  ~ClibFFInfo();


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を取り出す関数
  //////////////////////////////////////////////////////////////////////

  /// @brief クロック入力のタイプを返す．
  /// @retval 1 positive edge
  /// @retval 2 negative edge
  int
  clock_sense() const;

  /// @brief クリア入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  clear_sense() const;

  /// @brief プリセット入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  preset_sense() const;

  /// @brief 反転出力を持つタイプの時に true を返す．
  bool
  has_xq() const;

  /// @brief クリア入力を持つタイプの時に true を返す．
  bool
  has_clear() const;

  /// @brief プリセット入力を持つタイプの時に true を返す．
  bool
  has_preset() const;

  /// @brief データ入力のピン番号を返す．
  int
  data_pos() const;

  /// @brief クロック入力のピン番号を返す．
  int
  clock_pos() const;

  /// @brief クリア入力のピン番号を返す．
  ///
  /// クリア入力がない場合の値は不定
  int
  clear_pos() const;

  /// @brief プリセット入力のピン番号を返す．
  ///
  /// プリセット入力がない場合の値は不定
  int
  preset_pos() const;

  /// @brief 肯定出力のピン番号を返す．
  int
  q_pos() const;

  /// @brief 否定出力のピン番号を返す．
  int
  xq_pos() const;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const;

  /// @brief バイナリファイルを読み込む．
  void
  restore(
    istream& s ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン情報，ピン番号をパックしたもの
  ymuint32 mBits;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBFFINFO_H
