#ifndef CILATCHCELL_H
#define CILATCHCELL_H

/// @file CiLatchCell.h
/// @brief CiLatchCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
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
  CiLatchCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,          ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& data_in,                     ///< [in] "data_in" 関数の式
    const Expr& enable,                      ///< [in] "enable" 関数の式
    const Expr& enable_also                  ///< [in] "enable_also" 関数の式
  ) : CiCell(library, name, area,
	     input_list,
	     output_list,
	     inout_list,
	     vector<CiInternalPin*>{},
	     bus_list,
	     bundle_list,
	     timing_list),
      mDataIn{data_in},
      mEnable{enable},
      mEnable2{enable_also}
  {
  }

  /// @brief デストラクタ
  ~CiLatchCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの時に true を返す．
  bool
  is_latch() const override;

  /// @brief ラッチセルの場合にFFのピン情報を得る．
  ClibLatchInfo
  latch_info() const override;

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
  CiLatchRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& data_in,		     ///< [in] "data_in" 関数の式
    const Expr& enable,			     ///< [in] "enable" 関数の式
    const Expr& enable_also,		     ///< [in] "enable_also" 関数の式
    const Expr& clear                        ///< [in] "clear" 関数の式
  ) : CiLatchCell(library, name, area,
		  input_list,
		  output_list,
		  inout_list,
		  bus_list,
		  bundle_list,
		  timing_list,
		  data_in,
		  enable,
		  enable_also),
      mClear{clear}
  {
  }

  /// @brief デストラクタ
  ~CiLatchRCell() = default;


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
  CiLatchSCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& data_in,		     ///< [in] "data_in" 関数の式
    const Expr& enable,			     ///< [in] "enable" 関数の式
    const Expr& enable_also,		     ///< [in] "enable_also" 関数の式
    const Expr& preset			     ///< [in] "preset" 関数の式
  ) : CiLatchCell(library, name, area,
		  input_list,
		  output_list,
		  inout_list,
		  bus_list,
		  bundle_list,
		  timing_list,
		  data_in,
		  enable,
		  enable_also),
      mPreset{preset}
  {
  }

  /// @brief デストラクタ
  ~CiLatchSCell() = default;


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
  CiLatchSRCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,		     ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& data_in,		     ///< [in] "data_in" 関数の式
    const Expr& enable,			     ///< [in] "enable" 関数の式
    const Expr& enable_also,		     ///< [in] "enable_also" 関数の式
    const Expr& clear,			     ///< [in] "clear" 関数の式
    const Expr& preset,		             ///< [in] "preset" 関数の式
    SizeType clear_preset_var1,  ///< [in] clear と preset が同時にオンになったときの値1
    SizeType clear_preset_var2   ///< [in] clear と preset が同時にオンになったときの値2
  ) : CiLatchRCell(library, name, area,
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
      mPreset{preset},
      mClearPresetVal{
	static_cast<ymuint8>(clear_preset_var1),
	static_cast<ymuint8>(clear_preset_var2)
      }
  {
  }

  /// @brief デストラクタ
  ~CiLatchSRCell() = default;


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

#endif // CILATCHCELL_H
