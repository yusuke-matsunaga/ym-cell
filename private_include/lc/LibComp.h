#ifndef LIBCOMP_H
#define LIBCOMP_H

/// @file LibComp.h
/// @brief LibComp のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "lc/LcPatMgr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCell;

END_NAMESPACE_YM_CLIB


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LibComp LibComp.h "LibComp.h"
/// @brief セルライブラリの情報を解析して等価グループに分類するクラス
//////////////////////////////////////////////////////////////////////
class LibComp
{
public:

  /// @brief コンストラクタ
  LibComp() = default;

  /// @brief デストラクタ
  ~LibComp() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief セルのグループ化，クラス化を行う．
  void
  compile(
    const vector<CiCell*>& cell_list ///< [in] セルのリスト
  );

  /// @brief パタングラフの情報を取り出す．
  const LcPatMgr&
  pat_mgr() const;

  /// @brief グラフ構造全体の内容を表示する．
  void
  display(
    ostream& s ///< [in] 出力先のストリーム
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部の情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループの数を返す．
  int
  group_num() const;

  /// @brief セルグループを返す．
  LcGroup*
  group(
    int id ///< [in] セルグループ番号 ( 0 <= id < group_num() )
  ) const;

  /// @brief NPN同値クラスの数を返す．
  int
  npn_class_num() const;

  /// @brief NPN同値クラスを返す．
  LcClass*
  npn_class(
    int id ///< [in] NPN同値クラス番号 ( 0 <= id < npn_class_num() )
  ) const;

  /// @brief 定義済みの論理グループ番号を返す．
  ///
  /// 番号の意味は以下の通り．
  /// - 0: 定数0
  /// - 1: 定数1
  /// - 2: バッファ
  /// - 3: インバーター
  int
  logic_group(
    int id ///< [in] 番号
  ) const;

  /// @brief 定義済みのFFクラス番号を返す．
  ///
  /// has_q == false && has_xq == false は不適
  int
  ff_class(
    bool has_q,     ///< [in] Q端子の有無
    bool has_xq,    ///< [in] 反転Q端子の有無
    bool has_clear, ///< [in] クリア端子の有無
    bool has_preset ///< [in] プリセット端子の有無
  ) const;

  /// @brief 定義済みのラッチクラス番号を返す．
  ///
  /// has_q == false && has_xq == false は不適
  int
  latch_class(
    bool has_q,     ///< [in] Q端子の有無
    bool has_xq,    ///< [in] 反転Q端子の有無
    bool has_clear, ///< [in] クリア端子の有無
    bool has_preset ///< [in] プリセット端子の有無
  );


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 論理セルの基本タイプを登録する．
  void
  _logic_init();

  /// @brief FFセルの基本タイプを登録する．
  void
  _ff_init();

  /// @brief ラッチセルの基本タイプを登録する．
  void
  _latch_init();

  /// @brief セルを追加する．
  void
  _add_cell(
    CiCell* cell ///< [in] セル
  );

  /// @brief シグネチャに対応する LcGroup を求める．
  ///
  /// なければ新規に作る．
  LcGroup*
  _find_group(
    const LcSignature& sig ///< [in] シグネチャ
  );

  /// @brief 論理式に対応する LcGroup を求める．
  ///
  /// こちらは1出力の論理セル用
  /// 内部で _reg_pat() を呼ぶ．
  LcGroup*
  _find_group(
    const Expr& expr ///< [in] 論理式
  );

  /// @brief 新しいグループを作る．
  LcGroup*
  _new_group();

  /// @brief 新しいクラスを作る．
  LcClass*
  _new_class(
    const LcSignature& rep_sig ///< [in] 代表シグネチャ
  );

  /// @brief 正規変換を求める．
  /// @return 正規シグネチャへの変換マップを返す．
  NpnMapM
  _cannonical_map(
    const LcSignature& sig ///< [in] シグネチャ
  );

  /// @brief 同位体変換リストを求める．
  vector<NpnMapM>
  _find_idmap_list(
    const LcSignature& sig ///< [in] シグネチャ
  );

  /// @brief expr から生成されるパタンを登録する．
  void
  _reg_expr(
    const Expr& expr, ///< [in] 論理式
    LcGroup* fgroup   ///< [in] expr の属している機能グループ
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルグループのリスト
  // この配列上の位置とグループ番号は一致している．
  vector<unique_ptr<LcGroup>> mGroupList;

  // シグネチャ文字列をキーとしてグループ番号を保持するハッシュ表
  unordered_map<string, int> mGroupMap;

  // NPN同値クラスのリスト
  // この配列上の位置とクラス番号は一致している．
  vector<unique_ptr<LcClass>> mClassList;

  // 代表シグネチャの文字列をキーとしてクラス番号を保持するハッシュ表
  unordered_map<string, int> mClassMap;

  // 定義済みの論理グループ
  int mLogicGroup[4];

  // 定義済みのFFクラス番号
  int mFFClass[12];

  // 定義済みのラッチクラス番号
  int mLatchClass[12];

  // パタングラフを管理するオブジェクト
  LcPatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LIBCOMP_H
