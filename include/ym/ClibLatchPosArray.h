#ifndef YM_CLIBLATCHPOSARRAY_H
#define YM_CLIBLATCHPOSARRAY_H

/// @file ym/ClibLatchPosArray.h
/// @brief ClibLatchPosArray のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
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
  ClibLatchPosArray(int sig); ///< [in] 設定するシグネチャ

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
  ///
  /// クリア入力がない場合の値は不定
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
  ///
  /// プリセット入力がない場合の値は不定
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
  void
  set_signature(int sig); ///< [in] 設定するシグネチャ

  /// @brief 個々の情報を設定する．
  void
  set(int data_pos,     ///< [in] データ入力のピン番号
      int enable_pos,   ///< [in] イネーブル入力のピン番号
      int enable_sense, ///< [in] イネーブル入力の極性情報
      int clear_pos,    ///< [in] クリア入力のピン番号
      int clear_sense,  ///< [in] クリア入力の極性情報
      int preset_pos,   ///< [in] プリセット入力のピン番号
      int preset_sense, ///< [in] プリセット入力の極性情報
      int q_pos,        ///< [in] 肯定出力のピン番号
      int iq_pos);      ///< [in] 否定出力のピン番号


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン番号をパックしたもの
  int mData;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLATCHPOSARRAY_H
