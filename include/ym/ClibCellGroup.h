#ifndef YM_CLIBCELLGROUP_H
#define YM_CLIBCELLGROUP_H

/// @file ym/ClibCellGroup.h
/// @brief ClibCellGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/BinDec.h"
#include "ym/BinEnc.h"
#include "ym/ClibCellList.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellGroup ClibCellGroup.h "ym/ClibCellGroup.h"
/// @brief 論理的に等価なセルのグループを表すクラス
///
/// - 組み合わせ論理タイプ
///   各出力の論理関数と tristate 条件を表す論理関数を持つ．
///
/// - FFタイプ
///   single-stage, master-slave の区別，
///   非同期セット・クリアの有無，
///   リセット状態(セット・リセットの両方がアクティブ)
///   で区別されるFFコアの周囲の論理関数を持つ．
///
/// - latchタイプ
///   single-stage, master-slave の区別，
///   非同期セット・クリアの有無，
///   リセット状態(セット・リセットの両方がアクティブ)
///   で区別されるlatchコアの周囲の論理関数を持つ．
///
/// - fsmタイプ
///   statetableをコアとして，周囲の論理関数を持つ．
///
/// すべてのタイプで用いられる論理関数は入力ピンと入出力ピンをサポート
/// とする．FFセルの場合には内部ノードも使用可能
//////////////////////////////////////////////////////////////////////
class ClibCellGroup
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibCellGroup() = default;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 一般的な情報を取得する関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  ///
  /// ClibCellLibrary::group(id) で返されるオブジェクトの id() は id となる．
  virtual
  SizeType
  id() const = 0;

  /// @brief 代表クラスを返す．
  virtual
  const ClibCellClass&
  rep_class() const = 0;

  /// @brief 代表クラスに対する変換マップを返す．
  virtual
  const ClibIOMap&
  iomap() const = 0;

  /// @brief 入力ピン数+入出力ピン数を返す．
  virtual
  SizeType
  input_num() const = 0;

  /// @brief 出力ピン数+入出力ピン数を返す．
  virtual
  SizeType
  output_num() const = 0;

  /// @brief 入出力ピン数を返す．
  virtual
  SizeType
  inout_num() const = 0;

  /// @brief 内部ノード数を返す．
  virtual
  SizeType
  internal_node_num() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 機能情報を取得する関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  virtual
  ClibCellType
  type() const = 0;

  /// @brief FFタイプの時 true を返す．
  virtual
  bool
  is_ff() const = 0;

  /// @brief ラッチタイプの時 true を返す．
  virtual
  bool
  is_latch() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピン(入出力ピン)の情報を返す関数
  //
  // 入力として使うことのできるものは入力ピン，入出力ピンと FF タイプの
  // 場合の内部ノード(番号は input_num() )
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力の論理式を持っている時に true を返す．
  virtual
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const = 0;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  virtual
  bool
  has_logic() const = 0;

  /// @brief 出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  virtual
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const = 0;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  virtual
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const = 0;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  virtual
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name FF/ラッチセルの場合にピンの情報を返す関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief 非同期 clear を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  bool
  has_clear() const = 0;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  virtual
  Expr
  clear_expr() const = 0;

  /// @brief 非同期 preset を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  bool
  has_preset() const = 0;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  virtual
  Expr
  preset_expr() const = 0;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var1() const = 0;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var2() const = 0;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock_expr() const = 0;

  /// @brief master-slave FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock2_expr() const = 0;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  next_state_expr() const = 0;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable_expr() const = 0;

  /// @brief master-slave ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable2_expr() const = 0;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  data_in_expr() const = 0;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @name このグループに属しているセルの情報を取得する関数
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief セル数を返す．
  virtual
  SizeType
  cell_num() const = 0;

  /// @brief セルを返す．
  virtual
  const ClibCell&
  cell(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
  ) const = 0;

  /// @brief セルのリストを返す．
  virtual
  ClibCellList
  cell_list() const = 0;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLGROUP_H
