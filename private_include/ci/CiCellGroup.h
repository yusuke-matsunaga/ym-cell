#ifndef CICELLGROUP_H
#define CICELLGROUP_H

/// @file CiCellGroup.h
/// @brief CiCellGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellGroup.h"
#include "ym/ClibObjList.h"
#include "ym/NpnMapM.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCell;
class CiCellClass;

//////////////////////////////////////////////////////////////////////
/// @class CiCellGroup CiCellGroup.h "CiCellGroup.h"
/// @brief ClibCellGroup の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellGroup :
  public ClibCellGroup
{
  friend class CiCellLibrary;

public:

  /// @brief コンストラクタ
  /// @param[in] id 番号
  /// @param[in] map 変換マップ
  /// @param[in] pininfo ピン情報
  /// @param[in] cell_list セルのリスト
  /// @param[in] alloc メモリアロケータ
  ///
  /// pininfo は restore() 時のみ指定する．
  /// それ以外は後で set_ff_info()/set_latch_info() で設定する．
  CiCellGroup(int id,
	      const NpnMapM& map,
	      int pininfo,
	      const vector<CiCell*>& cell_list);

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCellGroup();

  /// @brief デストラクタ
  ~CiCellGroup();


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  /// @note ClibCellLibrary::group(id) で返されるオブジェクトの id() は id となる．
  int
  id() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表クラスを返す．
  const ClibCellClass&
  rep_class() const override;

  /// @brief 代表クラスに対する変換マップを返す．
  const NpnMapM&
  map() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // FF/ラッチセルの場合にピンの情報を返す関数
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合のピン情報を返す．
  /// @note FFセル以外の場合には返り値は不定
  ClibFFInfo
  ff_info() const override;

  /// @brief ラッチセルの場合のピン情報を返す．
  /// @note ラッチセル以外の場合には返り値は不定
  ClibLatchInfo
  latch_info() const override;

  /// @brief 反転出力を持つ時 true を返す．
  bool
  has_xq() const override;

  /// @brief データ入力を持つとき true を返す．
  bool
  has_data() const override;

  /// @brief データ入力のピン番号を返す．
  int
  data_pos() const override;

  /// @brief クロック入力のタイプを返す．
  /// @retval 0 該当しない
  /// @retval 1 positive edge
  /// @retval 2 negative edge
  int
  clock_sense() const override;

  /// @brief クロック入力のピン番号を返す．
  int
  clock_pos() const override;

  /// @brief イネーブル入力を持つとき true を返す．
  bool
  has_enable() const override;

  /// @brief イネーブル入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 positive edge
  /// @retval 2 negative edge
  int
  enable_sense() const override;

  /// @brief イネーブル入力のピン番号を返す．
  int
  enable_pos() const override;

  /// @brief クリア入力を持つタイプの時に true を返す．
  bool
  has_clear() const override;

  /// @brief クリア入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  clear_sense() const override;

  /// @brief クリア入力のピン番号を返す．
  /// @note クリア入力がない場合の値は不定
  int
  clear_pos() const override;

  /// @brief プリセット入力を持つタイプの時に true を返す．
  bool
  has_preset() const override;

  /// @brief プリセット入力のタイプを返す．
  /// @retval 0 なし
  /// @retval 1 High sensitive
  /// @retval 2 Low sensitive
  int
  preset_sense() const override;

  /// @brief プリセット入力のピン番号を返す．
  /// @note プリセット入力がない場合の値は不定
  int
  preset_pos() const override;

  /// @brief 肯定出力のピン番号を返す．
  int
  q_pos() const override;

  /// @brief 否定出力のピン番号を返す．
  int
  xq_pos() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // このグループに属しているセルの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルのリストを返す．
  const ClibCellList&
  cell_list() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @param[in] id 番号
  /// @param[in] map 変換マップ
  /// @param[in] pininfo ピン情報
  /// @param[in] cell_list セルのリスト
  /// @param[in] alloc メモリアロケータ
  ///
  /// pininfo は restore() 時のみ指定する．
  /// それ以外は後で set_ff_info()/set_latch_info() で設定する．
  void
  init(int id,
       const NpnMapM& map,
       int pininfo,
       const vector<CiCell*>& cell_list);

  /// @brief 親のセルクラスを設定する．
  /// @param[in] cell_class 親のクラス
  void
  set_class(CiCellClass* cell_class);

  /// @brief FFのピン情報を設定する．
  /// @param[in] pos_array ピン位置と極性情報の配列
  /// @note pos_array の意味は以下の通り
  ///  - pos_array[0] : データ入力のピン番号     (3bit)
  ///  - pos_array[1] : クロック入力のピン番号   (3bit) | 極性情報 (1bit)
  ///  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
  ///  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
  ///  - pos_array[4] : 肯定出力のピン番号       (3bit)
  ///  - pos_array[5] : 否定出力のピン番号       (3bit) | あるかないか (1bit)
  void
  set_ff_info(int pos_array[]);

  /// @brief ラッチのピン情報を設定する．
  /// @param[in] pos_array ピン位置と極性情報の配列
  /// @note pos_array の意味は以下の通り
  ///  - pos_array[0] : データ入力のピン番号     (3bit)
  ///  - pos_array[1] : イネーブル入力のピン番号 (3bit) | 極性情報 (2bit)
  ///  - pos_array[2] : クリア入力のピン番号     (3bit) | 極性情報 (2bit)
  ///  - pos_array[3] : プリセット入力のピン番号 (3bit) | 極性情報 (2bit)
  ///  - pos_array[4] : 肯定出力のピン番号       (3bit)
   void
  set_latch_info(int pos_array[]);


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  void
  dump(ostream& bos) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID 番号
  int mId;

  // 属している ClibCellClass
  const ClibCellClass* mRepClass;

  // ClibCellClass に対する入出力の変換関数
  NpnMapM mMap;

  // FF/ラッチのピン情報
  int mPinInfo;

  // セルのリスト
  ClibCellList mCellList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUP_H
