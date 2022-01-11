#ifndef YM_CLIBCELL_H
#define YM_CLIBCELL_H

/// @file ym/ClibCell.h
/// @brief ClibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2016, 2017, 2021, 2022 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/Expr.h"
#include "ym/ClibArea.h"
#include "ym/ClibCellGroup.h"


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
  /// @name 基本情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  ///
  /// ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
  virtual
  SizeType
  id() const = 0;

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief 面積の取得
  virtual
  ClibArea
  area() const = 0;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name ピン情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン数の取得
  virtual
  SizeType
  pin_num() const = 0;

  /// @brief ピンの取得
  /// @return ピン情報を返す．
  virtual
  const ClibPin&
  pin(
    SizeType pin_id ///< [in] ピン番号 ( 0 <= pin_id < pin_num() )
  ) const = 0;

  /// @brief 名前からピン番号の取得
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  virtual
  SizeType
  pin_id(
    const string& name ///< [in] ピン名
  ) const = 0;

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
  ///
  /// input_num() + inout_num() に等しい．
  virtual
  SizeType
  input_num2() const = 0;

  /// @brief 入力ピンの取得
  ///
  /// id >= input_num() の場合には入出力ピンが返される．
  virtual
  const ClibPin&
  input(
    SizeType id ///< [in] 番号 ( 0 <= id < input_num2() )
  ) const = 0;

  /// @brief 出力ピン+入出力ピン数の取得
  ///
  /// output_num() + inout_num() に等しい．
  virtual
  SizeType
  output_num2() const = 0;

  /// @brief 出力ピンの取得
  ///
  /// id >= output_num() の場合には入出力ピンが返される．
  virtual
  const ClibPin&
  output(
    SizeType id ///< [in] 出力番号 ( 0 <= id < output_num2() )
  ) const = 0;

  /// @brief 入出力ピンの取得
  virtual
  const ClibPin&
  inout(
    SizeType id ///< [in] 番号 ( 0 <= id < inout_num() )
  ) const = 0;

  /// @brief 内部ピンの取得
  virtual
  const ClibPin&
  internal(
    SizeType id ///< [in] 内部ピン番号 ( 0 <= id < internal_num() )
  ) const = 0;

  /// @brief バス数の取得
  virtual
  SizeType
  bus_num() const = 0;

  /// @brief バスの取得
  virtual
  const ClibBus&
  bus(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bus_num() )
  ) const = 0;

  /// @brief 名前からバス番号の取得
  /// @return name という名前のバス番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  virtual
  SizeType
  bus_id(
    const string& name ///< [in] バス名
  ) const = 0;

  /// @brief バンドル数の取得
  virtual
  SizeType
  bundle_num() const = 0;

  /// @brief バンドルの取得
  virtual
  const ClibBundle&
  bundle(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bundle_num() )
  ) const = 0;

  /// @brief 名前からバンドル番号の取得
  /// @return name という名前のバンドル番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  virtual
  SizeType
  bundle_id(
    const string& name ///< [in] バンドル名
  ) const = 0;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name タイミング情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の数を返す．
  virtual
  SizeType
  timing_num() const = 0;

  /// @brief タイミング情報を返す．
  virtual
  const ClibTiming&
  timing(
    SizeType pos ///< [in] インデックス ( 0 <= pos < timing_num() )
  ) const = 0;

  /// @brief 条件に合致するタイミング情報のインデックスのリストを返す．
  virtual
  const vector<SizeType>&
  timing_id_list(
    SizeType ipos,        ///< [in] 開始ピン番号 ( 0 <= ipos < input_num2() )
    SizeType opos,        ///< [in] 終了ピン番号 ( 0 <= opos < output_num2() )
    ClibTimingSense sense ///< [in] タイミング情報の摘要条件
  ) const = 0;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 機能情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const
  {
    return cgroup().type();
  }

  /// @brief 組み合わせ論理タイプの時 true を返す．
  bool
  is_logic() const
  {
    return cgroup().type() == ClibCellType::Logic;
  }

  /// @brief FFタイプの時 true を返す．
  bool
  is_ff() const
  {
    return cgroup().is_ff();
  }

  /// @brief ラッチタイプの時 true を返す．
  bool
  is_latch() const
  {
    return cgroup().is_latch();
  }

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const
  {
    return cgroup().has_logic(pin_id);
  }

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const
  {
    return cgroup().has_logic();
  }

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const
  {
    return cgroup().logic_expr(pin_id);
  }

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const
  {
    return cgroup().has_tristate(pin_id);
  }

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const
  {
    return cgroup().tristate_expr(pin_id);
  }

  /// @brief 非同期 clear を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_clear() const
  {
    return cgroup().has_clear();
  }

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const
  {
    return cgroup().clear_expr();
  }

  /// @brief 非同期 preset を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_preset() const
  {
    return cgroup().has_preset();
  }

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const
  {
    return cgroup().preset_expr();
  }

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var1() const
  {
    return cgroup().clear_preset_var1();
  }

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var2() const
  {
    return cgroup().clear_preset_var2();
  }

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const
  {
    return cgroup().clock_expr();
  }

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const
  {
    return cgroup().clock2_expr();
  }

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const
  {
    return cgroup().next_state_expr();
  }

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const
  {
    return cgroup().enable_expr();
  }

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const
  {
    return cgroup().enable2_expr();
  }

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const
  {
    return cgroup().data_in_expr();
  }

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name dump/restore 関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループを返す．
  virtual
  const ClibCellGroup&
  cgroup() const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELL_H
