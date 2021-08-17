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
  ClibCellLibrary() = default;

  /// @brief コピーコンストラクタ
  ///
  /// '浅い'コピーを行う．
  ClibCellLibrary(
    const ClibCellLibrary& src ///< [in] コピー元のオブジェクト
  );

  /// @brief 代入演算子
  /// @return 代入後の自身への参照を返す．
  ClibCellLibrary&
  operator=(
    const ClibCellLibrary& src ///< [in] コピー元のオブジェクト
  );

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
  read_mislib(
    const string& filename ///< [in] ファイル名
  );

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_mislib(
    const char* filename ///< [in] ファイル名
  )
  {
    return read_mislib(string(filename));
  }

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_liberty(
    const string& filename ///< [in] ファイル名
  );

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  ///
  /// 読み込みが失敗した場合はなにもしないで false を返す．
  bool
  read_liberty(
    const char* filename ///< [in] ファイル名
  )
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
  ///
  /// 返り値は
  /// - cmos
  /// - fpga
  /// のどちらか
  ClibTechnology
  technology() const;

  /// @brief 遅延モデルの取得
  ///
  /// 返り値は
  /// - generic_cmos
  /// - table_lookup
  /// - piecewise_cmos
  /// - cmos2
  /// - dcm
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

  /// @brief 遅延テーブルのテンプレート数の取得
  SizeType
  lu_table_template_num() const;

  /// @brief 遅延テーブルのテンプレートの取得
  const ClibLutTemplate&
  lu_table_template(
    SizeType table_id ///< [in] テンプレート番号 ( 0 <= table_id < lu_table_template_num() )
  ) const;

  /// @brief 遅延テーブルのテンプレート番号の取得
  ///
  /// なければ -1 を返す．
  SizeType
  lu_table_template_id(
    const char* name ///< [in] テンプレート名
  ) const;

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const char* name ///< [in] バスタイプ名
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // セル情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief このライブラリの持つセル数の取得
  SizeType
  cell_num() const;

  /// @brief セル情報の取得
  /// @return 該当するセル情報を返す．
  const ClibCell&
  cell(
    SizeType cell_id ///< [in] セル番号 ( 0 <= cell_id < cell_num() )
  ) const;

  /// @brief 名前からのセル番号の取得
  /// @return セル番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  cell_id(
    const char* name ///< [in] セル名
  ) const;

  /// @brief 名前からのセル番号の取得
  /// @return セル番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  cell_id(
    const string& name ///< [in] セル名
  ) const
  {
    return cell_id(name.c_str());
  }

  /// @brief セルグループ数の取得
  SizeType
  cell_group_num() const;

  /// @brief セルグループの取得
  const ClibCellGroup&
  cell_group(
    SizeType id ///< [in] グループ番号 ( 0 <= id < cell_group_num() )
  ) const;

  /// @brief NPN同値クラス数の取得
  SizeType
  npn_class_num() const;

  /// @brief NPN同値クラスの取得
  const ClibCellClass&
  npn_class(
    SizeType id ///< [in] 同値クラス番号 ( 0 <= id < npn_class_num() )
  ) const;


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
  simple_ff_class(
    bool has_clear, ///< [in] クリア端子を持つとき true にする．
    bool has_preset ///< [in] プリセット端子を持つとき true にする．
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // ラッチセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のラッチクラスを返す．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass&
  simple_latch_class(
    bool has_clear, ///< [in] クリア端子を持つとき true にする．
    bool has_preset ///< [in] プリセット端子を持つとき true にする．
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 総パタン数を返す．
  SizeType
  pg_pat_num() const;

  /// @brief パタンを返す．
  const ClibPatGraph&
  pg_pat(
    SizeType id ///< [in] パタン番号 ( 0 <= id < pg_pat_num() )
  ) const;

  /// @brief パタンの最大の入力数を得る．
  SizeType
  pg_max_input() const;

  /// @brief 総ノード数を返す．
  SizeType
  pg_node_num() const;

  /// @brief ノードの種類を返す．
  ClibPatType
  pg_node_type(
    SizeType id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const;

  /// @brief ノードが入力ノードの時に入力番号を返す．
  ///
  /// 入力ノードでない場合の返り値は不定
  SizeType
  pg_input_id(
    SizeType id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const;

  /// @brief 入力のノード番号を返す．
  /// @return input_id の入力に対応するノードのノード番号
  SizeType
  pg_input_node(
    SizeType input_id ///< [in] 入力番号 ( 0 <= input_id < pg_input_num() )
  ) const;

  /// @brief 総枝数を返す．
  SizeType
  pg_edge_num() const;

  /// @brief 枝のファンイン元のノード番号を返す．
  SizeType
  pg_edge_from(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const;

  /// @brief 枝のファンアウト先のノード番号を返す．
  SizeType
  pg_edge_to(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const;

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  SizeType
  pg_edge_pos(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const;

  /// @brief 枝の反転属性を返す．
  /// @retval true 反転あり
  /// @retval false 反転なし
  bool
  pg_edge_inv(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // ダンプ/リストア関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const;

  /// @brief バイナリダンプされた内容を読み込む．
  void
  restore(
    istream& s ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mImpl を切り替える．
  ///
  /// CiCellLibrary の参照回数を適切に管理する．
  /// mImpl はこの関数以外では変更しない．
  void
  change_impl(
    CiCellLibrary* new_impl ///< [in] 新しいオブジェクト
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 実装クラス
  CiCellLibrary* mImpl{nullptr};

};

/// @relates ClibCellLibrary
/// @brief 内容を出力する．
void
display_library(
  ostream& s,                    ///< [in] 出力先のストリーム
  const ClibCellLibrary& library ///< [in] 対象のセルライブラリ
);

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLLIBRARY_H
