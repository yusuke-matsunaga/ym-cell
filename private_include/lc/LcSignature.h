#ifndef LCSIGNATURE_H
#define LCSIGNATURE_H

/// @file LcSignature.h
/// @brief LcSignature のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcSignature LcSignature.h "LcSignature.h"
/// @brief セルの機能を表すシグネチャ
///
/// 基本的には各出力の機能を表す論理関数だが，FF,ラッチの場合が面倒．
/// 外部インターフェイスとしては2つのシグネチャが等しいかの比較と
/// ハッシュ関数用のハッシュ値生成ができればよい．
/// ただし，入力と出力の順序入れ替えおよび極性反転を行なうNPN変換
/// に対応する必要がある．
///
/// 具体的には
/// - 組み合わせ論理
/// - FF
/// - ラッチ
/// の3種類に分けて考える．
///
/// 組み合わせ論理の場合に各出力に対して
/// - 機能を表す論理関数
/// - トライステート条件を表す論理関数
/// を持つ．
/// ともに入力変数の番号はセルの入力ピン番号に一致する．
/// トライステート条件を表す論理関数はその関数の出力が1の時に
/// 出力がトライステートになるものとする．
/// トライステートにならない出力の場合，トラーステート条件は
/// 恒偽関数となる．
/// 場合によっては入力変数として現れない入力ピンや出力の機能が
/// 定義されていない出力ピンがある場合もある．
///
/// FF の場合には
/// - クロックエッジを表す論理関数
/// - 次状態関数
/// - クリア条件を表す論理関数(もしあれば)
/// - プリセット条件を表す論理関数(もしあれば)
/// - クリアとプリセットが同時にアクティブになった時の状態
///
/// ラッチの場合には
/// - イネーブルを表す論理関数(もしあれば)
/// - データ入力を表す論理関数(もしあれば)
/// - クリア条件を表す論理関数(もしあれば)
/// - プリセット条件を表す論理関数(もしあれば)
/// - クリアとプリセットが同時にアクティブになった時の状態
///
/// SRラッチのように，イネーブルとデータ入力がない場合もある．
//////////////////////////////////////////////////////////////////////
class LcSignature
{
public:

  /// @brief デストラクタ
  virtual
  ~LcSignature() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を返す．
  virtual
  ClibCellType
  type() const = 0;

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

  /// @brief 出力の論理式を持っている時に true を返す．
  virtual
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  virtual
  bool
  has_logic() const;

  /// @brief 出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  virtual
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  virtual
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  virtual
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const;

  /// @brief 非同期 clear を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  bool
  has_clear() const;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  virtual
  Expr
  clear_expr() const;

  /// @brief 非同期 preset を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  bool
  has_preset() const;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  virtual
  Expr
  preset_expr() const;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var1() const;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var2() const;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock_expr() const;

  /// @brief master-slave FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock2_expr() const;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  next_state_expr() const;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable_expr() const;

  /// @brief master-slave ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable2_expr() const;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  data_in_expr() const;

  /// @brief 内容を表す文字列を作る．
  virtual
  string
  str() const = 0;

  /// @brief 等価比較演算子
  bool
  operator==(
    const LcSignature& right ///< [in] 比較対象のオペランド
  ) const
  {
    return str() == right.str();
  }

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCSIGNATURE_H
