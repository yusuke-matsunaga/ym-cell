#ifndef CICELLLIBRARY_H
#define CICELLLIBRARY_H

/// @file CiCellLibrary.h
/// @brief CiCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibArea.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibResistance.h"
#include "ym/ClibPin.h"
#include "ym/ClibPatGraph.h"
#include "ym/ClibList.h"
#include "ym/ShString.h"
#include "ym/logic.h"
#include "ci/CiPatMgr.h"
#include "ci/CiCellPinHash.h"
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"


BEGIN_NAMESPACE_YM_CLIB

class CiBusType;
class CiCell;
class CiCellClass;
class CiCellGroup;
class CiInternalPin;
class CiLut;
class CiLutTemplate;
class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @class CiCellLibrary CiCellLibrary.h "CiCellLibrary.h"
/// @brief ClibCellLibrary の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCellLibrary
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

  /// @brief mislib 形式のファイルを読み込む．
  /// @return 生成したライブラリを返す．
  static
  CiCellLibrary*
  read_mislib(
    const string& filename ///< [in] ファイル名
  );

  /// @brief liberty 形式のファイルを読み込む．
  /// @return 生成したライブラリを返す．
  static
  CiCellLibrary*
  read_liberty(
    const string& filename ///< [in] ファイル名
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const
  {
    return mName;
  }

  /// @brief テクノロジの取得
  ///
  /// このクラスは常に ClibTechnology::cmos を返す．
  ClibTechnology
  technology() const
  {
    return mTechnology;
  }

  /// @brief 遅延モデルの取得
  /// 返り値は
  /// - ClibDelayModel::generic_cmos
  /// - ClibDelayModel::table_lookup
  /// - ClibDelayModel::piecewise_cmos
  /// - ClibDelayModel::cmos2
  /// - ClibDelayModel::dcm
  /// のいずれか
  ClibDelayModel
  delay_model() const
  {
    return mDelayModel;
  }

  /// @brief バス命名規則の取得
  string
  bus_naming_style() const
  {
    return mBusNamingStyle;
  }

  /// @brief 日付情報の取得
  string
  date() const
  {
    return mDate;
  }

  /// @brief リビジョン情報の取得
  string
  revision() const
  {
    return mRevision;
  }

  /// @brief コメント情報の取得
  string
  comment() const
  {
    return mComment;
  }

  /// @brief 時間単位の取得
  string
  time_unit() const
  {
    return mTimeUnit;
  }

  /// @brief 電圧単位の取得
  string
  voltage_unit() const
  {
    return mVoltageUnit;
  }

  /// @brief 電流単位の取得
  string
  current_unit() const
  {
    return mCurrentUnit;
  }

  /// @brief 抵抗単位の取得
  string
  pulling_resistance_unit() const
  {
    return mPullingResistanceUnit;
  }

  /// @brief 容量単位の取得
  double
  capacitive_load_unit() const
  {
    return mCapacitiveLoadUnit;
  }

  /// @brief 容量単位文字列の取得
  string
  capacitive_load_unit_str() const
  {
    return mCapacitiveLoadUnitStr;
  }

  /// @brief 電力単位の取得
  string
  leakage_power_unit() const
  {
    return mLeakagePowerUnit;
  }

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  lu_table_template(
    const string& name ///< [in] テンプレート名
  ) const
  {
    return lu_table_template(ShString(name));
  }

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  lu_table_template(
    const ShString& name ///< [in] テンプレート名
  ) const
  {
    if ( mLutDict.count(name) > 0 ) {
      return mLutDict.at(name);
    }
    return CLIB_NULLID;
  }

  /// @brief バスタイプの取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  bus_type(
    const string& name ///< [in] バスタイプ名
  ) const
  {
    return bus_type(ShString(name));
  }

  /// @brief バスタイプの取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  bus_type(
    const ShString& name ///< [in] バスタイプ名
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // セル情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief このライブラリの持つセル数の取得
  SizeType
  cell_num() const
  {
    return mCellList.size();
  }

  /// @brief 名前からのセル番号の取得
  SizeType
  cell(
    const string& name
  ) const
  {
    return cell(ShString(name));
  }

  /// @brief 名前からのセル番号の取得
  SizeType
  cell(
    const ShString& name
  ) const
  {
    if ( mCellDict.count(name) > 0 ) {
      return mCellDict.at(name);
    }
    return CLIB_NULLID;
  }

  /// @brief セル番号のリストの取得
  const vector<SizeType>&
  cell_list() const
  {
    return mRefCellList;
  }

  /// @brief セルグループ数の取得
  SizeType
  cell_group_num() const
  {
    return mGroupList.size();
  }

  /// @brief セルグループ番号のリストの取得
  const vector<SizeType>&
  cell_group_list() const
  {
    return mRefGroupList;
  }

  /// @brief NPN同値クラス数の取得
  SizeType
  npn_class_num() const
  {
    return mClassList.size();
  }

  /// @brief NPN同値クラス番号のリストの取得
  const vector<SizeType>&
  npn_class_list() const
  {
    return mRefClassList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 論理セルグループの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数0セルのグループを返す．
  SizeType
  const0_func() const
  {
    // 決め打ち
    return mLogicGroup[0];
  }

  /// @brief 定数1セルのグループを返す．
  SizeType
  const1_func() const
  {
    // 決め打ち
    return mLogicGroup[1];
  }

  /// @brief バッファセルのグループを返す．
  SizeType
  buf_func() const
  {
    // 決め打ち
    return mLogicGroup[2];
  }

  /// @brief インバータセルのグループを返す．
  SizeType
  inv_func() const
  {
    // 決め打ち
    return mLogicGroup[3];
  }


public:
  //////////////////////////////////////////////////////////////////////
  // FFセルクラスの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のFFクラスを返す．
  ///
  /// - cpv1, cpv2 の値は has_clear, has_preset がともに true
  ///   の時のみ意味を持つ．
  /// - 該当するセルがないときでも空のセルクラスが返される．
  SizeType
  simple_ff_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // ラッチセルクラスの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のラッチクラスを返す．
  ///
  /// - cpv1, cpv2 の値は has_clear, has_preset がともに true
  ///   の時のみ意味を持つ．
  /// - 該当するセルがないときでも空のセルクラスが返される．
  SizeType
  simple_latch_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_clear,    ///< [in] clear 端子を持つ時 true
    bool has_preset,   ///< [in] preset 端子を持つ時 true
    ClibCPV cpv1,      ///< [in] clear_preset_var1 の値
    ClibCPV cpv2       ///< [in] clear_preset_var2 の値
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 総パタン数を返す．
  SizeType
  pg_pat_num() const
  {
    return mPatMgr.pat_num();
  }

  /// @brief パタンの最大の入力数を得る．
  SizeType
  pg_max_input() const
  {
    return mPatMgr.max_input();
  }

  /// @brief 総ノード数を返す．
  SizeType
  pg_node_num() const
  {
    return mPatMgr.node_num();
  }

  /// @brief ノードの種類を返す．
  ClibPatType
  pg_node_type(
    SizeType id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const
  {
    return mPatMgr.node_type(id);
  }

  /// @brief ノードが入力ノードの時に入力番号を返す．
  ///
  /// 入力ノードでない場合の返り値は不定
  SizeType
  pg_input_id(
    SizeType id ///< [in] ノード番号 ( 0 <= id < pg_node_num() )
  ) const
  {
    return mPatMgr.input_id(id);
  }

  /// @brief 入力のノード番号を返す．
  SizeType
  pg_input_node(
    SizeType input_id ///< [in] 入力番号 ( 0 <= input_id < pg_max_input() )
  ) const
  {
    return mPatMgr.input_node(input_id);
  }

  /// @brief 総枝数を返す．
  SizeType
  pg_edge_num() const
  {
    return mPatMgr.edge_num();
  }

  /// @brief 枝のファンイン元のノード番号を返す．
  SizeType
  pg_edge_from(
    SizeType id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const
  {
    return mPatMgr.edge_from(id);
  }

  /// @brief 枝のファンアウト先のノード番号を返す．
  SizeType
  pg_edge_to(
    SizeType id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const
  {
    return mPatMgr.edge_to(id);
  }

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  SizeType
  pg_edge_pos(
    SizeType id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const
  {
    return mPatMgr.edge_pos(id);
  }

  /// @brief 枝の反転属性を返す．
  bool
  pg_edge_inv(
    SizeType id ///< [in] 枝番号 ( 0 <= id < pg_edge_num() )
  ) const
  {
    return mPatMgr.edge_inv(id);
  }


public:
  //////////////////////////////////////////////////////////////////////
  // ダンプ/リストア関係の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力ストリーム
  ) const;

  /// @brief バイナリダンプされた内容を読み込む．
  void
  restore(
    istream& s ///< [in] 入力ストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 情報設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を設定する．
  void
  set_name(
    const string& name ///< [in] 名前
  )
  {
    mName = name;
  }

  /// @brief 'technology' を設定する．
  void
  set_technology(
    ClibTechnology technology ///< [in] テクノロジ
  )
  {
    mTechnology = technology;
  }

  /// @brief 遅延モデルを設定する．
  void
  set_delay_model(
    ClibDelayModel delay_model ///< [in] 遅延モデル
  )
  {
    mDelayModel = delay_model;
  }

  /// @brief 'capacitive_load_unit' を設定する．
  void
  set_capacitive_load_unit(
    double unit,       ///< [in] 単位
    const string& ustr ///< [in] 単位を表す文字列
  )
  {
    mCapacitiveLoadUnit = unit;
    mCapacitiveLoadUnitStr = ustr;
  }

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

  /// @brief セルグループ/セルクラスの設定を行なう．
  void
  compile();


public:
  //////////////////////////////////////////////////////////////////////
  // CiXXX の生成関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1次元の LUT のテンプレートを作る．
  SizeType
  add_lut_template1(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1
  );

  /// @brief 2次元の LUT のテンプレートを作る．
  SizeType
  add_lut_template2(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2
  );

  /// @brief 3次元の LUT のテンプレートを作る．
  SizeType
  add_lut_template3(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2,
    ClibVarType var_type3,
    const vector<double>& index_list3
  );

  /// @brief セルクラスを作る．
  SizeType
  add_cell_class(
    const vector<ClibIOMap>& idmap_list ///< [in] 同位体変換のリスト
  );

  /// @brief セルグループを作る．
  SizeType
  add_cell_group(
    SizeType rep_class,    ///< [in] 親のセルクラス
    const ClibIOMap& iomap ///< [in] 変換マップ
  );

  /// @brief 論理セルを追加する．
  SizeType
  add_logic_cell(
    const ShString& name,     ///< [in] 名前
    ClibArea area             ///< [in] 面積
  );

  /// @brief FFセルを追加する．
  SizeType
  add_ff_cell(
    const ShString& name,      ///< [in] 名前
    ClibArea area,             ///< [in] 面積
    const ShString& var1,      ///< [in] 内部変数1の名前
    const ShString& var2,      ///< [in] 内部変数2の名前
    const Expr& clock,         ///< [in] マスタークロックの論理式
    const Expr& clock2,        ///< [in] スレーブクロックの論理式
    const Expr& next_state,    ///< [in] 次状態の論理式
    const Expr& clear,         ///< [in] クリア条件の論理式
    const Expr& preset,        ///< [in] プリセット条件の論理式
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  );

  /// @brief ラッチセルを追加する．
  SizeType
  add_latch_cell(
    const ShString& name,      ///< [in] 名前
    ClibArea area,             ///< [in] 面積
    const ShString& var1,      ///< [in] 内部変数1の名前
    const ShString& var2,      ///< [in] 内部変数2の名前
    const Expr& enable,        ///< [in] マスターイネーブルの論理式
    const Expr& enable2,       ///< [in] スレーブイネーブルの論理式
    const Expr& data_in,       ///< [in] データ入力の論理式
    const Expr& clear,         ///< [in] クリア条件の論理式
    const Expr& preset,        ///< [in] プリセット条件の論理式
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  );

  /// @brief FSMセルを追加する．
  SizeType
  add_fsm_cell(
    const ShString& name,      ///< [in] 名前
    ClibArea area              ///< [in] 面積
  );

  /// @brief 入力ピンを追加する．
  /// @return 生成されたピン番号を返す．
  SizeType
  add_input(
    SizeType cell_id,                 ///< [in] セル番号
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance  ///< [in] 立ち下がり時の負荷容量
  );

  /// @brief 出力ピンを追加する．
  /// @return 生成されたピン番号を返す．
  SizeType
  add_output(
    SizeType cell_id,                ///< [in] セル番号
    const ShString& name,            ///< [in] ピン名
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最大負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition,         ///< [in] 最大遷移時間
    const Expr& function,            ///< [in] 出力の論理式
    const Expr& tristate             ///< [in] tristate 条件
  );

  /// @brief 入出力ピンを追加する．
  /// @return 生成されたピン番号を返す．
  SizeType
  add_inout(
    SizeType cell_id,                 ///< [in] セル番号
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance max_fanout,	      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,	      ///< [in] 最大ファンアウト容量
    ClibCapacitance max_capacitance,  ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance,  ///< [in] 最大負荷容量
    ClibTime max_transition,	      ///< [in] 最大遷移時間
    ClibTime min_transition,          ///< [in] 最大遷移時間
    const Expr& function,             ///< [in] 出力の論理式
    const Expr& tristate              ///< [in] tristate 条件
  );

  /// @brief 内部ピンを追加する．
  /// @return 生成されたピン番号を返す．
  SizeType
  add_internal(
    SizeType cell_id,    ///< [in] セル番号
    const ShString& name ///< [in] 名前
  );

  /// @brief バスを追加する．
  /// @return 生成されｔバス番号を返す．
  SizeType
  add_bus(
    SizeType cell_id,                ///< [in] セル番号
    const ShString& name,            ///< [in] 名前
    SizeType bus_type,               ///< [in] バスタイプ
    const vector<SizeType>& pin_list ///< [in] ピンリスト
  );

  /// @brief バンドルを追加する．
  /// @return 生成されたバンドル番号を返す．
  SizeType
  add_bundle(
    SizeType cell_id,                ///< [in] セル番号
    const ShString& name,            ///< [in] 名前
    const vector<SizeType>& pin_list ///< [in] ピンリスト
  );

  /// @brief タイミング情報を作る(ジェネリック遅延モデル)．
  /// @return 生成されたタイミング番号を返す．
  SizeType
  add_timing_generic(
    ClibTimingType type,            ///< [in] タイミングの種類
    const Expr& cond,               ///< [in] 条件式
    ClibTime intrinsic_rise,        ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,        ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,            ///< [in] 立ち上がり負荷依存遅延
    ClibTime slope_fall,            ///< [in] 立ち下がり負荷依存遅延
    ClibResistance rise_resistance, ///< [in] 立ち上がり抵抗
    ClibResistance fall_resistance  ///< [in] 立ち下がり抵抗
  );

  /// @brief タイミング情報を作る(折れ線近似)．
  /// @return 生成されたタイミング番号を返す．
  SizeType
  add_timing_piecewise(
    ClibTimingType timing_type,
    const Expr& cond,
    ClibTime intrinsic_rise,
    ClibTime intrinsic_fall,
    ClibTime slope_rise,
    ClibTime slope_fall,
    ClibResistance rise_pin_resistance,
    ClibResistance fall_pin_resistance
  );

  /// @brief タイミング情報を作る(非線形タイプ1)．
  /// @return 生成されたタイミング番号を返す．
  SizeType
  add_timing_lut1(
    ClibTimingType timing_type,
    const Expr& cond,
    SizeType cell_rise,
    SizeType cell_fall,
    SizeType rise_transition,
    SizeType fall_transition
  );

  /// @brief タイミング情報を作る(非線形タイプ2)．
  /// @return 生成されたタイミング番号を返す．
  SizeType
  add_timing_lut2(
    ClibTimingType timing_type,
    const Expr& cond,
    SizeType rise_transition,
    SizeType fall_transition,
    SizeType rise_propagation,
    SizeType fall_propagation
  );

  /// @brief タイミング情報用のデータ構造を初期化する．
  void
  init_cell_timing_map(
    SizeType cell_id ///< [in] セル番号
  );

  /// @brief 1次元の LUT を作る．
  CiLut*
  new_lut1(
    const CiLutTemplate* lut_template, ///< [in] テンプレート
    const vector<double>& value_array, ///< [in] 値の配列
    const vector<double>& index_array  ///< [in] インデックス値のリスト
  );

  /// @brief 2次元の LUT を作る．
  CiLut*
  new_lut2(
    const CiLutTemplate* lut_template,  ///< [in] テンプレート
    const vector<double>& value_array,  ///< [in] 値の配列
    const vector<double>& index_array1, ///< [in] インデックス値のリスト1
    const vector<double>& index_array2  ///< [in] インデックス値のリスト2
  );

  /// @brief 3次元の LUT を作る．
  CiLut*
  new_lut3(
    const CiLutTemplate* lut_template,  ///< [in] テンプレート
    const vector<double>& value_array,  ///< [in] 値の配列
    const vector<double>& index_array1, ///< [in] インデックス値のリスト1
    const vector<double>& index_array2, ///< [in] インデックス値のリスト2
    const vector<double>& index_array3  ///< [in] インデックス値のリスト3
  );

  /// @brief LUT を作る．
  SizeType
  add_lut(
    const ShString& templ_name,        ///< [in] テンプレート名
    const vector<double>& value_array, ///< [in] 値の配列
    const vector<double>& index_array1 ///< [in] インデックス値のリスト1
    = vector<double>{},
    const vector<double>& index_array2 ///< [in] インデックス値のリスト2
    = vector<double>{},
    const vector<double>& index_array3 ///< [in] インデックス値のリスト3
    = vector<double>{}
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 参照回数に関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 参照回数を増やす．
  void
  inc_ref() const;

  /// @brief 参照回数を減らす．
  void
  dec_ref() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CiXXX の要素にアクセスする関数
  //////////////////////////////////////////////////////////////////////

  /// @brief LUT テンプレートを得る．
  CiLutTemplate*
  _lut_template(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mLutTemplateList[id].get();
  }

  /// @brief セルクラスを得る．
  CiCellClass*
  _cell_class(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mClassList[id].get();
  }

  /// @brief セルグループを得る．
  CiCellGroup*
  _cell_group(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mGroupList[id].get();
  }

  /// @brief セルを得る．
  CiCell*
  _cell(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mCellList[id].get();
  }

  /// @brief ピンを得る．
  CiPin*
  _pin(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mPinList[id].get();
  }

  /// @brief バスを得る．
  CiBus*
  _bus(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mBusList[id].get();
  }

  /// @brief バンドルを得る．
  CiBundle*
  _bundle(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mBundleList[id].get();
  }

  /// @brief タイミング情報を得る．
  CiTiming*
  _timing(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mTimingList[id].get();
  }

  /// @brief LUTを得る．
  CiLut*
  _lut(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mLutList[id].get();
  }

  /// @brief パタンを得る．
  const CiPatGraph&
  _pat_graph(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mPatMgr.pat(id);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // restore で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を読み込む．
  void
  restore_name(
    BinDec& s ///< [in] 入力ストリーム
  )
  {
    string name;
    s >> name;
    mName = name;
  }

  /// @brief 'technology' を読み込む．
  void
  restore_technology(
    BinDec& s ///< [in] 入力ストリーム
  )
  {
    ymuint8 tmp;
    s >> tmp;
    mTechnology = static_cast<ClibTechnology>(tmp);
  }

  /// @brief 遅延モデルを読み込む．
  void
  restore_delay_model(
    BinDec& s ///< [in] 入力ストリーム
  )
  {
    ymuint8 tmp;
    s >> tmp;
    mDelayModel = static_cast<ClibDelayModel>(tmp);
  }

  /// @brief 'capacitive_load_unit' を読み込む．
  void
  restore_capacitive_load_unit(
    BinDec& s ///< [in] 入力ストリーム
  )
  {
    double unit;
    string ustr;
    s >> unit
      >> ustr;
    mCapacitiveLoadUnit = unit;
    mCapacitiveLoadUnitStr = ustr;
  }

  /// @brief 属性を読み込む(浮動小数点型)
  void
  restore_double_attr(
    BinDec& s,              ///< [in] 入力ストリーム
    const string& attr_name ///< [in] 属性名
  )
  {
    double val;
    s >> val;
    set_attr(attr_name, val);
  }

  /// @brief 属性を読み込む(文字列型)．
  void
  restore_str_attr(
    BinDec& s,              ///< [in] 入力ストリーム
    const string& attr_name ///< [in] 属性名
  )
  {
    string val;
    s >> val;
    set_attr(attr_name, val);
  }

  /// @brief バスタイプを読み込む．
  void
  restore_bustype(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief LUT テンプレートを読み込む．
  void
  restore_lut_template(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief セルを読み込む．
  void
  restore_cell(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief ピン情報を読み込む．
  void
  restore_pin(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief バス情報を読み込む．
  void
  restore_bus(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief バンドル情報を読み込む．
  void
  restore_bundle(
    BinDec& s ///< [in] 入力ストリーム
  );

  /// @brief セルごとのピン，バス，バンドルの辞書を作る．
  void
  construct_cellpin_dict();

  /// @brief タイミング情報を読み込む．
  void
  restore_timing(
    BinDec& s  ///< [in] 入力ストリーム
  );

  /// @brief LUT を読み込む．
  void
  restore_lut(
    BinDec& s  ///< [in] 入力ストリーム
  );

  /// @brief セルグループを読み込む．
  void
  restore_cell_group(
    BinDec& s  ///< [in] 入力ストリーム
  );

  /// @brief セルクラスを読み込む．
  void
  restore_cell_class(
    BinDec& s  ///< [in] 入力ストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // ピンハッシュ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピンを登録する．
  /// @return ピン番号を返す．
  SizeType
  reg_pin(
    SizeType cell_id, ///< [in] セル番号
    CiPin* pin        ///< [in] ピン
  )
  {
    SizeType id = mPinList.size();
    mPinList.push_back(unique_ptr<CiPin>{pin});
    mPinDict.add(cell_id, pin->_name(), id);
    return id;
  }

  /// @brief ピン名からピン番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_pin_id(
    SizeType cell_id, ///< [in] セル番号
    ShString name     ///< [in] ピン名
  ) const
  {
    return mPinDict.get(cell_id, name);
  }

  /// @brief バスを登録する．
  SizeType
  reg_bus(
    SizeType cell_id, ///< [in] セル番号
    CiBus* bus        ///< [in] バス
  )
  {
    auto id = mBusList.size();
    mBusList.push_back(unique_ptr<CiBus>(bus));
    mBusDict.add(cell_id, bus->_name(), id);
    return id;
  }

  /// @brief バス名からバス番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_bus_id(
    SizeType cell_id, ///< [in] セル番号
    ShString name     ///< [in] バス名
  ) const
  {
    return mBusDict.get(cell_id, name);
  }

  /// @brief バンドルを登録する．
  SizeType
  reg_bundle(
    SizeType cell_id, ///< [in] セル番号
    CiBundle* bundle  ///< [in] バンドル
  )
  {
    auto id = mBundleList.size();
    mBundleList.push_back(unique_ptr<CiBundle>(bundle));
    mBundleDict.add(cell_id, bundle->_name(), id);
    return id;
  }

  /// @brief バンドル名からバンドル番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_bundle_id(
    SizeType cell_id, ///< [in] セル番号
    ShString name     ///< [in] バンドル名
  ) const
  {
    return mBundleDict.get(cell_id, name);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をクリアする．
  void
  clear();

  /// @brief セルを登録する．
  /// @return セル番号を返す．
  SizeType
  reg_cell(
    CiCell* cell ///< [in] セル
  );

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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 参照回数
  mutable
  SizeType mRefCount{0};

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
  double mCapacitiveLoadUnit{0.0};

  // 容量単位の文字列
  string mCapacitiveLoadUnitStr;

  // 電力単位
  string mLeakagePowerUnit;

  // 遅延モデル
  ClibDelayModel mDelayModel{ClibDelayModel::generic_cmos};

  // バスタイプのリスト
  vector<unique_ptr<CiBusType>> mBusTypeList;

  // 名前をキーにしたバスタイプ番号の辞書
  unordered_map<ShString, SizeType> mBusTypeDict;

  // 遅延テンプレートのリスト
  vector<unique_ptr<CiLutTemplate>> mLutTemplateList;

  // テンプレート番号のリスト
  vector<SizeType> mRefLutTemplateList;

  // 名前をキーにした遅延テンプレート番号の辞書
  unordered_map<ShString, SizeType> mLutDict;

  // セルの所有権管理用のリスト
  vector<unique_ptr<CiCell>> mCellList;

  // セル番号のリスト
  vector<SizeType> mRefCellList;

  // 名前をキーにしたセル番号の辞書
  unordered_map<ShString, SizeType> mCellDict;

  // ピンの所有権管理用のリスト
  vector<unique_ptr<CiPin>> mPinList;

  // セル番号とピン名をキーにしたピン番号の辞書
  CiCellPinHash mPinDict;

  // バスの所有権管理用のリスト
  vector<unique_ptr<CiBus>> mBusList;

  // セル番号とバス名をキーにしたバス番号の辞書
  CiCellPinHash mBusDict;

  // バンドルの所有権管理用のリスト
  vector<unique_ptr<CiBundle>> mBundleList;

  // セル番号とバンドル名をキーにしたバンドル番号の辞書
  CiCellPinHash mBundleDict;

  // タイミング情報のリスト
  vector<unique_ptr<CiTiming>> mTimingList;

  // Lut のリスト
  vector<unique_ptr<CiLut>> mLutList;

  // セルグループの所有権管理用のリスト
  vector<unique_ptr<CiCellGroup>> mGroupList;

  // セルグループ番号のリスト
  vector<SizeType> mRefGroupList;

  // NPN同値クラスの所有権管理用のリスト
  vector<unique_ptr<CiCellClass>> mClassList;

  // NPN同値類番号のリスト
  vector<SizeType> mRefClassList;

  // 論理セルグループの情報
  // 0: 定数0
  // 1: 定数1
  // 2: バッファ
  // 3: インバータ
  SizeType mLogicGroup[4];

  // 単純なFFクラスの情報
  // インデックスは CiSeqInfo で作る．
  vector<SizeType> mSimpleFFClass;

  // 単純なラッチクラスの情報
  // インデックスは CiSeqInfo で作る．
  vector<SizeType> mSimpleLatchClass;

  // パタングラフを管理するクラス
  CiPatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLLIBRARY_H
