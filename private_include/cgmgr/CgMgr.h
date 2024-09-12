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
///
/// ClibCellLibrary の構築中に一時的に生成されるインスタンスなので
/// あまりメモリ効率は考えていない．
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

  /// @brief 論理セルグループを得る．
  const CiCellGroup*
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

  /// @brief FFクラスを得る．
  vector<const CiCellClass*>
  find_ff_class(
    ClibSeqAttr seq_attr ///< [in] 順序セルの属性
  ) const;

  /// @brief FFクラスの辞書を得る．
  const std::unordered_map<SizeType, vector<const CiCellClass*>>&
  ff_class_dict() const
  {
    return mFFClassDict;
  }

  /// @brief ラッチクラスを得る．
  vector<const CiCellClass*>
  find_latch_class(
    ClibSeqAttr seq_attr ///< [in] 順序セルの属性
  ) const;

  /// @brief ラッチクラスの辞書を得る．
  const std::unordered_map<SizeType, vector<const CiCellClass*>>&
  latch_class_dict() const
  {
    return mLatchClassDict;
  }

  /// @brief シグネチャに一致するグループを探す．
  /// @return グループを返す．
  ///
  /// なければ作る．
  CiCellGroup*
  find_group(
    const CgSignature& sig ///< [in] シグネチャ
  );

  /// @breif パタングラフを生成する．
  void
  gen_pat();

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
    SizeType id,                   ///< [in] パタン番号 ( 0 <= id < pat_num() )
    const CiCellClass*& rep_class, ///< [out] パタンの表す代表関数番号
    SizeType& input_num,           ///< [out] パタンの入力数
    vector<SizeType>& node_list    ///< [out] パタンを DFS 順でたどった時のノード番号のリスト
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

  // セルクラスと関係する論理式のリスト
  struct ClassExprList
  {
    CiCellClass* mClass;
    vector<Expr> mExprList;
  };

  // ライブラリ
  CiCellLibrary& mLibrary;

  // シグネチャ文字列をキーにしてグループを保持する辞書
  unordered_map<string, CiCellGroup*> mGroupDict;

  // シグネチャ文字列をキーにしてセルクラスを保持する辞書
  unordered_map<string, CiCellClass*> mClassDict;

  // セルクラスをキーにして論理式のリストを保持する辞書
  unordered_map<const CiCellClass*, vector<Expr>> mExprListDict;

  // 論理セルグループのリスト
  // 0: 定数0
  // 1: 定数1
  // 2: バッファ
  // 3: インバータ
  const CiCellGroup* mLogicGroup[4];

  // FFセルクラスのリストを持つ辞書
  // キーは ClibSeqAttr::index()
  std::unordered_map<SizeType, vector<const CiCellClass*>> mFFClassDict;

  // ラッチセルクラスのリストを持つ辞書
  // キーは ClibSeqAttr::index()
  std::unordered_map<SizeType, vector<const CiCellClass*>> mLatchClassDict;

  // 一時的にパタンを保持するクラス
  PatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB

#endif // CGMGR_H
