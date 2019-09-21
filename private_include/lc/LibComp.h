#ifndef LIBCOMP_H
#define LIBCOMP_H

/// @file LibComp.h
/// @brief LibComp のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
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
  LibComp();

  /// @brief デストラクタ
  ~LibComp();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief セルのグループ化，クラス化を行う．
  /// @param[in] cell_list セルのリスト
  void
  compile(const vector<CiCell*>& cell_list);

  /// @brief パタングラフの情報を取り出す．
  const LcPatMgr&
  pat_mgr() const;

  /// @brief グラフ構造全体の内容を表示する．
  /// @param[in] s 出力先のストリーム
  void
  display(ostream& s) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部の情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループの数を返す．
  int
  group_num() const;

  /// @brief セルグループを返す．
  /// @param[in] id セルグループ番号 ( 0 <= id < group_num() )
  LcGroup*
  group(int id) const;

  /// @brief NPN同値クラスの数を返す．
  int
  npn_class_num() const;

  /// @brief NPN同値クラスを返す．
  /// @param[in] id NPN同値クラス番号 ( 0 <= id < npn_class_num() )
  LcClass*
  npn_class(int id) const;

  /// @brief 定義済みの論理グループ番号を返す．
  /// @param[in] id 番号
  /// - 0: 定数0
  /// - 1: 定数1
  /// - 2: バッファ
  /// - 3: インバーター
  int
  logic_group(int id) const;

  /// @brief 定義済みのFFクラス番号を返す．
  /// @param[in] has_q Q端子の有無
  /// @param[in] has_xq 反転Q端子の有無
  /// @param[in] has_clear クリア端子の有無
  /// @param[in] has_preset プリセット端子の有無
  ///
  /// has_q == false && has_xq == false は不適
  int
  ff_class(bool has_q,
	   bool has_xq,
	   bool has_clear,
	   bool has_preset) const;

  /// @brief 定義済みのラッチクラス番号を返す．
  /// @param[in] has_q Q端子の有無
  /// @param[in] has_xq 反転Q端子の有無
  /// @param[in] has_clear クリア端子の有無
  /// @param[in] has_preset プリセット端子の有無
  ///
  /// has_q == false && has_xq == false は不適
  int
  latch_class(bool has_q,
	      bool has_xq,
	      bool has_clear,
	      bool has_preset);


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
  /// @param[in] cell セル
  void
  _add_cell(CiCell* cell);

  /// @brief シグネチャに対応する LcGroup を求める．
  /// @param[in] sig シグネチャ
  ///
  /// なければ新規に作る．
  LcGroup*
  _find_group(const LcSignature& sig);

  /// @brief 論理式に対応する LcGroup を求める．
  /// @param[in] expr 論理式
  ///
  /// こちらは1出力の論理セル用
  /// 内部で _reg_pat() を呼ぶ．
  LcGroup*
  _find_group(const Expr& expr);

  /// @brief 新しいグループを作る．
  LcGroup*
  _new_group();

  /// @brief 新しいクラスを作る．
  /// @param[in] rep_sig 代表シグネチャ
  LcClass*
  _new_class(const LcSignature& rep_sig);

  /// @brief 正規変換を求める．
  /// @param[in] sig シグネチャ
  /// @return 正規シグネチャへの変換マップを返す．
  NpnMapM
  _cannonical_map(const LcSignature& sig);

  /// @brief 同位体変換リストを求める．
  /// @param[in] sig シグネチャ
  /// @param[out] idmap_list 同位体変換のリスト
  void
  _find_idmap_list(const LcSignature& sig,
		  vector<NpnMapM>& idmap_list);

  /// @brief expr から生成されるパタンを登録する．
  /// @param[in] expr 論理式
  /// @param[in] fgroup expr の属している機能グループ
  void
  _reg_expr(const Expr& expr,
	    LcGroup* fgroup);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルグループのリスト
  // この配列上の位置とグループ番号は一致している．
  vector<LcGroup*> mGroupList;

  // シグネチャ文字列をキーとしてグループ番号を保持するハッシュ表
  unordered_map<string, int> mGroupMap;

  // NPN同値クラスのリスト
  // この配列上の位置とクラス番号は一致している．
  vector<LcClass*> mClassList;

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
