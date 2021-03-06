﻿
/// @file CiLatchCell.cc
/// @brief CiLatchCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiLatchCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] data_in "data_in" 関数の式
// @param[in] enable "enable" 関数の式
// @param[in] enable_also "enable_also" 関数の式
CiLatchCell::CiLatchCell(CiCellLibrary* library,
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
			 const Expr& enable_also) :
  CiCell(library, name, area,
	 input_list,
	 output_list,
	 inout_list,
	 vector<CiInternalPin*>(),
	 bus_list,
	 bundle_list,
	 timing_list),
  mDataIn(data_in),
  mEnable(enable),
  mEnable2(enable_also)
{
}

// @brief デストラクタ
CiLatchCell::~CiLatchCell()
{
}

// @brief ラッチセルの時に true を返す．
bool
CiLatchCell::is_latch() const
{
  return true;
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::data_in_expr() const
{
  return mDataIn;
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::enable_expr() const
{
  return mEnable;
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::enable2_expr() const
{
  return mEnable2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchRCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] data_in "data_in" 関数の式
// @param[in] enable "enable" 関数の式
// @param[in] enable_also "enable_also" 関数の式
// @param[in] clear "clear" 関数の式
CiLatchRCell::CiLatchRCell(CiCellLibrary* library,
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
			   const Expr& clear) :
  CiLatchCell(library, name, area,
	      input_list,
	      output_list,
	      inout_list,
	      bus_list,
	      bundle_list,
	      timing_list,
	      data_in,
	      enable,
	      enable_also),
  mClear(clear)
{
}

// @brief デストラクタ
CiLatchRCell::~CiLatchRCell()
{
}

// @brief ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiLatchRCell::has_clear() const
{
  return true;
}

// @brief ラッチセルの場合にクリア条件を表す論理式を返す．
// @note クリア端子がない場合の返り値は不定
Expr
CiLatchRCell::clear_expr() const
{
  return mClear;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchSCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] data_in "data_in" 関数の式
// @param[in] enable "enable" 関数の式
// @param[in] enable_also "enable_also" 関数の式
// @param[in] preset "preset" 関数の式
// *1: - false 論理式なし
//     - true 論理式あり
CiLatchSCell::CiLatchSCell(CiCellLibrary* library,
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
			   const Expr& preset) :
  CiLatchCell(library, name, area,
	      input_list,
	      output_list,
	      inout_list,
	      bus_list,
	      bundle_list,
	      timing_list,
	      data_in,
	      enable,
	      enable_also),
  mPreset(preset)
{
}

// @brief デストラクタ
CiLatchSCell::~CiLatchSCell()
{
}

// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiLatchSCell::has_preset() const
{
  return true;
}

// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiLatchSCell::preset_expr() const
{
  return mPreset;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchSRCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] data_in "data_in" 関数の式
// @param[in] enable "enable" 関数の式
// @param[in] enable_also "enable_also" 関数の式
// @param[in] clear "clear" 関数の式
// @param[in] preset "preset" 関数の式
// @param[in] clear_preset_var1 clear と preset が同時にオンになったときの値1
// @param[in] clear_preset_var2 clear と preset が同時にオンになったときの値2
// *1: - false 論理式なし
//     - true 論理式あり
CiLatchSRCell::CiLatchSRCell(CiCellLibrary* library,
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
			     int clear_preset_var2) :
  CiLatchRCell(library, name, area,
	       input_list,
	       output_list,
	       inout_list,
	       bus_list,
	       bundle_list,
	       timing_list,
	       data_in,
	       enable,
	       enable_also,
	       clear),
  mPreset(preset)
{
  mClearPresetVal[0] = clear_preset_var1;
  mClearPresetVal[1] = clear_preset_var2;
}

// @brief デストラクタ
CiLatchSRCell::~CiLatchSRCell()
{
}

// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiLatchSRCell::has_preset() const
{
  return true;
}

// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiLatchSRCell::preset_expr() const
{
  return mPreset;
}

// @brief clear_preset_var1 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
int
CiLatchSRCell::clear_preset_var1() const
{
  return mClearPresetVal[0];
}

// @brief clear_preset_var2 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
int
CiLatchSRCell::clear_preset_var2() const
{
  return mClearPresetVal[1];
}

END_NAMESPACE_YM_CLIB
