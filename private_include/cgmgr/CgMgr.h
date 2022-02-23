#ifndef CGMGR_H
#define CGMGR_H

/// @file CgMgr.h
/// @brief CgMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellClass;
class CiCellGroup;
class CiCell;
class CgSignature;

//////////////////////////////////////////////////////////////////////
/// @class CgMgr CgMgr.h "CgMgr.h"
/// @brief セルグループを管理するクラス
//////////////////////////////////////////////////////////////////////
class CgMgr
{
public:

  /// @brief コンストラクタ
  explicit
  CgMgr(
    CiCellLibrary& library ///< [in] 対象のセルライブラリ
  );

  /// @brief デストラクタ
  ~CgMgr() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief セルをグループに登録する．
  /// @return セルの所属するグループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  reg_group(
    const CiCell* cell ///< [in] セル
  );

  /// @brief 論理セルグループ番号を得る．
  SizeType
  logic_group(
    SizeType type ///< [in] グループの種類
                  ///<  - 0: 定数0
                  ///<  - 1: 定数1
                  ///<  - 2: バッファ
                  ///<  - 3: インバータ
  ) const
  {
    ASSERT_COND( 0 <= type && type < 4 );
    return mLogicGroup[type];
  }

#if 0
  /// @brief 1出力の組み合わせ論理用セルグループを得る．
  ///
  /// 通常のテクノロジマッピングで用いられるのはこのグループ内のセルのみ．
  CiCellGroup*
  find_logic_group(
    SizeType input_num, ///< [in] 入力数
    const Expr& expr    ///< [in] 出力の論理式
  );

  /// @brief 1出力のtristate論理用セルグループを得る．
  CiCellGroup*
  find_logic_group(
    SizeType input_num,  ///< [in] 入力数
    const Expr& expr,    ///< [in] 出力の論理式
    const Expr& tristate ///< [in] トライステート条件式
  );

  /// @brief 一般的な組み合わせ論理用セルグループを得る．
  CiCellGroup*
  find_logic_group(
    SizeType input_num,                ///< [in] 入力数
    SizeType output_num,               ///< [in] 出力数
    SizeType inout_num,                ///< [in] 入出力数
    const vector<Expr>& expr_array,    ///< [in] 出力の論理式の配列
                                       ///<  - 配列のサイズは output_num + inout_num
                                       ///<  - 論理式を持たない場合にはinvalid な Expr を持つ
                                       ///<    (Expr::is_valid() == false)．
    const vector<Expr>& tristate_array ///< [in] 出力のtristate条件の配列
                                       ///<  - 配列のサイズは output_num + inout_num
                                       ///<  - tristate にならない場合は定数0となる．
  );

  /// @brief フリップフロップ用セルグループを得る．
  CiCellGroup*
  find_ff_group(
    SizeType input_num,                 ///< [in] 入力数
    SizeType output_num,                ///< [in] 出力数
    SizeType inout_num,                 ///< [in] 入出力数
    const vector<Expr>& expr_array,     ///< [in] 出力の論理式の配列
                                        ///<  - 配列のサイズは output_num + inout_num
                                        ///<  - 論理式を持たない場合にはinvalid な Expr を持つ
                                        ///<    (Expr::is_valid() == false)．
    const vector<Expr>& tristate_array, ///< [in] 出力のtristate条件の配列
                                        ///<  - 配列のサイズは output_num + inout_num
                                        ///<  - tristate にならない場合は定数0となる．
    const Expr& clock,                  ///< [in] マスタークロックの論理式
    const Expr& clock2,                 ///< [in] スレーブクロックの論理式
                                        ///<  - single-stage FF の場合は定数0
    const Expr& next_state,             ///< [in] 次状態の論理式
                                        ///<  - invalid の場合もある．
    const Expr& clear,                  ///< [in] クリア条件の論理式
                                        ///<  - 定数0の場合もある．
    const Expr& preset,                 ///< [in] プリセット条件の論理式
                                        ///<  - 定数0の場合もある．
    ClibCPV clear_preset_var1,          ///< [in] クリアとプリセットが同時にアクティブになった時の値1
                                        ///<  - clear, preset が非0の時意味を持つ．
    ClibCPV clear_preset_var2           ///< [in] クリアとプリセットが同時にアクティブになった時の値2
                                        ///<  - clear, preset が非0の時意味を持つ．
  );

  /// @brief ラッチ用セルグループを得る．
  CiCellGroup*
  find_latch_group(
    SizeType input_num,                 ///< [in] 入力数
    SizeType output_num,                ///< [in] 出力数
    SizeType inout_num,                 ///< [in] 入出力数
    const vector<Expr>& expr_array,     ///< [in] 出力の論理式の配列
                                        ///<  - 配列のサイズは output_num + inout_num
                                        ///<  - 論理式を持たない場合にはinvalid な Expr を持つ
                                        ///<    (Expr::is_valid() == false)．
    const vector<Expr>& tristate_array, ///< [in] 出力のtristate条件の配列
                                        ///<  - 配列のサイズは output_num + inout_num
                                        ///<  - tristate にならない場合は定数0となる．
    const Expr& enable,                 ///< [in] マスターイネーブルの論理式
    const Expr& enable2,                ///< [in] スレーブイネーブルの論理式
                                        ///<  - single-stage latch の場合は定数0
    const Expr& data_in,                ///< [in] データ入力の論理式
                                        ///<  - invalid の場合もある．
    const Expr& clear,                  ///< [in] クリア条件の論理式
                                        ///<  - 定数0の場合もある．
    const Expr& preset,                 ///< [in] プリセット条件の論理式
                                        ///<  - 定数0の場合もある．
    ClibCPV clear_preset_var1,          ///< [in] クリアとプリセットが同時にアクティブになった時の値1
                                        ///<  - clear, preset が非0の時意味を持つ．
    ClibCPV clear_preset_var2           ///< [in] クリアとプリセットが同時にアクティブになった時の値2
                                        ///<  - clear, preset が非0の時意味を持つ．
  );
#endif

private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 論理セルグループの初期化を行なう．
  void
  logic_init();

  /// @brief FFグループの初期化を行なう．
  void
  ff_init();

  /// @brief ラッチグループの初期化を行なう．
  void
  latch_init();

  /// @brief 論理式から作られるシグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  _find_logic_group(
    const Expr& expr ///< [in] 論理式
  );

  /// @brief シグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  _find_group(
    const CgSignature& sig ///< [in] シグネチャ
  );

  /// @brief 代表クラスを得る．
  CiCellClass*
  _find_class(
    const CgSignature& sig ///< [in] シグネチャ
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリ
  CiCellLibrary& mLibrary;

  // シグネチャ文字列をキーにしてセルグループを保持する辞書
  unordered_map<string, CiCellGroup*> mGroupDict;

  // シグネチャ文字列をキーにしてセルクラスを保持する辞書
  unordered_map<string, CiCellClass*> mClassDict;

  // 論理セルグループ番号のリスト
  SizeType mLogicGroup[4];

};

END_NAMESPACE_YM_CLIB

#endif // CGMGR_H
