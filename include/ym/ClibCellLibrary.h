#ifndef YM_CLIBCELLLIBRARY_H
#define YM_CLIBCELLLIBRARY_H

/// @file ym/ClibCellLibrary.h
/// @brief ClibCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/IDO.h"
#include "ym/ODO.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellLibrary ClibCellLibrary.h "ym/ClibCellLibrary.h"
/// @brief セルライブラリを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibCellLibrary
{
public:

  /// @brief コンストラクタ
  ///
  /// 空の状態で初期化される．
  ClibCellLibrary();

  /// @brief コピーコンストラクタ
  /// @param[in] src コピー元のオブジェクト
  ///
  /// '浅い'コピーを行う．
  ClibCellLibrary(const ClibCellLibrary& src);

  /// @brief 代入演算子
  /// @param[in] src コピー元のオブジェクト
  const ClibCellLibrary&
  operator=(const ClibCellLibrary& src);

  /// @brief デストラクタ
  ~ClibCellLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @return 読み込みが成功したら true を返す．
  bool
  read_mislib(const string& filename);

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @return 読み込みが成功したら true を返す．
  bool
  read_mislib(const char* filename);

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @return 読み込みが成功したら true を返す．
  bool
  read_liberty(const string& filename);

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @return 読み込みが成功したら true を返す．
  bool
  read_liberty(const char* filename);


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief テクノロジの取得
  /// 返り値は
  /// - kTechCmos
  /// - kTechFpga
  /// のどちらか
  ClibTechnology
  technology() const;

  /// @brief 遅延モデルの取得
  /// 返り値は
  /// - kClibDelayGenericCmos
  /// - kClibDelayTableLookup
  /// - kClibDelayPiecewiseCmos
  /// - kClibDelayCmos2
  /// - kClibDelayDcm
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
  ymuint
  lu_table_template_num() const;

  /// @brief 遅延テーブルのテンプレートの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < lu_table_template_num() )
  const ClibLutTemplate*
  lu_table_template(ymuint pos) const;

  /// @brief 遅延テーブルのテンプレートの取得
  /// @param[in] name テンプレート名
  ///
  /// なければ nullptr を返す．
  const ClibLutTemplate*
  lu_table_template(const char* name) const;

  /// @brief バスタイプの取得
  /// @param[in] name バスタイプ名
  ///
  /// なければ nullptr を返す．
  const ClibBusType*
  bus_type(const char* name) const;


public:
  //////////////////////////////////////////////////////////////////////
  // セル情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief このライブラリの持つセル数の取得
  ymuint
  cell_num() const;

  /// @brief セルの取得
  /// @param[in] pos 位置番号( 0 <= pos < cell_num() )
  const ClibCell*
  cell(ymuint pos) const;

  /// @brief 名前からのセルの取得
  const ClibCell*
  cell(const char* name) const;

  /// @brief 名前からのセルの取得
  const ClibCell*
  cell(const string& name) const;

  /// @brief セルグループの個数を返す．
  ymuint
  group_num() const;

  /// @brief セルグループを返す．
  /// @param[in] id グループ番号　( 0 <= id < group_num() )
  const ClibCellGroup*
  group(ymuint id) const;

  /// @brief NPN同値クラスの個数を返す．
  ymuint
  npn_class_num() const;

  /// @brief NPN同値クラスを返す．
  /// @param[in] id クラス番号 ( 0 <= id < npn_class_num() )
  const ClibCellClass*
  npn_class(ymuint id) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 論理セルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数0セルのグループを返す．
  const ClibCellGroup*
  const0_func() const;

  /// @brief 定数1セルのグループを返す．
  const ClibCellGroup*
  const1_func() const;

  /// @brief バッファセルのグループを返す．
  const ClibCellGroup*
  buf_func() const;

  /// @brief インバータセルのグループを返す．
  const ClibCellGroup*
  inv_func() const;


public:
  //////////////////////////////////////////////////////////////////////
  // FFセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のFFクラスを返す．
  /// @param[in] has_clear クリア端子を持つとき true にする．
  /// @param[in] has_preset プリセット端子を持つとき true にする．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass*
  simple_ff_class(bool has_clear,
		  bool has_preset) const;


public:
  //////////////////////////////////////////////////////////////////////
  // ラッチセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のラッチクラスを返す．
  /// @param[in] has_clear クリア端子を持つとき true にする．
  /// @param[in] has_preset プリセット端子を持つとき true にする．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass*
  simple_latch_class(bool has_clear,
		     bool has_preset) const;


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 総パタン数を返す．
  ymuint
  pg_pat_num() const;

  /// @brief パタンを返す．
  /// @param[in] id パタン番号 ( 0 <= id < pg_pat_num() )
  const ClibPatGraph&
  pg_pat(ymuint id) const;

  /// @brief パタンの最大の入力数を得る．
  ymuint
  pg_max_input() const;

  /// @brief 総ノード数を返す．
  ymuint
  pg_node_num() const;

  /// @brief ノードの種類を返す．
  /// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
  ClibPatType
  pg_node_type(ymuint id) const;

  /// @brief ノードが入力ノードの時に入力番号を返す．
  /// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
  ///
  /// 入力ノードでない場合の返り値は不定
  ymuint
  pg_input_id(ymuint id) const;

  /// @brief 入力のノード番号を返す．
  /// @param[in] input_id 入力番号 ( 0 <= input_id < pg_input_num() )
  /// @return input_id の入力に対応するノードのノード番号
  ymuint
  pg_input_node(ymuint input_id) const;

  /// @brief 総枝数を返す．
  ymuint
  pg_edge_num() const;

  /// @brief 枝のファンイン元のノード番号を返す．
  /// @param[in] id 枝番号 ( 0 <= id < edge_num() )
  ymuint
  pg_edge_from(ymuint id) const;

  /// @brief 枝のファンアウト先のノード番号を返す．
  /// @param[in] id 枝番号 ( 0 <= id < edge_num() )
  ymuint
  pg_edge_to(ymuint id) const;

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  /// @param[in] id 枝番号 ( 0 <= id < edge_num() )
  ymuint
  pg_edge_pos(ymuint id) const;

  /// @brief 枝の反転属性を返す．
  /// @param[in] id 枝番号 ( 0 <= id < edge_num() )
  bool
  pg_edge_inv(ymuint id) const;


public:
  //////////////////////////////////////////////////////////////////////
  // ダンプ/リストア関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  void
  dump(ODO& s) const;

  /// @brief バイナリダンプされた内容を読み込む．
  /// @param[in] s 入力元のストリーム
  void
  restore(IDO& s);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mImpl を切り替える．
  /// @param[in] new_impl 新しいオブジェクト
  ///
  /// CiCellLibrary の参照回数を適切に管理する．
  /// mImpl はこの関数以外では変更しない．
  void
  change_impl(CiCellLibrary* new_impl);


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
display_library(ostream& s,
		const ClibCellLibrary& library);

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCELLLIBRARY_H
