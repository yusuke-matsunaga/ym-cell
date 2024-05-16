#ifndef CILATCHCELL_H
#define CILATCHCELL_H

/// @file CiLatchCell.h
/// @brief CiLatchCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiFLCell.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

//////////////////////////////////////////////////////////////////////
/// @class CiLatchCell CiLatchCell.h "CiLatchCell.h"
/// @brief 単純なsingle-stage ラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatchCell :
  public CiFLCell
{
public:

  /// @brief restore() 用のコンストラクタ
  CiLatchCell(
    const CiCellLibrary* lib ///< [in] 親のライブラリ
  ) : CiFLCell{lib}
  {
  }

  /// @brief コンストラクタ
  CiLatchCell(
    const CiCellLibrary* lib,    ///< [in] 親のライブラリ
    const ShString& name,        ///< [in] 名前
    ClibArea area,               ///< [in] 面積
    const ShString& var1,        ///< [in] 内部変数1の名前
    const ShString& var2,        ///< [in] 内部変数2の名前
    const Expr& enable,          ///< [in] "enable" 関数の式
    const Expr& data_in,         ///< [in] "data_in" 関数の式
    const Expr& clear,           ///< [in] "clear" 関数の式
    const Expr& preset,          ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,   ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2    ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : CiFLCell{lib, name, area,
               var1, var2,
	       clear, preset,
	       clear_preset_var1,
	       clear_preset_var2},
      mEnable{enable},
      mDataIn{data_in}
  {
  }

  /// @brief デストラクタ
  ~CiLatchCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief ラッチセルの時に true を返す．
  bool
  is_latch() const override;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const override;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const override;


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
    Serializer& s ///< [in] シリアライザ
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    Deserializer& s ///< [in] デシリアライザ
  ) override;


protected:
  //////////////////////////////////////////////////////////////////////
  // dump/restore の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump_Latch(
    Serializer& s ///< [in] シリアライザ
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // enable 論理式
  Expr mEnable;

  // data_in 論理式
  Expr mDataIn;

};


//////////////////////////////////////////////////////////////////////
/// @class CiLatch2Cell CiLatchCell.h "CiLatchCell.h"
/// @brief 単純なmaster-slave ラッチセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLatch2Cell :
  public CiLatchCell
{
public:

  /// @brief restore() 用のコンストラクタ
  CiLatch2Cell(
    const CiCellLibrary* lib ///< [in] 親のライブラリ
  ) : CiLatchCell{lib}
  {
  }

  /// @brief コンストラクタ
  CiLatch2Cell(
    const CiCellLibrary* lib,    ///< [in] 親のライブラリ
    const ShString& name,	 ///< [in] 名前
    ClibArea area,		 ///< [in] 面積
    const ShString& var1,        ///< [in] 内部変数1の名前
    const ShString& var2,        ///< [in] 内部変数2の名前
    const Expr& enable,		 ///< [in] "enable" 関数の式
    const Expr& enable_also,	 ///< [in] "enable_also" 関数の式
    const Expr& data_in,	 ///< [in] "data_in" 関数の式
    const Expr& clear,           ///< [in] "clear" 関数の式
    const Expr& preset,          ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1,   ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2    ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : CiLatchCell{lib, name, area,
                  var1, var2,
		  enable, data_in,
		  clear, preset,
		  clear_preset_var1,
		  clear_preset_var2},
      mEnable2{enable_also}
  {
  }

  /// @brief デストラクタ
  ~CiLatch2Cell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    Serializer& s ///< [in] シリアライザ
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    Deserializer& s ///< [in] デシリアライザ
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // enable2 論理式
  Expr mEnable2;

};

END_NAMESPACE_YM_CLIB

#endif // CILATCHCELL_H
