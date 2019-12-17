
/// @file CiFFCell.cc
/// @brief CiFFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiFFCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
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
// @param[in] next_state "next_state" 関数の式
// @param[in] clocked_on "clocked_on" 関数の式
// @param[in] clocked_on_also "clocked_on_also" 関数の式
CiFFCell::CiFFCell(CiCellLibrary* library,
		   const ShString& name,
		   ClibArea area,
		   const vector<CiInputPin*>& input_list,
		   const vector<CiOutputPin*>& output_list,
		   const vector<CiInoutPin*>& inout_list,
		   const vector<CiBus*>& bus_list,
		   const vector<CiBundle*>& bundle_list,
		   const vector<CiTiming*>& timing_list,
		   const Expr& next_state,
		   const Expr& clocked_on,
		   const Expr& clocked_on_also) :
  CiCell(library, name, area,
	 input_list,
	 output_list,
	 inout_list,
	 vector<CiInternalPin*>(),
	 bus_list,
	 bundle_list,
	 timing_list),
  mNextState(next_state),
  mClock(clocked_on),
  mClock2(clocked_on_also)
{
}

// @brief デストラクタ
CiFFCell::~CiFFCell()
{
}

// @brief FFセルの時に true を返す．
bool
CiFFCell::is_ff() const
{
  return true;
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::next_state_expr() const
{
  return mNextState;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::clock_expr() const
{
  return mClock;
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::clock2_expr() const
{
  return mClock2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFRCell
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
// @param[in] next_state "next_state" 関数の式
// @param[in] clocked_on "clocked_on" 関数の式
// @param[in] clocked_on_also "clocked_on_also" 関数の式
// @param[in] clear "clear" 関数の式
CiFFRCell::CiFFRCell(CiCellLibrary* library,
		     const ShString& name,
		     ClibArea area,
		     const vector<CiInputPin*>& input_list,
		     const vector<CiOutputPin*>& output_list,
		     const vector<CiInoutPin*>& inout_list,
		     const vector<CiBus*>& bus_list,
		     const vector<CiBundle*>& bundle_list,
		     const vector<CiTiming*>& timing_list,
		     const Expr& next_state,
		     const Expr& clocked_on,
		     const Expr& clocked_on_also,
		     const Expr& clear) :
  CiFFCell(library, name, area,
	   input_list,
	   output_list,
	   inout_list,
	   bus_list,
	   bundle_list,
	   timing_list,
	   next_state,
	   clocked_on,
	   clocked_on_also),
  mClear(clear)
{
}

// @brief デストラクタ
CiFFRCell::~CiFFRCell()
{
}

// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiFFRCell::has_clear() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
// @note クリア端子がない場合の返り値は不定
Expr
CiFFRCell::clear_expr() const
{
  return mClear;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFSCell
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
// @param[in] next_state "next_state" 関数の式
// @param[in] clocked_on "clocked_on" 関数の式
// @param[in] clocked_on_also "clocked_on_also" 関数の式
// @param[in] preset "preset" 関数の式
CiFFSCell::CiFFSCell(CiCellLibrary* library,
		     const ShString& name,
		     ClibArea area,
		     const vector<CiInputPin*>& input_list,
		     const vector<CiOutputPin*>& output_list,
		     const vector<CiInoutPin*>& inout_list,
		     const vector<CiBus*>& bus_list,
		     const vector<CiBundle*>& bundle_list,
		     const vector<CiTiming*>& timing_list,
		     const Expr& next_state,
		     const Expr& clocked_on,
		     const Expr& clocked_on_also,
		     const Expr& preset) :
  CiFFCell(library, name, area,
	   input_list,
	   output_list,
	   inout_list,
	   bus_list,
	   bundle_list,
	   timing_list,
	   next_state,
	   clocked_on,
	   clocked_on_also),
  mPreset(preset)
{
}

// @brief デストラクタ
CiFFSCell::~CiFFSCell()
{
}

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiFFSCell::has_preset() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiFFSCell::preset_expr() const
{
  return mPreset;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFSRCell
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
// @param[in] next_state "next_state" 関数の式
// @param[in] clocked_on "clocked_on" 関数の式
// @param[in] clocked_on_also "clocked_on_also" 関数の式
// @param[in] clear "clear" 関数の式
// @param[in] preset "preset" 関数の式
// @param[in] clear_preset_var1 clear と preset が同時にオンになったときの値1
// @param[in] clear_preset_var2 clear と preset が同時にオンになったときの値1
CiFFSRCell::CiFFSRCell(CiCellLibrary* library,
		       const ShString& name,
		       ClibArea area,
		       const vector<CiInputPin*>& input_list,
		       const vector<CiOutputPin*>& output_list,
		       const vector<CiInoutPin*>& inout_list,
		       const vector<CiBus*>& bus_list,
		       const vector<CiBundle*>& bundle_list,
		       const vector<CiTiming*>& timing_list,
		       const Expr& next_state,
		       const Expr& clocked_on,
		       const Expr& clocked_on_also,
		       const Expr& clear,
		       const Expr& preset,
		       int clear_preset_var1,
		       int clear_preset_var2) :
  CiFFRCell(library, name, area,
	    input_list,
	    output_list,
	    inout_list,
	    bus_list,
	    bundle_list,
	    timing_list,
	    next_state,
	    clocked_on,
	    clocked_on_also,
	    clear),
  mPreset(preset)
{
  mClearPresetVal[0] = clear_preset_var1;
  mClearPresetVal[1] = clear_preset_var2;
}

// @brief デストラクタ
CiFFSRCell::~CiFFSRCell()
{
}

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiFFSRCell::has_preset() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiFFSRCell::preset_expr() const
{
  return mPreset;
}

// @brief clear_preset_var1 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
int
CiFFSRCell::clear_preset_var1() const
{
  return mClearPresetVal[0];
}

// @brief clear_preset_var2 の取得
// @retval 0 "L"
// @retval 1 "H"
// @note FFセルとラッチセルの時に意味を持つ．
int
CiFFSRCell::clear_preset_var2() const
{
  return mClearPresetVal[1];
}

END_NAMESPACE_YM_CLIB
