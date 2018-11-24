#ifndef CILATCHCELL_H
#define CILATCHCELL_H

/// @file CiLatchCell.h
/// @brief CiLatchCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLatchCell CiLatchCell.h "CiLatchCell.h"
/// @brief ラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatchCell :
  public CiCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  /// @param[in] data_in "data_in" 関数の式
  /// @param[in] enable "enable" 関数の式
  /// @param[in] enable_also "enable_also" 関数の式
  /// @param[in] alloc メモリアロケータ
  /// *1: - false 論理式なし
  ///     - true 論理式あり
  CiLatchCell(CiCellLibrary* library,
	      const ShString& name,
	      ClibArea area,
	      const vector<CiInputPin*>& input_list,
	      const vector<CiOutputPin*>& output_list,
	      const vector<CiInoutPin*>& inout_list,
	      const vector<CiBus*>& bus_list,
	      const vector<CiBundle*>& bundle_list,
	      const vector<CiTiming*>& timing_list,
	      const Expr& data_in,
	      const Expr& enable,
	      const Expr& enable_also,
	      Alloc& alloc);

  /// @brief デストラクタ
  ~CiLatchCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの時に true を返す．
  bool
  is_latch() const override;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const override;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const override;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // data_in 論理式
  Expr mDataIn;

  // enable 論理式
  Expr mEnable;

  // enable2 論理式
  Expr mEnable2;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLatchRCell CiLatchCell.h "CiLatchCell.h"
/// @brief クリア付きのラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatchRCell :
  public CiLatchCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  /// @param[in] data_in "data_in" 関数の式
  /// @param[in] enable "enable" 関数の式
  /// @param[in] enable_also "enable_also" 関数の式
  /// @param[in] clear "clear" 関数の式
  /// @param[in] alloc メモリアロケータ
  /// *1: - false 論理式なし
  ///     - true 論理式あり
  CiLatchRCell(CiCellLibrary* library,
	       const ShString& name,
	       ClibArea area,
	       const vector<CiInputPin*>& input_list,
	       const vector<CiOutputPin*>& output_list,
	       const vector<CiInoutPin*>& inout_list,
	       const vector<CiBus*>& bus_list,
	       const vector<CiBundle*>& bundle_list,
	       const vector<CiTiming*>& timing_list,
	       const Expr& data_in,
	       const Expr& enable,
	       const Expr& enable_also,
	       const Expr& clear,
	       Alloc& alloc);

  /// @brief デストラクタ
  ~CiLatchRCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの場合にクリア端子を持っていたら true を返す．
  bool
  has_clear() const override;

  /// @brief ラッチセルの場合にクリア条件を表す論理式を返す．
  /// @note クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clear 論理式
  Expr mClear;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLatchSCell CiLatchCell.h "CiLatchCell.h"
/// @brief プリセット付きのラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatchSCell :
  public CiLatchCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  /// @param[in] data_in "data_in" 関数の式
  /// @param[in] enable "enable" 関数の式
  /// @param[in] enable_also "enable_also" 関数の式
  /// @param[in] preset "preset" 関数の式
  /// @param[in] alloc メモリアロケータ
  /// *1: - false 論理式なし
  ///     - true 論理式あり
  CiLatchSCell(CiCellLibrary* library,
	       const ShString& name,
	       ClibArea area,
	       const vector<CiInputPin*>& input_list,
	       const vector<CiOutputPin*>& output_list,
	       const vector<CiInoutPin*>& inout_list,
	       const vector<CiBus*>& bus_list,
	       const vector<CiBundle*>& bundle_list,
	       const vector<CiTiming*>& timing_list,
	       const Expr& data_in,
	       const Expr& enable,
	       const Expr& enable_also,
	       const Expr& preset,
	       Alloc& alloc);

  /// @brief デストラクタ
  ~CiLatchSCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // preset 論理式
  Expr mPreset;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLatchSRCell CiLatchCell.h "CiLatchCell.h"
/// @brief クリア付きとプリセット付きのラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatchSRCell :
  public CiLatchRCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  /// @param[in] data_in "data_in" 関数の式
  /// @param[in] enable "enable" 関数の式
  /// @param[in] enable_also "enable_also" 関数の式
  /// @param[in] clear "clear" 関数の式
  /// @param[in] preset "preset" 関数の式
  /// @param[in] clear_preset_var1 clear と preset が同時にオンになったときの値1
  /// @param[in] clear_preset_var2 clear と preset が同時にオンになったときの値2
  /// @param[in] alloc メモリアロケータ
  /// *1: - false 論理式なし
  ///     - true 論理式あり
  CiLatchSRCell(CiCellLibrary* library,
		const ShString& name,
		ClibArea area,
		const vector<CiInputPin*>& input_list,
		const vector<CiOutputPin*>& output_list,
		const vector<CiInoutPin*>& inout_list,
		const vector<CiBus*>& bus_list,
		const vector<CiBundle*>& bundle_list,
		const vector<CiTiming*>& timing_list,
		const Expr& data_in,
		const Expr& enable,
		const Expr& enable_also,
		const Expr& clear,
		const Expr& preset,
		int clear_preset_var1,
		int clear_preset_var2,
		Alloc& alloc);

  /// @brief デストラクタ
  ~CiLatchSRCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;

  /// @brief clear_preset_var1 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  int
  clear_preset_var1() const override;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  int
  clear_preset_var2() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // preset 論理式
  Expr mPreset;

  // clear_preser_var1/var2
  ymuint8 mClearPresetVal[2];

};

END_NAMESPACE_YM_CLIB

#endif // CILATCHCELL_H
