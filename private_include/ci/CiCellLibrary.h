#ifndef CICELLLIBRARY_H
#define CICELLLIBRARY_H

/// @file CiCellLibrary.h
/// @brief CiCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibArea.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibResistance.h"
#include "ym/ClibTiming.h"
#include "ym/ClibPin.h"
#include "ym/ShString.h"
#include "ym/Expr.h"
#include "CiLutHash.h"
#include "CiCellHash.h"
#include "CiPatMgr.h"
#include "CiPinHash.h"

#include "ci/CiCell.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCellClass.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"


#if 0
BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

class LibComp;

END_NAMESPACE_YM_CLIB_LIBCOMP
#endif

BEGIN_NAMESPACE_YM_CLIB

class CiBus;
class CiBundle;

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
  ///
  /// エラーが起こったら nullptr を返す．
  static
  CiCellLibrary*
  read_mislib(
    const string& filename ///< [in] ファイル名
  );

  /// @brief liberty 形式のファイルを読み込む．
  /// @return 生成したライブラリを返す．
  ///
  /// エラーが起こったら nullptr を返す．
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

  /// @brief 遅延テーブルのテンプレート数の取得
  SizeType
  lu_table_template_num() const
  {
    return mLutTemplateList.size();
  }

  /// @brief 遅延テーブルのテンプレート番号の取得
  const ClibLutTemplate&
  lu_table_template(
    SizeType table_id ///< [in] テンプレート番号 ( 0 <= table_id < lu_table_template_num() )
  ) const
  {
    ASSERT_COND( 0 <= table_id && table_id < lu_table_template_num() );
    return *mLutTemplateList[table_id];
  }

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  lu_table_template_id(
    const char* name ///< [in] テンプレート名
  ) const
  {
    return lu_table_template_id(ShString(name));
  }

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  lu_table_template_id(
    const string& name ///< [in] テンプレート名
  ) const
  {
    return lu_table_template_id(ShString(name));
  }

  /// @brief ルックアップテーブルのテンプレート番号の取得
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  lu_table_template_id(
    const ShString& name ///< [in] テンプレート名
  ) const
  {
    if ( mLutHash.count(name) > 0 ) {
      return mLutHash.at(name);
    }
    else {
      return CLIB_NULLID;
    }
  }

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const char* name ///< [in] バスタイプ名
  ) const
  {
    return bus_type(ShString(name));
  }

  /// @brief バスタイプの取得
  ///
  /// なければ nullptr を返す．
  const ClibBusType&
  bus_type(
    const string& name ///< [in] バスタイプ名
  ) const
  {
    return bus_type(ShString(name));
  }

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

  /// @brief このライブラリの持つセル数の取得
  SizeType
  cell_num() const
  {
    return mCellList.size();
  }

  /// @brief セル情報の取得
  /// @return 該当するセル情報を返す．
  const ClibCell&
  cell(
    SizeType cell_id ///< [in] セル番号 ( 0 <= cell_id < cell_num() )
  ) const
  {
    ASSERT_COND( 0 <= cell_id && cell_id < cell_num() );
    return *mCellList[cell_id];
  }

  /// @brief 名前からのセル番号の取得
  SizeType
  cell_id(
    const char* name
  ) const
  {
    return cell_id(ShString(name));
  }

  /// @brief 名前からのセル番号の取得
  SizeType
  cell_id(
    const string& name
  ) const
  {
    return cell_id(ShString(name));
  }

  /// @brief 名前からのセル番号の取得
  SizeType
  cell_id(
    const ShString& name
  ) const
  {
    return mCellHash.at(name)->id();
  }

  /// @brief セルグループ数の取得
  SizeType
  cell_group_num() const
  {
    return mGroupList.size();
  }

  /// @brief セルグループの取得
  const ClibCellGroup&
  cell_group(
    SizeType id ///< [in] グループ番号 ( 0 <= id < cell_group_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < cell_group_num() );
    return *mGroupList[id];
  }

  /// @brief NPN同値クラス数の取得
  SizeType
  npn_class_num() const
  {
    return mClassList.size();
  }

  /// @brief NPN同値クラスの取得
  const ClibCellClass&
  npn_class(
    SizeType id ///< [in] 同値クラス番号 ( 0 <= id < npn_class_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < npn_class_num() );
    return *mClassList[id];
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 論理セルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数0セルのグループを返す．
  const ClibCellGroup&
  const0_func() const
  {
    // 決め打ち
    return *mLogicGroup[0];
  }

  /// @brief 定数1セルのグループを返す．
  const ClibCellGroup&
  const1_func() const
  {
    // 決め打ち
    return *mLogicGroup[1];
  }

  /// @brief バッファセルのグループを返す．
  const ClibCellGroup&
  buf_func() const
  {
    // 決め打ち
    return *mLogicGroup[2];
  }

  /// @brief インバータセルのグループを返す．
  const ClibCellGroup&
  inv_func() const
  {
    // 決め打ち
    return *mLogicGroup[3];
  }


public:
  //////////////////////////////////////////////////////////////////////
  // FFセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のFFクラスを返す．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass&
  simple_ff_class(
    bool has_clear,
    bool has_preset
  ) const
  {
    SizeType pos = 0;
    if ( has_clear ) {
      pos += 1;
    }
    if ( has_preset ) {
      pos += 2;
    }
    return *mFFClass[pos];
  }


public:
  //////////////////////////////////////////////////////////////////////
  // ラッチセルの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 単純な型のラッチクラスを返す．
  ///
  /// 該当するセルがないときでも空のセルクラスが返される．
  const ClibCellClass&
  simple_latch_class(
    bool has_clear,
    bool has_preset
  ) const
  {
    SizeType pos = 0;
    if ( has_clear ) {
      pos += 1;
    }
    if ( has_preset ) {
      pos += 2;
    }
    return *mLatchClass[pos];
  }


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

  /// @brief パタンを返す．
  const ClibPatGraph&
  pg_pat(
    SizeType id
  ) const
  {
    return mPatMgr.pat(id);
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
    SizeType id
  ) const
  {
    return mPatMgr.node_type(id);
  }

  /// @brief ノードが入力ノードの時に入力番号を返す．
  /// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
  /// @note 入力ノードでない場合の返り値は不定
  SizeType
  pg_input_id(
    SizeType id
  ) const
  {
    return mPatMgr.input_id(id);
  }

  /// @brief 入力のノード番号を返す．
  /// @return input_id の入力に対応するノードのノード番号
  SizeType
  pg_input_node(
    SizeType input_id
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
  /// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
  SizeType
  pg_edge_from(
    SizeType id
  ) const
  {
    return mPatMgr.edge_from(id);
  }

  /// @brief 枝のファンアウト先のノード番号を返す．
  /// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
  SizeType
  pg_edge_to(
    SizeType id
  ) const
  {
    return mPatMgr.edge_to(id);
  }

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  /// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
  SizeType
  pg_edge_pos(
    SizeType id
  ) const
  {
    return mPatMgr.edge_pos(id);
  }

  /// @brief 枝の反転属性を返す．
  bool
  pg_edge_inv(
    SizeType id
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
    ostream& s
  ) const;

  /// @brief バイナリダンプされた内容を読み込む．
  void
  restore(
    istream& s
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 情報設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を設定する．
  void
  set_name(
    const string& name
  )
  {
    mName = name;
  }

  /// @brief 'technology' を設定する．
  void
  set_technology(
    ClibTechnology technology
  )
  {
    mTechnology = technology;
  }

  /// @brief 遅延モデルを設定する．
  void
  set_delay_model(
    ClibDelayModel delay_model
  )
  {
    mDelayModel = delay_model;
  }

  /// @brief 'capacitive_load_unit' を設定する．
  void
  set_capacitive_load_unit(
    double unit,
    const string& ustr
  )
  {
    mCapacitiveLoadUnit = unit;
    mCapacitiveLoadUnitStr = ustr;
  }

  /// @brief 属性を設定する(浮動小数点型)
  void
  set_attr(
    const string& attr_name,
    double value
  );

  /// @brief 属性を設定する(文字列型)．
  void
  set_attr(
    const string& attr_name,
    const string& value
  );

  /// @brief 遅延テーブルのテンプレートのリストを設定する．
  void
  set_lu_table_template_list(
    const vector<CiLutTemplate*>& template_list
  );


public:
  //////////////////////////////////////////////////////////////////////
  // CiXXX の生成関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1次元の LUT のテンプレートを作る．
  static
  CiLutTemplate*
  new_lut_template1(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1
  );

  /// @brief 2次元の LUT のテンプレートを作る．
  static
  CiLutTemplate*
  new_lut_template2(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2
  );

  /// @brief 3次元の LUT のテンプレートを作る．
  static
  CiLutTemplate*
  new_lut_template3(
    const ShString& name,
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2,
    ClibVarType var_type3,
    const vector<double>& index_list3
  );

  /// @brief セルクラスを作る．
  CiCellClass*
  new_cell_class(
    const vector<NpnMapM>& idmap_list ///< [in] 同位体変換のリスト
  );

  /// @brief 1出力の論理セル用のグループを作る．
  CiCellGroup*
  new_logic_group(
    const ClibCellClass* rep_class, ///< [in] 親のセルクラス
    const NpnMapM& map,             ///< [in] 変換マップ
    SizeType input_num,             ///< [in] 入力数
    const Expr& expr                ///< [in] 出力の論理式
  );

  /// @brief 一般的な論理セル用のグループを作る．
  CiCellGroup*
  new_logic_group(
    const ClibCellClass* rep_class,    ///< [in] 親のセルクラス
    const NpnMapM& map,                ///< [in] 変換マップ
    SizeType input_num,                ///< [in] 入力数
    SizeType output_num,               ///< [in] 出力数
    SizeType inout_num,                ///< [in] 入出力数
    const vector<Expr>& expr_array,    ///< [in] 出力の論理式の配列
    const vector<Expr>& tristate_array ///< [in] 出力のtristate条件の配列
  );

  /// @brief FF用のグループを作る．
  CiCellGroup*
  new_ff_group(
    const ClibCellClass* rep_class,     ///< [in] 親のセルクラス
    const NpnMapM& map,                 ///< [in] 変換マップ
    SizeType input_num,                 ///< [in] 入力数
    SizeType output_num,                ///< [in] 出力数
    SizeType inout_num,                 ///< [in] 入出力数
    const vector<Expr>& expr_array,     ///< [in] 出力の論理式の配列
    const vector<Expr>& tristate_array, ///< [in] 出力のtristate条件の配列
    const Expr& clock,                  ///< [in] マスタークロックの論理式
    const Expr& clock2,                 ///< [in] スレーブクロックの論理式
    const Expr& next_state,             ///< [in] 次状態の論理式
    const Expr& clear,                  ///< [in] クリア条件の論理式
    const Expr& preset,                 ///< [in] プリセット条件の論理式
    ClibCPV clear_preset_var1,          ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2           ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  );

  /// @brief 論理セルを生成する．
  static
  CiCell*
  new_logic_cell(
    const ShString& name,
    ClibArea area,
    const vector<CiInputPin*>& input_list,
    const vector<CiOutputPin*>& output_list,
    const vector<CiInoutPin*>& inout_list,
    const vector<CiBus*>& bus_list,
    const vector<CiBundle*>& bundle_list,
    const vector<CiTiming*>& timing_list
  );

  /// @brief FFセルを生成する．
  static
  CiCell*
  new_ff_cell(
    const ShString& name,
    ClibArea area,
    const vector<CiInputPin*>& input_list,
    const vector<CiOutputPin*>& output_list,
    const vector<CiInoutPin*>& inout_list,
    const vector<CiBus*>& bus_list,
    const vector<CiBundle*>& bundle_list,
    const vector<CiTiming*>& timing_list,
    const Expr& next_state,
    const Expr& clocked_on,
    const Expr& clocked_on_also,
    const Expr& clear,
    const Expr& preset,
    int clear_preset_var1,
    int clear_preset_var2
  );

  /// @brief ラッチセルを生成する．
  static
  CiCell*
  new_latch_cell(
    const ShString& name,
    ClibArea area,
    const vector<CiInputPin*>& input_list,
    const vector<CiOutputPin*>& output_list,
    const vector<CiInoutPin*>& inout_list,
    const vector<CiBus*>& bus_list,
    const vector<CiBundle*>& bundle_list,
    const vector<CiTiming*>& timing_list,
    const Expr& data_in,
    const Expr& enable,
    const Expr& enable_also,
    const Expr& clear,
    const Expr& preset,
    int clear_preset_var1,
    int clear_preset_var2
  );

  /// @brief FSMセルを生成する．
  static
  CiCell*
  new_fsm_cell(
    const ShString& name,
    ClibArea area,
    const vector<CiInputPin*>& input_list,
    const vector<CiOutputPin*>& output_list,
    const vector<CiInoutPin*>& inout_list,
    const vector<CiInternalPin*>& internal_list,
    const vector<CiBus*>& bus_list,
    const vector<CiBundle*>& bundle_list,
    const vector<CiTiming*>& timing_list
  );

  /// @brief セルの入力ピンを生成する．
  static
  CiInputPin*
  new_cell_input(
    const ShString& name,
    ClibCapacitance capacitance,
    ClibCapacitance rise_capacitance,
    ClibCapacitance fall_capacitance
  );

  /// @brief セルの出力ピンの内容を設定する．
  static
  CiOutputPin*
  new_cell_output(
    const ShString& name,
    ClibCapacitance max_fanout,
    ClibCapacitance min_fanout,
    ClibCapacitance max_capacitance,
    ClibCapacitance min_capacitance,
    ClibTime max_transition,
    ClibTime min_transition
  );

  /// @brief セルの入出力ピンの内容を設定する．
  static
  CiInoutPin*
  new_cell_inout(
    const ShString& name,
    ClibCapacitance capacitance,
    ClibCapacitance rise_capacitance,
    ClibCapacitance fall_capacitance,
    ClibCapacitance max_fanout,
    ClibCapacitance min_fanout,
    ClibCapacitance max_capacitance,
    ClibCapacitance min_capacitance,
    ClibTime max_transition,
    ClibTime min_transition
  );

  /// @brief セルの内部ピンを生成する．
  static
  CiInternalPin*
  new_cell_internal(
    const ShString& name
  );

  /// @brief タイミング情報を作る(ジェネリック遅延モデル)．
  static
  CiTiming*
  new_timing_generic(
    ClibTimingType type,
    const Expr& cond,
    ClibTime intrinsic_rise,
    ClibTime intrinsic_fall,
    ClibTime slope_rise,
    ClibTime slope_fall,
    ClibResistance rise_resistance,
    ClibResistance fall_resistance
  );

  /// @brief タイミング情報を作る(折れ線近似)．
  static
  CiTiming*
  new_timing_piecewise(
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
  static
  CiTiming*
  new_timing_lut1(
    ClibTimingType timing_type,
    const Expr& cond,
    CiLut* cell_rise,
    CiLut* cell_fall,
    CiLut* rise_transition,
    CiLut* fall_transition
  );

  /// @brief タイミング情報を作る(非線形タイプ2)．
  static
  CiTiming*
  new_timing_lut2(
    ClibTimingType timing_type,
    const Expr& cond,
    CiLut* rise_transition,
    CiLut* fall_transition,
    CiLut* rise_propagation,
    CiLut* fall_propagation
  );

  /// @brief タイミング情報をセットする．
  static
  void
  set_timing(
    CiCell* cell,
    int input_id,
    int output_id,
    ClibTimingSense timing_sense,
    const vector<CiTiming*>& timing_list
  );

  /// @brief 1次元の LUT を作る．
  /// @param[in] lut_template テンプレート
  /// @param[in] value_array 値の配列
  /// @param[in] index_array インデックス値のリスト
  static
  CiLut*
  new_lut1(
    const ClibLutTemplate* lut_template,
    const vector<double>& value_array,
    const vector<double>& index_array = vector<double>{}
  );

  /// @brief 2次元の LUT を作る．
  /// @param[in] lut_template テンプレート
  /// @param[in] value_array 値の配列
  /// @param[in] index_array1 インデックス値のリスト
  /// @param[in] index_array2 インデックス値のリスト
  static
  CiLut*
  new_lut2(
    const ClibLutTemplate* lut_template,
    const vector<double>& value_array,
    const vector<double>& index_array1 = vector<double>{},
    const vector<double>& index_array2 = vector<double>{}
  );

  /// @brief 3次元の LUT を作る．
  /// @param[in] lut_template テンプレート
  /// @param[in] value_array 値の配列
  /// @param[in] index_array1 インデックス値のリスト
  /// @param[in] index_array2 インデックス値のリスト
  /// @param[in] index_array3 インデックス値のリスト
  static
  CiLut*
  new_lut3(
    const ClibLutTemplate* lut_template,
    const vector<double>& value_array,
    const vector<double>& index_array1 = vector<double>{},
    const vector<double>& index_array2 = vector<double>{},
    const vector<double>& index_array3 = vector<double>{}
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

  /// @brief LUT テンプレートを読み込む．
  void
  restore_lut_template(
    istream& s ///< [in] 入力ストリーム
  );

  /// @brief セルを読み込む．
  void
  restore_cell(
    istream& s ///< [in] 入力ストリーム
  );

  /// @brief セルグループを読み込む．
  void
  restore_cell_group(
    istream& s  ///< [in] 入力ストリーム
  );

  /// @brief セルクラスを読み込む．
  void
  restore_cell_class(
    istream& s  ///< [in] 入力ストリーム
  );

  /// @brief タイミング情報を読み込む．
  vector<CiTiming*>
  restore_timing(
    istream& s  ///< [in] 入力ストリーム
  );

  /// @brief LUT を読み込む．
  CiLut*
  restore_lut(
    istream& s  ///< [in] 入力ストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // ピンハッシュ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピンを登録する．
  void
  reg_pin(
    const CiCell* cell, ///< [in] 親のセル
    ShString name,      ///< [in] ピン名
    SizeType id         ///< [in] ピン番号
  );

  /// @brief ピン名からピン番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_pin_id(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] ピン名
  );

  /// @brief バスを登録する．
  void
  reg_bus(
    const CiCell* cell, ///< [in] 親のセル
    ShString name,      ///< [in] バス名
    SizeType id         ///< [in] バス番号
  );

  /// @brief バス名からバス番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_bus_id(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] バス名
  );

  /// @brief バンドルを登録する．
  void
  reg_bundle(
    const CiCell* cell, ///< [in] 親のセル
    ShString name,      ///< [in] バンドル名
    SizeType id         ///< [in] バンドル番号
  );

  /// @brief バンドル名からバンドル番号を取り出す．
  ///
  /// 見つからない場合は CLIB_NULLID を返す．
  SizeType
  get_bundle_id(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] バンドル名
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 参照回数
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
  double mCapacitiveLoadUnit;

  // 容量単位の文字列
  string mCapacitiveLoadUnitStr;

  // 電力単位
  string mLeakagePowerUnit;

  // 遅延モデル
  ClibDelayModel mDelayModel{ClibDelayModel::generic_cmos};

  // 遅延テンプレートのリスト
  vector<CiLutTemplate*> mLutTemplateList;

  // 名前をキーにした遅延テンプレート番号のハッシュ表
  unordered_map<ShString, SizeType> mLutHash;

  // セルのリスト
  vector<unique_ptr<CiCell>> mCellList;

  // 名前をキーにしたセルのハッシュ表
  unordered_map<ShString, CiCell*> mCellHash;

  // ピン名をキーにしたピン番号のハッシュ表
  CiCellPinHash mPinHash;

  // バス名をキーにしたバス番号のハッシュ表
  CiCellPinHash mBusHash;

  // バンドル名をキーにしたバンドル番号のハッシュ表
  CiCellPinHash mBundleHash;

  // セルグループのリスト
  vector<unique_ptr<CiCellGroup>> mGroupList;

  // NPN同値クラスのリスト
  vector<unique_ptr<CiCellClass>> mClassList;

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
