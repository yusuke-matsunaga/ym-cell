#ifndef CICELLGROUP_H
#define CICELLGROUP_H

/// @file CiCellGroup.h
/// @brief CiCellGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellGroup.h"
#include "ym/Expr.h"
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
  CiCellGroup(
    SizeType id,                    ///< [in] 番号
    const ClibCellClass* rep_class, ///< [in] 親のセルクラス
    const NpnMapM& map              ///< [in] 変換マップ
  );

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCellGroup() = default;

  /// @brief デストラクタ
  ~CiCellGroup() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 一般的な情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  SizeType
  id() const override;

  /// @brief 親のセルクラスを返す．
  const ClibCellClass&
  rep_class() const override;

  /// @brief 入力ピン数+入出力ピン数を返す．
  SizeType
  input_num() const override;

  /// @brief 出力ピン数+入出力ピン数を返す．
  SizeType
  output_num() const override;

  /// @brief 入出力ピン数を返す．
  SizeType
  inout_num() const override;

  /// @brief 内部ノード数を返す．
  SizeType
  internal_node_num() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表クラスに対する変換マップを返す．
  const NpnMapM&
  map() const override;

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// s@brief FFセルの時に true を返す．
  bool
  is_ff() const override;

  /// @brief ラッチセルの時に true を返す．
  bool
  is_latch() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 組み合わせ論理セルの場合のピンの情報を返す関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const override;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const override;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const override;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // FF/ラッチセルの場合にピンの情報を返す関数
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
  bool
  has_clear() const override;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
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

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const override;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const override;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // このグループに属しているセルの情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セル数を返す．
  SizeType
  cell_num() const override;

  /// @brief セルを返す．
  const ClibCell&
  cell(
    SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルを追加する．
  void
  add_cell(
    CiCell* cell
  );


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    ostream& bos ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID 番号
  SizeType mId{CLIB_NULLID};

  // 属している ClibCellClass
  const ClibCellClass* mRepClass{nullptr};

  // ClibCellClass に対する入出力の変換関数
  NpnMapM mMap;

  // セルのリスト
  vector<CiCell*> mCellList;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLGROUP_H
