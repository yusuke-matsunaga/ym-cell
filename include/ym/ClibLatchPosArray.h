#ifndef YM_CLIBLATCHPOSARRAY_H
#define YM_CLIBLATCHPOSARRAY_H

/// @file ym/ClibLatchPosArray.h
/// @brief ClibLatchPosArray のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLatchPosArray ClibLatchPosArray.h "ym/ClibLatchPosArray.h"
/// @brief Latch のピン番号の情報を表すクラス
/// @note 実際には制御ピンの極性情報も合わせて持つ．
//////////////////////////////////////////////////////////////////////
class ClibLatchPosArray
{
public:

  /// @brief コンストラクタ
  ClibLatchPosArray();

  /// @brief シグネチャを指定するコンストラクタ
  explicit
  ClibLatchPosArray(int sig);

  /// @brief デストラクタ
  ~ClibLatchPosArray();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャを返す．
  int
  signature() const;

  /// @brief データ入力のピン番号を返す．
  int
  data_pos() const;

  /// @brief イネーブル入力のピン番号を返す．
  int
  enable_pos() const;

  /// @brief イネーブル入力の極性情報を返す．
  /// @retval 0 なし
  /// @retval 1 positive edge
  /// @retval 2 negative edge
  int
  enable_sense() const;

  /// @brief イネーブル入力を持つとき true を返す．
  bool
  has_enable() const;

  /// @brief クリア入力のピン番号を返す．
  /// @note クリア入力がない場合の値は不定
  int
  clear_pos() const;

  /// @brief クリア入力の極性情報を返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  clear_sense() const;

  /// @brief クリア入力を持つとき true を返す．
  bool
  has_clear() const;

  /// @brief プリセット入力のピン番号を返す．
  /// @note プリセット入力がない場合の値は不定
  int
  preset_pos() const;

  /// @brief プリセット入力の極性情報を返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  preset_sense() const;

  /// @brief プリセット入力を持つとき true を返す．
  bool
  has_preset() const;

  /// @brief 肯定出力のピン番号を返す．
  int
  q_pos() const;

  /// @brief 否定出力のピン番号を返す．
  int
  iq_pos() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャを設定する．
  /// @param[in] sig 設定するシグネチャ
  void
  set_signature(int sig);

  /// @brief 個々の情報を設定する．
  /// @param[in] data_pos データ入力のピン番号
  /// @param[in] enable_pos イネーブル入力のピン番号
  /// @param[in] enable_sense イネーブル入力の極性情報
  /// @param[in] clear_pos クリア入力のピン番号
  /// @param[in] clear_sense クリア入力の極性情報
  /// @param[in] preset_pos プリセット入力のピン番号
  /// @param[in] preset_sense プリセット入力の極性情報
  /// @param[in] q_pos 肯定出力のピン番号
  /// @param[in] iq_pos 否定出力のピン番号
  void
  set(int data_pos,
      int enable_pos,
      int enable_sense,
      int clear_pos,
      int clear_sense,
      int preset_pos,
      int preset_sense,
      int q_pos,
      int iq_pos);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン番号をパックしたもの
  int mData;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLATCHPOSARRAY_H
