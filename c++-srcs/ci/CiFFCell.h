﻿#ifndef CIFFCELL_H
#define CIFFCELL_H

/// @file CiFFCell.h
/// @brief CiFFCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiFLCell.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

//////////////////////////////////////////////////////////////////////
/// @class CiFFCell CiFFCell.h "CiFFCell.h"
/// @brief 単純なsingle-stage FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFFCell :
  public CiFLCell
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiFFCell() = default;

  /// @brief コンストラクタ
  CiFFCell(
    const ShString& name,        ///< [in] 名前
    ClibArea area,               ///< [in] 面積
    const ShString& var1,        ///< [in] 内部変数1の名前
    const ShString& var2,        ///< [in] 内部変数2の名前
    const Expr& clocked_on,      ///< [in] "clocked_on" 関数の式
    const Expr& next_state,      ///< [in] "next_state" 関数の式
    const Expr& clear,           ///< [in] "clear" 関数の式
    const Expr& preset,          ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,   ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2    ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : CiFLCell{name, area,
               var1, var2,
               clear, preset,
	       clear_preset_var1,
	       clear_preset_var2},
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

  /// @brief 組み合わせ論理タイプの時 true を返す．
  bool
  is_logic() const override;

  /// @brief FFセルの時に true を返す．
  bool
  is_ff() const override;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // CiCell の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャを返す．
  CgSignature
  make_signature(
    const CiCellLibrary* library ///< [in] ライブラリ
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


protected:
  //////////////////////////////////////////////////////////////////////
  // dump/restore の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump_FF(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const;



private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock 論理式
  Expr mClock;

  // next_state 論理式
  Expr mNextState;

};


//////////////////////////////////////////////////////////////////////
/// @class CiFF2Cell CiFFCell.h "CiFFCell.h"
/// @brief 単純なmaster-slave FFセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFF2Cell :
  public CiFFCell
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiFF2Cell() = default;

  /// @brief コンストラクタ
  CiFF2Cell(
    const ShString& name,        ///< [in] 名前
    ClibArea area,               ///< [in] 面積
    const ShString& var1,        ///< [in] 内部変数1の名前
    const ShString& var2,        ///< [in] 内部変数2の名前
    const Expr& clocked_on,      ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also, ///< [in] "clocked_on_also" 関数の式
    const Expr& next_state,      ///< [in] "next_state" 関数の式
    const Expr& clear,           ///< [in] "clear" 関数の式
    const Expr& preset,          ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,   ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2    ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : CiFFCell{name, area,
               var1, var2,
               clocked_on, next_state,
	       clear, preset,
               clear_preset_var1,
               clear_preset_var2},
      mClock2{clocked_on_also}
  {
  }

  /// @brief デストラクタ
  ~CiFF2Cell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock2 論理式
  Expr mClock2;

};

END_NAMESPACE_YM_CLIB

#endif // CIFFCELL_H
