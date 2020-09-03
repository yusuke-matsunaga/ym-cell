#ifndef YM_CLIBCELL_H
#define YM_CLIBCELL_H

/// @file ym/ClibCell.h
/// @brief ClibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2016, 2017 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.


#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/ClibArea.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCell ClibCell.h "ym/ClibCell.h"
/// @brief セル本体のクラス
//////////////////////////////////////////////////////////////////////
class ClibCell
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  ///
  /// ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
  virtual
  int
  id() const = 0;

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief 面積の取得
  virtual
  ClibArea
  area() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // ピン情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン数の取得
  virtual
  SizeType
  pin_num() const = 0;

  /// @brief ピンのリストの取得
  virtual
  const ClibCellPinList&
  pin_list() const = 0;

  /// @brief ピンの取得
  /// @param[in] pin_id ピン番号 ( 0 <= pin_id < pin_num() )
  /// @return ピン情報を返す．
  virtual
  const ClibCellPin&
  pin(int pin_id) const = 0;

  /// @brief 名前からピン番号の取得
  /// @param[in] name ピン名
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ -1 を返す．
  virtual
  int
  pin_id(const string& name) const = 0;

  /// @brief 名前からピン番号の取得
  /// @param[in] name ピン名
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ -1 を返す．
  virtual
  int
  pin_id(const char* name) const = 0;

  /// @brief 入力ピン数の取得
  virtual
  SizeType
  input_num() const = 0;

  /// @brief 出力ピン数の取得
  virtual
  SizeType
  output_num() const = 0;

  /// @brief 入出力ピン数の取得
  virtual
  SizeType
  inout_num() const = 0;

  /// @brief 内部ピン数の取得
  virtual
  SizeType
  internal_num() const = 0;

  /// @brief 入力ピン+入出力ピン数の取得
  /// @note input_num() + inout_num() に等しい．
  virtual
  SizeType
  input_num2() const = 0;

  /// @brief 入力ピンの取得
  /// @param[in] id 番号 ( 0 <= id < input_num2() )
  /// @note id >= input_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin&
  input(int id) const = 0;

  /// @brief 出力ピン+入出力ピン数の取得
  /// @note output_num() + inout_num() に等しい．
  virtual
  SizeType
  output_num2() const = 0;

  /// @brief 出力ピンの取得
  /// @param[in] id 出力番号 ( 0 <= id < output_num2() )
  /// @note id >= output_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin&
  output(int id) const = 0;

  /// @brief 入出力ピンの取得
  /// @param[in] id 番号 ( 0 <= id < inout_num() )
  virtual
  const ClibCellPin&
  inout(int id) const = 0;

  /// @brief 内部ピンの取得
  /// @param[in] id 内部ピン番号 ( 0 <= id < internal_num() )
  virtual
  const ClibCellPin&
  internal(int id) const = 0;

  /// @brief バス数の取得
  virtual
  SizeType
  bus_num() const = 0;

  /// @brief バスの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
  virtual
  const ClibBus&
  bus(int pos) const = 0;

  /// @brief 名前からバス番号の取得
  /// @param[in] name バス名
  /// @return name という名前のバス番号を返す．
  ///
  /// なければ -1 を返す．
  virtual
  int
  bus_id(const string& name) const = 0;

  /// @brief バンドル数の取得
  virtual
  SizeType
  bundle_num() const = 0;

  /// @brief バンドルの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
  virtual
  const ClibBundle&
  bundle(int pos) const = 0;

  /// @brief 名前からバンドル番号の取得
  /// @param[in] name バンドル名
  /// @return name という名前のバンドル番号を返す．
  ///
  /// なければ -1 を返す．
  virtual
  int
  bundle_id(const string& name) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報のリストを返す．
  virtual
  const ClibTimingList&
  timing_list() const = 0;

  /// @brief 条件に合致するタイミング情報のリストを返す．
  /// @param[in] ipos 開始ピン番号 ( 0 <= ipos < input_num2() )
  /// @param[in] opos 終了ピン番号 ( 0 <= opos < output_num2() )
  /// @param[in] sense タイミング情報の摘要条件
  virtual
  const ClibTimingList&
  timing_list(int ipos,
	      int opos,
	      ClibTimingSense sense) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 属している ClibCellGroup を返す．
  virtual
  const ClibCellGroup&
  cell_group() const = 0;

  /// @brief 組み合わせ論理セルの時に true を返す．
  virtual
  bool
  is_logic() const = 0;

  /// @brief FFセルの時に true を返す．
  virtual
  bool
  is_ff() const = 0;

  /// @brief ラッチセルの時に true を返す．
  virtual
  bool
  is_latch() const = 0;

  /// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
  virtual
  bool
  is_fsm() const = 0;

  /// @brief 出力の論理式を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  virtual
  bool
  has_logic(int pin_id) const = 0;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  virtual
  bool
  has_logic() const = 0;

  /// @brief 論理セルの場合に出力の論理式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  virtual
  Expr
  logic_expr(int pin_id) const = 0;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  virtual
  bool
  has_tristate(int pin_id) const = 0;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  /// @note 通常の論理セルの場合には定数0を返す．
  virtual
  Expr
  tristate_expr(int pin_id) const = 0;

  /// @brief FFセルの場合にFFのピン情報を得る．
  virtual
  ClibFFInfo
  ff_info() const = 0;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  next_state_expr() const = 0;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock_expr() const = 0;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock2_expr() const = 0;

  /// @brief ラッチセルの場合にFFのピン情報を得る．
  virtual
  ClibLatchInfo
  latch_info() const = 0;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  data_in_expr() const = 0;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable_expr() const = 0;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable2_expr() const = 0;

  /// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
  virtual
  bool
  has_clear() const = 0;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  /// @note クリア端子がない場合の返り値は不定
  virtual
  Expr
  clear_expr() const = 0;

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  virtual
  bool
  has_preset() const = 0;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  virtual
  Expr
  preset_expr() const = 0;

  /// @brief clear_preset_var1 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  virtual
  int
  clear_preset_var1() const = 0;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  virtual
  int
  clear_preset_var2() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ostream& s) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELL_H
