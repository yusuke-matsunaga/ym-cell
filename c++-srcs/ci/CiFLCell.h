#ifndef CIFLCELL_H
#define CIFLCELL_H

/// @file CiFLCell.h
/// @brief CiLFCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiFLCell CiFLCell.h "CiFLCell.h"
/// @brief FFとラッチに共通なクラス
//////////////////////////////////////////////////////////////////////
class CiFLCell :
  public CiCell
{
public:

  /// @brief restore() 用のコンストラクタ
  CiFLCell(
    const CiCellLibrary* lib ///< [in] 親のライブラリ
  ) : CiCell{lib}
  {
  }

  /// @brief コンストラクタ
  CiFLCell(
    const CiCellLibrary* lib,  ///< [in] 親のライブラリ
    const ShString& name,      ///< [in] 名前
    ClibArea area,             ///< [in] 面積
    const ShString& var1,      ///< [in] 内部変数1の名前
    const ShString& var2,      ///< [in] 内部変数2の名前
    const Expr& clear,         ///< [in] "clear" 関数の式
    const Expr& preset,        ///< [in] "preset" 関数の式
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : CiCell{lib, name, area},
      mVar1{var1},
      mVar2{var2},
      mClear{clear},
      mPreset{preset},
      mCpv1{clear_preset_var1},
      mCpv2{clear_preset_var2}
  {
  }

  /// @brief デストラクタ
  ~CiFLCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部変数1の名前を返す．
  string
  qvar1() const override;

  /// @brief 内部変数1の名前を返す．
  string
  qvar2() const override;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var1() const override;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var2() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump_FL(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容を読み込む．
  void
  restore(
    Deserializer& s ///< [in] デシリアライザ
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 内部変数1
  ShString mVar1;

  // 内部変数2
  ShString mVar2;

  // clear 論理式
  Expr mClear;

  // preset 論理式
  Expr mPreset;

  // clear_preset_var1
  ClibCPV mCpv1;

  // clear_preset_var2
  ClibCPV mCpv2;

};

END_NAMESPACE_YM_CLIB

#endif // CIFLCELL_H
