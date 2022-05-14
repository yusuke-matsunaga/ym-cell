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

  /// @brief FFクラス番号を得る．
  SizeType
  ff_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  ) const
  {
    SizeType idx;
    SizeType sub_idx;
    encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
    if ( idx < 6 ) {
      return mSimpleFFClass[idx];
    }
    else if ( idx == 6 ) {
      return mCpvFFClass[sub_idx];
    }
    else {
      return mCpvFFClass[sub_idx + 25];
    }
  }

  /// @brief ラッチクラス番号を得る．
  SizeType
  latch_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  ) const
  {
    SizeType idx;
    SizeType sub_idx;
    encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
    if ( idx < 6 ) {
      return mSimpleLatchClass[idx];
    }
    else if ( idx == 6 ) {
      return mCpvLatchClass[sub_idx];
    }
    else {
      return mCpvLatchClass[sub_idx + 25];
    }
  }

  /// @brief FF/ラッチの属性をエンコードする．
  static
  void
  encode_attr(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2,      ///< [in] clear_preset_var2 の値
    SizeType& idx,     ///< [out] メインインデックス
    SizeType& sub_idx  ///< [out] サブインデックス
  );


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

#if 0
  /// @brief 論理式から作られるシグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  _find_logic_group(
    const Expr& expr ///< [in] 論理式
  );

  /// @brief FFのシグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  _find_ff_group(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  );

  /// @brief ラッチのシグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  _find_latch_group(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  );
#endif

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

  // 単純なFFクラス番号のリスト
  SizeType mSimpleFFClass[6];

  // clear/preset 付きの単純なFFクラス番号のリスト
  SizeType mCpvFFClass[50];

  // 単純なラッチクラス番号のリスト
  SizeType mSimpleLatchClass[6];

  // clear/preset 付きの単純なラッチクラス番号のリスト
  SizeType mCpvLatchClass[50];

};

END_NAMESPACE_YM_CLIB

#endif // CGMGR_H
