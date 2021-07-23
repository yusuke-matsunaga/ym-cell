#ifndef CIFFCELL_H
#define CIFFCELL_H

/// @file CiFFCell.h
/// @brief CiFFCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiFFCell CiFFCell.h "CiFFCell.h"
/// @brief FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFCell :
  public CiCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiFFCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,          ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& next_state,                  ///< [in] "next_state" 関数の式
    const Expr& clocked_on,                  ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also              ///< [in] "clocked_on_also" 関数の式
  ) : CiCell(library, name, area,
	     input_list,
	     output_list,
	     inout_list,
	     vector<CiInternalPin*>{},
	     bus_list,
	     bundle_list,
	     timing_list),
      mNextState{next_state},
      mClock{clocked_on},
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFFCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの時に true を返す．
  bool
  is_ff() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // next_state 論理式
  Expr mNextState;

  // clock 論理式
  Expr mClock;

  // clock2 論理式
  Expr mClock2;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFRCell CiFFCell.h "CiFFCell.h"
/// @brief クリア付きのFFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFRCell :
  public CiFFCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiFFRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& clear                        ///< [in] "clear" 関数の式
  ) : CiFFCell(library, name, area,
	   input_list,
	       output_list,
	       inout_list,
	       bus_list,
	       bundle_list,
	       timing_list,
	       next_state,
	       clocked_on,
	       clocked_on_also),
      mClear{clear}
  {
  }

  /// @brief デストラクタ
  ~CiFFRCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
  bool
  has_clear() const override;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
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
/// @class CiFFSCell CiFFCell.h "CiFFCell.h"
/// @brief プリセット付きのFFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFSCell :
  public CiFFCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiFFSCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& preset                       ///< [in] "preset" 関数の式
  ) : CiFFCell(library, name, area,
	       input_list,
	       output_list,
	       inout_list,
	       bus_list,
	       bundle_list,
	       timing_list,
	       next_state,
	       clocked_on,
	       clocked_on_also),
      mPreset{preset}
  {
  }

  /// @brief デストラクタ
  ~CiFFSCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
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
/// @class CiFFSRCell CiFFCell.h "CiFFCell.h"
/// @brief クリア付きとプリセット付きのFFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFSRCell :
  public CiFFRCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiFFSRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& clear,                       ///< [in] "clear" 関数の式
    const Expr& preset,                      ///< [in] "preset" 関数の式
    int clear_preset_var1, ///< [in] clear と preset が同時にオンになったときの値1
    int clear_preset_var2  ///< [in] clear と preset が同時にオンになったときの値2
  ) : CiFFRCell(library, name, area,
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
      mPreset{preset},
      mClearPresetVal{
	static_cast<ymuint8>(clear_preset_var1),
	static_cast<ymuint8>(clear_preset_var2)
      }
  {
  }

  /// @brief デストラクタ
  ~CiFFSRCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;

  /// @brief clear_preset_var1 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  ///
  /// FFセルとラッチセルの時に意味を持つ．
  SizeType
  clear_preset_var1() const override;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  ///
  /// FFセルとラッチセルの時に意味を持つ．
  SizeType
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

#endif // CIFFCELL_H
