#ifndef CIFFCELL_H
#define CIFFCELL_H

/// @file CiFFCell.h
/// @brief CiFFCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiFFCell CiFFCell.h "CiFFCell.h"
/// @brief 単純なsingle-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFCell :
  public CiCell
{
public:

  /// @brief コンストラクタ
  CiFFCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,                  ///< [in] "clocked_on" 関数の式
    const Expr& next_state                   ///< [in] "next_state" 関数の式
  ) : CiCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      vector<CiInoutPin*>{},
      timing_list
#endif
    },
      mExprList{expr_list},
      mClock{clocked_on},
      mNextState{next_state}

  {
  }

  /// @brief デストラクタ
  ~CiFFCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief FFセルの時に true を返す．
  bool
  is_ff() const override;

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力の論理式のリスト
  vector<Expr> mExprList;

  // clock 論理式
  Expr mClock;

  // next_state 論理式
  Expr mNextState;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFRCell CiFFCell.h "CiFFCell.h"
/// @brief クリア付きのFFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFRCell :
  public CiFFCell
{
public:

  /// @brief コンストラクタ
  CiFFRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clear                        ///< [in] "clear" 関数の式
  ) : CiFFCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state
    },
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
public:

  /// @brief コンストラクタ
  CiFFSCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& preset                       ///< [in] "preset" 関数の式
  ) : CiFFCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state
    },
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
/// @brief クリアとプリセット付きのFFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFSRCell :
  public CiFFRCell
{
public:

  /// @brief コンストラクタ
  CiFFSRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clear,                       ///< [in] "clear" 関数の式
    const Expr& preset,                      ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,               ///< [in] "clear_preset_var1" の値
    ClibCPV clear_preset_var2                ///< [in] "clear_preset_var2" の値
  ) : CiFFRCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state,
      clear
    },
      mPreset{preset},
      mCPV{
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
  ///
  /// FFセルとラッチセルの時に意味を持つ．
  ClibCPV
  clear_preset_var1() const override;

  /// @brief clear_preset_var2 の取得
  ///
  /// FFセルとラッチセルの時に意味を持つ．
  ClibCPV
  clear_preset_var2() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // preset 論理式
  Expr mPreset;

  // clear_preser_var1/var2
  ymuint8 mCPV[2];

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFCell CiFFCell.h "CiFFCell.h"
/// @brief 単純なmulti-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFMCell :
  public CiFFCell
{
public:

  /// @brief コンストラクタ
  CiFFMCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,                  ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,             ///< [in] "clocked_on_also" 関数の式
    const Expr& next_state                   ///< [in] "next_state" 関数の式
  ) : CiFFCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state
    },
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFFMCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock2 論理式
  Expr mClock2;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFMRCell CiFFCell.h "CiFFCell.h"
/// @brief クリア付きのmulti-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFMRCell :
  public CiFFRCell
{
public:

  /// @brief コンストラクタ
  CiFFMRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clear                        ///< [in] "clear" 関数の式
  ) : CiFFRCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state,
      clear
    },
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFFMRCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock2 論理式
  Expr mClock2;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFMSCell CiFFCell.h "CiFFCell.h"
/// @brief プリセット付きの multi-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFMSCell :
  public CiFFSCell
{
public:

  /// @brief コンストラクタ
  CiFFMSCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& preset                       ///< [in] "preset" 関数の式
  ) : CiFFSCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state,
      preset
    },
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFFMSCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock2 論理式
  Expr mClock2;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFFMSRCell CiFFCell.h "CiFFCell.h"
/// @brief クリアとプリセット付きの multi-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFMSRCell :
  public CiFFSRCell
{
public:

  /// @brief コンストラクタ
  CiFFMSRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
    const Expr& clocked_on,		     ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,	     ///< [in] "clocked_on_also" 関数の式
    const Expr& next_state,		     ///< [in] "next_state" 関数の式
    const Expr& clear,                       ///< [in] "clear" 関数の式
    const Expr& preset,                      ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,               ///< [in] "clear_preset_var1" の値
    ClibCPV clear_preset_var2                ///< [in] "clear_preset_var2" の値
  ) : CiFFSRCell{
      library, name, area,
#if 0
      input_list,
      output_list,
      timing_list,
#endif
      expr_list,
      clocked_on,
      next_state,
      clear, preset,
      clear_preset_var1,
      clear_preset_var2
    },
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFFMSRCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock2 論理式
  Expr mClock2;

};

END_NAMESPACE_YM_CLIB

#endif // CIFFCELL_H
