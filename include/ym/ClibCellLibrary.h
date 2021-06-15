#ifndef YM_CLIBCELLLIBRARY_H
#define YM_CLIBCELLLIBRARY_H

/// @file ym/ClibCellLibrary.h
/// @brief ClibCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellLibrary ClibCellLibrary.h "ym/ClibCellLibrary.h"
/// @brief セルライブラリを表すクラス
///
/// 実際には実体の CiCellLibrary へのスマートポインタとなっている．
/// アプリケーション側では CiCellLibrary のメモリ管理について気にする
/// 必要はない．
//////////////////////////////////////////////////////////////////////
class ClibCellLibrary
{
public:

  /// @brief コンストラクタ
  ///
  /// 空の状態で初期化される．
  ClibCellLibrary();

  /// @brief コピーコンストラクタ
  ///
  /// '浅い'コピーを行う．
  ClibCellLibrary(const ClibCellLibrary& src); ///< [in] コピー元のオブジェクト

  /// @brief 代入演算子
  const ClibCellLibrary&
  operator=(const ClibCellLibrary& src); ///< [in] コピー元のオブジェクト

  /// @brief デストラクタ
  ~ClibCellLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_mislib(const string& filename); ///< [in] ファイル名

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_mislib(const char* filename) ///< [in] ファイル名
  {
    return read_mislib(string(filename));
  }

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_liberty(const string& filename); ///< [in] ファイル名

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_liberty(const char* filename) ///< [in] ファイル名
  {
    return read_liberty(string(filename));
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief テクノロジの取得
  /// 返り値は
  /// - Cmos
  /// - Fpga
  /// のどちらか
  ClibTechnology
  technology() const;

  /// @brief 遅延モデルの取得
  /// 返り値は
  /// - GenericCmos
  /// - TableLookup
  /// - PiecewiseCmos
  /// - Cmos2
  /// - Dcm
  /// のいずれか
  ClibDelayModel
  delay_model() const;

  /// @brief バス命名規則の取得
  string
  bus_naming_style() const;

  /// @brief 日付情報の取得
  string
  date() const;

  /// @brief リビジョン情報の取得
  string
  revision() const;

  /// @brief コメント情報の取得
  string
  comment() const;

  /// @brief 時間単位の取得
  string
  time_unit() const;

  /// @brief 電圧単位の取得
  string
  voltage_unit() const;

  /// @brief 電流単位の取得
  string
  current_unit() const;

  /// @brief 抵抗単位の取得
  string
  pulling_resistance_unit() const;

  /// @brief 容量単位の取得
  ///
  /// なぜかここだけインターフェイスが異なる．
  double
  capacitive_load_unit() const;

  /// @brief 容量単位文字列の取得
  ///
  /// なぜかここだけインターフェイスが異なる．
  string
  capacitive_load_unit_str() const;

  /// @brief 電力単位の取得
  string
  leakage_power_unit() const;

  /// @brief 遅延テーブルのテンプレートのリストの取得
  const ClibLutTemplateList&
  lu_table_template_list() const;

  /// @brief 遅延テーブルのテンプレート数の取得
  int
  lu_table_template_num() const;

  /// @brief 遅延テーブルのテンプレート番号の取得
  const ClibLutTemplate&
  lu_table_template(int table_id) const; ///< [in] テンプレート番号 ( 0 <= table_id < lu_table_template_num() )

  /// @brief 遅延テーブルのテンプレート番号の取得
  ///
  /// なければ -1 を返す．
  int
  lu_table_template_id(const char* name) const; ///< [in] テンプレート名

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(const char* name) const; ///< [in] バスタイプ名


public:
  //////////////////////////////////////////////////////////////////////
  // セル情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief このライブラリの持つセルのリストの取得
  const ClibCellList&
  cell_list() const;

  /// @brief このライブラリの持つセル数の取得
  int
  cell_num() const;

  /// @brief セル情報の取得
  /// @return 該当するセル情報を返す．
  const ClibCell&
  cell(int cell_id) const; ///< [in] セル番号 ( 0 <= cell_id < cell_num() )

  /// @brief 名前からのセル番号の取得
  /// @return セル番号を返す．
  ///
  /// なければ -1 を返す．
  int
  cell_id(const char* name) const; ///< [in] セル名

  /// @brief 名前からのセル番号の取得
  /// @return セル番号を返す．
  ///
  /// なければ -1 を返す．
  int
  cell_id(const string& name) const; ///< [in] セル名

  /// @brief セルグループのリストを返す．
  const ClibCellGroupList&
  group_list() const;

  /// @brief NPN同値クラスのリストを返す．
  const ClibCellClassList&
  npn_class_list() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 論理セルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数0セルのグループを返す．
  const ClibCellGroup&
  const0_func() const;

  /// @brief 定数1セルのグループを返す．
  const ClibCellGroup&
  const1_func() const;

  /// @brief バッファセルのグループを返す．
  const ClibCellGroup&
  buf_func() const;

  /// @brief インバータセルのグループを返す．
  const ClibCellGroup&
  inv_func() const;


public:
  //////////////////////////////////////////////////////////////////////
  // FFセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のFFクラスを返す．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass&
  simple_ff_class(bool has_clear,         ///< [in] クリア端子を持つとき true にする．
		  bool has_preset) const; ///< [in] プリセット端子を持つとき true にする．


public:
  //////////////////////////////////////////////////////////////////////
  // ラッチセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のラッチクラスを返す．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass&
  simple_latch_class(bool has_clear,         ///< [in] クリア端子を持つとき true にする．
		     bool has_preset) const; ///< [in] プリセット端子を持つとき true にする．


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 総パタン数を返す．
  int
  pg_pat_num() const;

  /// @brief パタンを返す．
  const ClibPatGraph&
  pg_pat(int id) const; ///< [in] パタン番号 ( 0 <= id < pg_pat_num() )

  /// @brief パタンの最大の入力数を得る．
  int
  pg_max_input() const;

  /// @brief 総ノード数を返す．
  int
  pg_node_num() const;

  /// @brief ノードの種類を返す．
  ClibPatType
  pg_node_type(int id) const; ///< [in] ノード番号 ( 0 <= id < pg_node_num() )

  /// @brief ノードが入力ノードの時に入力番号を返す．
  ///
  /// 入力ノードでない場合の返り値は不定
  int
  pg_input_id(int id) const; ///< [in] ノード番号 ( 0 <= id < pg_node_num() )

  /// @brief 入力のノード番号を返す．
  /// @return input_id の入力に対応するノードのノード番号
  int
  pg_input_node(int input_id) const; ///< [in] 入力番号 ( 0 <= input_id < pg_input_num() )

  /// @brief 総枝数を返す．
  int
  pg_edge_num() const;

  /// @brief 枝のファンイン元のノード番号を返す．
  int
  pg_edge_from(int id) const; ///< [in] 枝番号 ( 0 <= id < edge_num() )

  /// @brief 枝のファンアウト先のノード番号を返す．
  int
  pg_edge_to(int id) const; ///< [in] 枝番号 ( 0 <= id < edge_num() )

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  int
  pg_edge_pos(int id) const; ///< [in] 枝番号 ( 0 <= id < edge_num() )

  /// @brief 枝の反転属性を返す．
  bool
  pg_edge_inv(int id) const; ///< [in] 枝番号 ( 0 <= id < edge_num() )


public:
  //////////////////////////////////////////////////////////////////////
  // ダンプ/リストア関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(ostream& s) const; ///< [in] 出力先のストリーム

  /// @brief バイナリダンプされた内容を読み込む．
  void
  restore(istream& s); ///< [in] 入力元のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mImpl を切り替える．
  ///
  /// CiCellLibrary の参照回数を適切に管理する．
  /// mImpl はこの関数以外では変更しない．
  void
  change_impl(CiCellLibrary* new_impl); ///< [in] 新しいオブジェクト


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 実装クラス
  CiCellLibrary* mImpl;

};

/// @relates ClibCellLibrary
/// @brief 内容を出力する．
void
display_library(ostream& s,                      ///< [in] 出力先のストリーム
		const ClibCellLibrary& library); ///< [in] 対象のセルライブラリ

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLLIBRARY_H
