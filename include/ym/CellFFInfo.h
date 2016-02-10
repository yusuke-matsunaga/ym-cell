﻿#ifndef YM_CELLFFINFO_H
#define YM_CELLFFINFO_H

/// @file ym/CellFFInfo.h
/// @brief CellFFInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ym_cell.h"
#include "ym/IDO.h"
#include "ym/ODO.h"


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
/// @class CellFFInfo CellFFInfo.h "ym/CellFFInfo.h"
/// @brief FFセルのピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class CellFFInfo
{
public:

  /// @brief 空のコンストラクタ
  /// @note 内容は不定
  CellFFInfo();

  /// @brief コンストラクタ
  /// @param[in] pos_array ピン位置と極性情報の配列
  /// @note pos_array の意味は以下の通り
  ///  - pos_array[0] : データ入力のピン番号     (3bit)
  ///  - pos_array[1] : クロック入力のピン番号   (3bit) | 極性情報 (1bit)
  ///  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
  ///  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
  ///  - pos_array[4] : 肯定出力のピン番号       (3bit)
  ///  - pos_array[5] : 否定出力のピン番号       (3bit)
  CellFFInfo(ymuint pos_array[]);

  /// @brief デストラクタ
  ~CellFFInfo();


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を取り出す関数
  //////////////////////////////////////////////////////////////////////

  /// @brief クロック入力のタイプを返す．
  /// @retval 1 positive edge
  /// @retval 2 negative edge
  ymuint
  clock_sense() const;

  /// @brief クリア入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  ymuint
  clear_sense() const;

  /// @brief プリセット入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  ymuint
  preset_sense() const;

  /// @brief クリア入力を持つタイプの時に true を返す．
  bool
  has_clear() const;

  /// @brief プリセット入力を持つタイプの時に true を返す．
  bool
  has_preset() const;

  /// @brief データ入力のピン番号を返す．
  ymuint
  data_pos() const;

  /// @brief クロック入力のピン番号を返す．
  ymuint
  clock_pos() const;

  /// @brief クリア入力のピン番号を返す．
  /// @note クリア入力がない場合の値は不定
  ymuint
  clear_pos() const;

  /// @brief プリセット入力のピン番号を返す．
  /// @note プリセット入力がない場合の値は不定
  ymuint
  preset_pos() const;

  /// @brief 肯定出力のピン番号を返す．
  ymuint
  q_pos() const;

  /// @brief 否定出力のピン番号を返す．
  ymuint
  xq_pos() const;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  /// @param[in] ffinfo 対象の CellFFInfo
  /// @return ストリームを返す．
  friend
  ODO&
  operator<<(ODO& bos,
	     const CellFFInfo& ffinfo);

  /// @brief バイナリファイルを読み込む．
  /// @param[in] bis 入力元のストリーム
  /// @param[out] ffinfo 結果を格納する変数
  /// @return ストリームを返す．
  friend
  IDO&
  operator>>(IDO& bis,
	     CellFFInfo& ffinfo);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン情報，ピン番号をパックしたもの
  ymuint32 mBits;

};

END_NAMESPACE_YM_CELL

#endif // YM_CELLFFINFO_H
