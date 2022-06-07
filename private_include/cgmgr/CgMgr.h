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
#include "cgmgr/PatMgr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellClass;
class CiCellGroup;
class CiCell;
class CiSeqInfo;
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
    const CiSeqInfo& info ///< [in] clock/clear/preset 等の情報
  ) const;

  /// @brief ラッチクラス番号を得る．
  SizeType
  latch_class(
    const CiSeqInfo& info ///< [in] clock/clear/preset 等の情報
  ) const;

  /// @brief シグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  find_group(
    const CgSignature& sig ///< [in] シグネチャ
  );

  /// @brief 全ノード数を返す．
  SizeType
  pat_node_num() const;

  /// @brief ノードを返す．
  const PatNode&
  pat_node(
    SizeType pos ///< [in] ノード番号 ( 0 <= pos < node_num() )
  ) const;

  /// @brief パタン数を返す．
  SizeType
  pat_num() const;

  /// @brief パタンのノードリストを返す．
  void
  get_pat_info(
    SizeType id,                ///< [in] パタン番号 ( 0 <= id < pat_num() )
    SizeType& rep_id,           ///< [out] パタンの表す代表関数番号
    SizeType& input_num,        ///< [out] パタンの入力数
    vector<SizeType>& node_list ///< [out] パタンを DFS 順でたどった時のノード番号のリスト
  ) const;


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
  vector<SizeType> mSimpleFFClass;

  // 単純なラッチクラス番号のリスト
  vector<SizeType> mSimpleLatchClass;

  // 一時的にパタンを保持するクラス
  PatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB

#endif // CGMGR_H
