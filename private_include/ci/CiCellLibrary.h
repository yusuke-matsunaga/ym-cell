#ifndef CICELLLIBRARY_H
#define CICELLLIBRARY_H

/// @file CiCellLibrary.h
/// @brief CiCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellLibrary.h"
#include "ym/ClibArea.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibObjList.h"
#include "ym/ClibResistance.h"
#include "ym/ClibTiming.h"
#include "ym/ClibCellPin.h"
#include "ym/ShString.h"
#include "ym/Expr.h"
#include "CiLutHash.h"
#include "CiCellHash.h"
#include "CiCellPin.h"
#include "CiCellPinHash.h"
#include "CiPatMgr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellClass;
class CiCellGroup;
class CiLutTemplate;
class CiCell;
class CiBus;
class CiBundle;
class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @class CiCellLibrary CiCellLibrary.h "CiCellLibrary.h"
/// @brief ClibCellLibrary の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellLibrary :
  public ClibCellLibrary
{
public:

  /// @brief コンストラクタ
  CiCellLibrary();

  /// @brief デストラクタ
  ~CiCellLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  bool
  read_mislib(
    const string& filename ///< [in] ファイル名
  );

  /// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
  /// @return 読み込みが成功したら true を返す．
  bool
  read_liberty(
    const string& filename ///< [in] ファイル名
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief テクノロジの取得
  ///
  /// このクラスは常に ClibTechnology::cmos を返す．
  ClibTechnology
  technology() const;

  /// @brief 遅延モデルの取得
  /// 返り値は
  /// - ClibDelay::generic_cmos
  /// - ClibDelay::piecewise_cmos
  /// - ClibDelay::table_lookup
  /// - ClibDelay::cmos2
  /// - ClibDelay::dcm
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
  double
  capacitive_load_unit() const;

  /// @brief 容量単位文字列の取得
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
  lu_table_template(
    int table_id ///< [in] テンプレート番号 ( 0 <= table_id < lu_table_template_num() )
  ) const;

#if 0
  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ -1 を返す．
  int
  lu_table_template_id(
    const char* name ///< [in] テンプレート名
  ) const;

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ -1 を返す．
  int
  lu_table_template_id(
    const string& name ///< [in] テンプレート名
  ) const;

  /// @brief ルックアップテーブルのテンプレート番号の取得
  /// @param[in] name
  ///
  /// なければ -1 を返す．
  int
  lu_table_template_id(
    const ShString& name ///< [in] テンプレート名
  ) const;
#endif

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const char* name ///< [in] バスタイプ名
  ) const;

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const string& name ///< [in] バスタイプ名
  ) const;

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const ShString& name ///< [in] バスタイプ名
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // セル情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief このライブラリの持つセルのリストの取得
  const ClibCellList&
  cell_list() const;

  /// @brief 名前からのセル番号の取得
  int
  cell_id(
    const char* name ///< [in] セル名
  ) const;

  /// @brief 名前からのセル番号の取得
  int
  cell_id(
    const string& name ///< [in] セル名
  ) const;

  /// @brief 名前からのセル番号の取得
  int
  cell_id(
    const ShString& name ///< [in] セル名
  ) const;

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
  int
  pg_pat_num() const;

  /// @brief パタンを返す．
  const ClibPatGraph&
  pg_pat(
    int id ///< [in] パタン番号 ( 0 <= id < pg_pat_num() )
  ) const;

  /// @brief パタンの最大の入力数を得る．
  int
  pg_max_input() const;

  /// @brief 総ノード数を返す．
  int
  pg_node_num() const;

  /// @brief ノードの種類を返す．
  ClibPatType
  pg_node_type(
    int id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const;

  /// @brief ノードが入力ノードの時に入力番号を返す．
  ///
  /// 入力ノードでない場合の返り値は不定
  int
  pg_input_id(
    int id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const;

  /// @brief 入力のノード番号を返す．
  /// @return input_id の入力に対応するノードのノード番号
  int
  pg_input_node(
    int input_id ///< [in] 入力番号 ( 0 <= input_id < pg_input_num() )
  ) const;

  /// @brief 総枝数を返す．
  int
  pg_edge_num() const;

  /// @brief 枝のファンイン元のノード番号を返す．
  int
  pg_edge_from(
    int id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const;

  /// @brief 枝のファンアウト先のノード番号を返す．
  int
  pg_edge_to(
    int id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const;

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  int
  pg_edge_pos(
    int id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const;

  /// @brief 枝の反転属性を返す．
  bool
  pg_edge_inv(
    int id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
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


public:
  //////////////////////////////////////////////////////////////////////
  // 情報設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を設定する．
  void
  set_name(
    const string& name ///< [in] 名前
  );

  /// @brief 'technology' を設定する．
  void
  set_technology(
    ClibTechnology technology ///< [in] テクノロジ
  );

  /// @brief 遅延モデルを設定する．
  void
  set_delay_model(
    ClibDelayModel delay_model ///< [in] 遅延モデル．
  );

  /// @brief 'capacitive_load_unit' を設定する．
  void
  set_capacitive_load_unit(
    double unit,       ///< [in] 単位
    const string& ustr ///< [in] 単位の後に表示する文字列
  );

  /// @brief 属性を設定する(浮動小数点型)
  void
  set_attr(
    const string& attr_name, ///< [in] 属性名
    double value             ///< [in] 値
  );

  /// @brief 属性を設定する(文字列型)．
  void
  set_attr(
    const string& attr_name, ///< [in] 属性名
    const string& value      ///< [in] 値
  );

  /// @brief 遅延テーブルのテンプレートのリストを設定する．
  void
  set_lu_table_template_list(
    const vector<CiLutTemplate*>& template_list ///< [in] テンプレートのリスト
  );

  /// @brief 1次元の LUT のテンプレートを作る．
  CiLutTemplate*
  new_lut_template1(
    const ShString& name,             ///< [in] 名前
    ClibVarType var_type1,            ///< [in] 変数型
    const vector<double>& index_list1 ///< [in] インデックス値のリスト
  );

  /// @brief 2次元の LUT のテンプレートを作る．
  CiLutTemplate*
  new_lut_template2(
    const ShString& name,              ///< [in] 名前
    ClibVarType var_type1,             ///< [in] 変数型
    const vector<double>& index_list1, ///< [in] インデックス値のリスト
    ClibVarType var_type2,             ///< [in] 変数型
    const vector<double>& index_list2  ///< [in] インデックス値のリスト
  );

  /// @brief 3次元の LUT のテンプレートを作る．
  CiLutTemplate*
  new_lut_template3(
    const ShString& name,              ///< [in] 名前
    ClibVarType var_type1,             ///< [in] 変数型
    const vector<double>& index_list1, ///< [in] インデックス値のリスト
    ClibVarType var_type2,             ///< [in] 変数型
    const vector<double>& index_list2, ///< [in] インデックス値のリスト
    ClibVarType var_type3,             ///< [in] 変数型
    const vector<double>& index_list3  ///< [in] インデックス値のリスト
  );

  /// @brief セルのリストを設定する．
  /// @param[in] cell_list
  /// @param[in] do_compile
  ///
  /// restore() 時には compile() を実行する必要はない．
  void
  set_cell_list(
    const vector<CiCell*>& cell_list, ///< [in] セルのリスト
    bool do_compile = true            ///< [in] compile() を実行する時 true にするフラグ
  );

  /// @brief 論理セルを生成する．
  CiCell*
  new_logic_cell(
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,          ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list     ///< [in] タイミング情報のリスト
  );

  /// @brief FFセルを生成する．
  CiCell*
  new_ff_cell(
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& next_state,                  ///< [in] "next_state" 関数の式
    const Expr& clocked_on,                  ///< [in] "clocked_on" 関数の式
    const Expr& clocked_on_also,             ///< [in] "clocked_on_also" 関数の式
    const Expr& clear,                       ///< [in] "clear" 関数の式
    const Expr& preset,                      ///< [in] "preset" 関数の式
    int clear_preset_var1,                   ///< [in] clear と preset が同時にオンになったときの値1
    int clear_preset_var2                    ///< [in] clear と preset が同時にオンになったときの値2
  );

  /// @brief ラッチセルを生成する．
  CiCell*
  new_latch_cell(
    const ShString& name,                    ///< [in] 名前
    ClibArea area,			     ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,	     ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
    const Expr& data_in,                     ///< [in] "data_in" 関数の式
    const Expr& enable,                      ///< [in] "enable" 関数の式
    const Expr& enable_also,                 ///< [in] "enable_also" 関数の式
    const Expr& clear,                       ///< [in] "clear" 関数の式
    const Expr& preset,                      ///< [in] "preset" 関数の式
    int clear_preset_var1,                   ///< [in] clear と preset が同時にオンになったときの値1
    int clear_preset_var2                    ///< [in] clear と preset が同時にオンになったときの値2
  );

  /// @brief FSMセルを生成する．
  CiCell*
  new_fsm_cell(
    const ShString& name,                        ///< [in] 名前
    ClibArea area,				 ///< [in] 面積
    const vector<CiInputPin*>& input_list,	 ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list,	 ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,	 ///< [in] 入出力ピンのリスト
    const vector<CiInternalPin*>& internal_list, ///< [in] 内部ピンのリスト
    const vector<CiBus*>& bus_list,		 ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,	 ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list	 ///< [in] タイミング情報のリスト
  );

  /// @brief セルの入力ピンを生成する．
  CiInputPin*
  new_cell_input(
    const ShString& name,             ///< [in] 入力ピン名
    ClibCapacitance capacitance,      ///< [in] 入力ピンの負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 入力ピンの立ち上がり負荷容量
    ClibCapacitance fall_capacitance  ///< [in] 入力ピンの立ち下がり負荷容量
  );

  /// @brief セルの出力ピンの内容を設定する．
  CiOutputPin*
  new_cell_output(
    const ShString& name,            ///< [in] 出力ピン名
    bool has_logic,                  ///< [in] 出力の論理式を持つ時に true となるフラグ
    const Expr& logic_expr,          ///< [in] 出力の論理式
    const Expr& tristate_expr,       ///< [in] トライステート条件の論理式
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最小負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition          ///< [in] 最小遷移時間
  );

  /// @brief セルの入出力ピンの内容を設定する．
  CiInoutPin*
  new_cell_inout(
    const ShString& name,             ///< [in] 入出力ピン名
    bool has_logic,                   ///< [in] 出力の論理式を持つ時に true となるフラグ
    const Expr& logic_expr,           ///< [in] 出力の論理式
    const Expr& tristate_expr,        ///< [in] トライステート条件の論理式
    ClibCapacitance capacitance,      ///< [in] 入力ピンの負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 入力ピンの立ち上がり負荷容量
    ClibCapacitance fall_capacitance, ///< [in] 入力ピンの立ち下がり負荷容量
    ClibCapacitance max_fanout,       ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,       ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance,  ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance,  ///< [in] 最小負荷容量
    ClibTime max_transition,          ///< [in] 最大遷移時間
    ClibTime min_transition           ///< [in] 最小遷移時間
  );

  /// @brief セルの内部ピンを生成する．
  CiInternalPin*
  new_cell_internal(
    const ShString& name ///< [in] 内部ピン名
  );

  /// @brief タイミング情報を作る(ジェネリック遅延モデル)．
  CiTiming*
  new_timing_generic(
    ClibTimingType type,            ///< [in] タイミングの型
    const Expr& cond,               ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,        ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,        ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,            ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall,            ///< [in] 立ち下がりスロープ遅延
    ClibResistance rise_resistance, ///< [in] 立ち上がり負荷依存係数
    ClibResistance fall_resistance  ///< [in] 立ち下がり負荷依存係数
  );

  /// @brief タイミング情報を作る(折れ線近似)．
  CiTiming*
  new_timing_piecewise(
    ClibTimingType timing_type,         ///< [in] タイミングの型
    const Expr& cond,                   ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,            ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,            ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,                ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall,                ///< [in] 立ち下がりスロープ遅延
    ClibResistance rise_pin_resistance, ///< [in] 立ち上がりピン抵抗
    ClibResistance fall_pin_resistance  ///< [in] 立ち下がりピン抵抗
  );

  /// @brief タイミング情報を作る(非線形タイプ1)．
  CiTiming*
  new_timing_lut1(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    ClibLut* cell_rise,         ///< [in] 立ち上がりセル遅延テーブル
    ClibLut* cell_fall,         ///< [in] 立ち下がりセル遅延テーブル
    ClibLut* rise_transition,   ///< [in] 立ち上がり遷移テーブル
    ClibLut* fall_transition    ///< [in] 立ち下がり遷移テーブル
  );

  /// @brief タイミング情報を作る(非線形タイプ2)．
  CiTiming*
  new_timing_lut2(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    ClibLut* rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    ClibLut* fall_transition,   ///< [in] 立ち下がり遷移遅延テーブル
    ClibLut* rise_propagation,  ///< [in] 立ち上がり伝搬遅延テーブル
    ClibLut* fall_propagation   ///< [in] 立ち下がり伝搬遅延テーブル
  );

  /// @brief タイミング情報をセットする．
  void
  set_timing(
    CiCell* cell,                        ///< [in] セル
    int input_id,                        ///< [in] 入力ピンID
    int output_id,                       ///< [in] 出力ピンID
    ClibTimingSense timing_sense,        ///< [in] タイミングセンス
    const vector<CiTiming*>& timing_list ///< [in] タイミング情報のリスト
  );

  /// @brief 1次元の LUT を作る．
  ClibLut*
  new_lut1(
    const ClibLutTemplate* lut_template,                 ///< [in] テンプレート
    const vector<double>& value_array,                   ///< [in] 値の配列
    const vector<double>& index_array = vector<double>{} ///< [in] インデックス値のリスト
  );

  /// @brief 2次元の LUT を作る．
  ClibLut*
  new_lut2(
    const ClibLutTemplate* lut_template,                   ///< [in] テンプレート
    const vector<double>& value_array,                     ///< [in] 値の配列
    const vector<double>& index_array1 = vector<double>{}, ///< [in] インデックス値のリスト
    const vector<double>& index_array2 = vector<double>{}  ///< [in] インデックス値のリスト
  );

  /// @brief 3次元の LUT を作る．
  ClibLut*
  new_lut3(
    const ClibLutTemplate* lut_template,                   ///< [in] テンプレート
    const vector<double>& value_array,                     ///< [in] 値の配列
    const vector<double>& index_array1 = vector<double>{}, ///< [in] インデックス値のリスト
    const vector<double>& index_array2 = vector<double>{}, ///< [in] インデックス値のリスト
    const vector<double>& index_array3 = vector<double>{}  ///< [in] インデックス値のリスト
  );


public:
  //////////////////////////////////////////////////////////////////////
  // デフォルト(エラーフォールバック)のオブジェクト
  //////////////////////////////////////////////////////////////////////

  /// @brief デフォルトの BusType を返す．
  static
  const ClibBusType&
  error_bus_type();

  /// @brief デフォルトの LutTemplate を返す．
  static
  const ClibLutTemplate&
  error_lut_template();

  /// @brief デフォルトの Lut を返す．
  static
  const ClibLut&
  error_lut();

  /// @brief デフォルトの Cell を返す．
  static
  const ClibCell&
  error_cell();

  /// @brief デフォルトの CellGroup を返す．
  static
  const ClibCellGroup&
  error_cell_group();

  /// @brief デフォルトの CellClass を返す．
  static
  const ClibCellClass&
  error_cell_class();

  /// @brief デフォルトの PatGraph を返す．
  static
  const ClibPatGraph&
  error_patgraph();


public:
  //////////////////////////////////////////////////////////////////////
  // 参照回数に関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 参照回数を増やす．
  void
  inc_ref();

  /// @brief 参照回数を減らす．
  void
  dec_ref();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルのグループ分けを行う．
  ///
  /// 論理セルのパタングラフも作成する．
  void
  compile(
    const vector<CiCell*>& cell_list ///< [in] 対象のセルのリスト
  );


  /// @brief セルグループを作る．
  ///
  /// pininfo は restore() 時のみ指定する．
  /// それ以外は後で set_ff_info()/set_latch_info() で設定する．
  CiCellGroup*
  new_cell_group(
    int id,                          ///< [in] 番号
    const NpnMapM& map,              ///< [in] 変換マップ
    int pininfo,                     ///< [in] ピン情報
    const vector<CiCell*>& cell_list ///< [in] セルのリスト
  );

  /// @brief セルクラスを作る．
  CiCellClass*
  new_cell_class(
    int id,                                ///< [in] 番号
    const vector<NpnMapM>& idmap_list,     ///< [in] 同位体変換リスト
    const vector<CiCellGroup*>& group_list ///< [in] グループのリスト
  );

  /// @brief LUT テンプレートを読み込む．
  void
  restore_lut_template(
    istream& s ///< [in] 入力ストリーム
  );

  /// @brief セルを読み込む．
  void
  restore_cell(
    istream& s,                ///< [in] 入力ストリーム
    vector<CiCell*>& cell_list ///< [out] 読み込んだセルを格納するリスト
  );

  /// @brief セルグループを読み込む．
  void
  restore_cell_group(
    istream& s,                              ///< [in] 入力ストリーム
    const vector<CiCell*>& global_cell_list, ///< [in] グローバルセルのリスト
    vector<CiCellGroup*>& group_list         ///< [out] 読み込んだセルグループを格納するリスト
  );

  /// @brief セルクラスを読み込む．
  void
  restore_cell_class(
    istream& s,                                    ///< [in] 入力ストリーム
    const vector<CiCellGroup*>& global_group_list, ///< [in] グローバルグループのリスト
    vector<CiCellClass*>& class_list               ///< [out] 読み込んだセルクラスを格納するリスト
  );

  /// @brief タイミング情報を読み込む．
  void
  restore_timing(
    istream& s,                    ///< [in] 入力ストリーム
    vector<CiTiming*>& timing_list ///< [out] 読み込んだタイミングを格納するリスト
  );

  /// @brief LUT を読み込む．
  /// @return 読み込んだLUTを返す．
  ClibLut*
  restore_lut(
    istream& s ///< [in] 入力ストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // ピンハッシュ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピンを登録する．
  void
  reg_pin(
    CiCellPin* pin ///< [in] ピン
  );

  /// @brief ピン名からピン番号を取り出す．
  ///
  /// 見つからない場合は -1 を返す．
  int
  get_pin_id(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] ピン名
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 参照回数
  int mRefCount;

  // 名前
  string mName;

  // テクノロジ
  ClibTechnology mTechnology{ClibTechnology::cmos};

  // バス命名規則
  string mBusNamingStyle;

  // 日付
  string mDate;

  // リビジョン
  string mRevision;

  // コメント
  string mComment;

  // 時間単位
  string mTimeUnit;

  // 電圧単位
  string mVoltageUnit;

  // 電流単位
  string mCurrentUnit;

  // 抵抗単位
  string mPullingResistanceUnit;

  // 容量単位
  double mCapacitiveLoadUnit;

  // 容量単位の文字列
  string mCapacitiveLoadUnitStr;

  // 電力単位
  string mLeakagePowerUnit;

  // 遅延モデル
  ClibDelayModel mDelayModel{ClibDelayModel::generic_cmos};

  // 遅延テンプレートのリスト
  ClibLutTemplateList mLutTemplateList;

  // 名前をキーにした遅延テンプレート番号のハッシュ表
  unordered_map<ShString, int> mLutHash;

  // セルのリスト
  ClibCellList mCellList;

  // 名前をキーにしたセルのハッシュ表
  unordered_map<ShString, CiCell*> mCellHash;

  // ピン名をキーにしたピン番号のハッシュ表
  CiCellPinHash mPinHash;

  // セルグループのリスト
  ClibCellGroupList mGroupList;

  // NPN同値クラスのリスト
  ClibCellClassList mClassList;

  // 論理セルグループの情報
  // 0: 定数0
  // 1: 定数1
  // 2: バッファ
  // 3: インバータ
  const ClibCellGroup* mLogicGroup[4];

  // FFクラスの情報
  //  0:    Q: クリアなし: プリセットなし
  //  1:    Q: クリアなし: プリセットあり
  //  2:    Q: クリアあり: プリセットなし
  //  3:    Q: クリアあり: プリセットあり
  //  4:   XQ: クリアなし: プリセットなし
  //  5:   XQ: クリアなし: プリセットあり
  //  6:   XQ: クリアあり: プリセットなし
  //  7:   XQ: クリアあり: プリセットあり
  //  8: Q/XQ: クリアなし: プリセットなし
  //  9: Q/XQ: クリアなし: プリセットあり
  // 10: Q/XQ: クリアあり: プリセットなし
  // 11: Q/XQ: クリアあり: プリセットあり
  const ClibCellClass* mFFClass[12];

  // ラッチクラスの情報
  //  0:    Q: クリアなし: プリセットなし
  //  1:    Q: クリアなし: プリセットあり
  //  2:    Q: クリアあり: プリセットなし
  //  3:    Q: クリアあり: プリセットあり
  //  4:   XQ: クリアなし: プリセットなし
  //  5:   XQ: クリアなし: プリセットあり
  //  6:   XQ: クリアあり: プリセットなし
  //  7:   XQ: クリアあり: プリセットあり
  //  8: Q/XQ: クリアなし: プリセットなし
  //  9: Q/XQ: クリアなし: プリセットあり
  // 10: Q/XQ: クリアあり: プリセットなし
  // 11: Q/XQ: クリアあり: プリセットあり
  const ClibCellClass* mLatchClass[12];

  // パタングラフを管理するクラス
  CiPatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLLIBRARY_H
