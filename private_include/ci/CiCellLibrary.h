﻿#ifndef CICELLLIBRARY_H
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
#include "ym/ShString.h"
#include "ym/logic.h"
#include "ci/CiPatMgr.h"
#include "ci/CiCellNameHash.h"
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"
#include "ci/conv_list.h"


BEGIN_NAMESPACE_YM_CLIB

class CiBusType;
class CiCell;
class CiCellClass;
class CiCellGroup;
class CiInternalPin;
class CiLut;
class CiLutTemplate;
class CiTiming;
class Serializer;

//////////////////////////////////////////////////////////////////////
/// @class CiCellLibrary CiCellLibrary.h "CiCellLibrary.h"
/// @brief ClibCellLibrary の実装クラス
///
/// 本来はライブラリ -> セル -> ピン という風に階層構造を持つが，
/// 個々のオブジェクトの所有権的にはすべてライブラリに属していると考える．
/// 逆にすべての要素に対する参照は親のライブラリに対する参照とみなす．
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

  /// @brief 区間インデックスのタイプの取得
  ClibVarType
  piece_type() const
  {
    return mPieceType;
  }

  /// @brief 区間のリストの取得
  vector<double>
  piece_define() const
  {
    return mPieceDefine;
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

  /// @brief 位置からセルの取得
  const CiCell*
  cell(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < cell_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < cell_num() );
    return mCellList[pos].get();
  }

  /// @brief 名前からのセルの取得
  const CiCell*
  cell(
    const string& name
  ) const
  {
    return cell(ShString{name});
  }

  /// @brief 名前からのセルの取得
  const CiCell*
  cell(
    const ShString& name
  ) const
  {
    if ( mCellDict.count(name) > 0 ) {
      return mCellDict.at(name);
    }
    return nullptr;
  }

  /// @brief セルのリストの取得
  vector<const CiCell*>
  cell_list() const
  {
    return conv_list(mCellList);
  }

  /// @brief セルグループ数の取得
  SizeType
  cell_group_num() const
  {
    return mCellGroupList.size();
  }

  /// @brief セルグループの取得
  const CiCellGroup*
  cell_group(
    SizeType pos ///< [in] 位置 ( 0 <= pos < cell_group_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < cell_group_num() );
    return mCellGroupList[pos].get();
  }

  /// @brief セルグループのリストの取得
  vector<const CiCellGroup*>
  cell_group_list() const
  {
    return conv_list(mCellGroupList);
  }

  /// @brief NPN同値クラス数の取得
  SizeType
  npn_class_num() const
  {
    return mCellClassList.size();
  }

  /// @brief NPN同値クラスの取得
  const CiCellClass*
  npn_class(
    SizeType pos ///< [in] 位置 ( 0 <= pos < npn_class_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < npn_class_num() );
    return mCellClassList[pos].get();
  }

  /// @brief NPN同値クラス番号のリストの取得
  vector<const CiCellClass*>
  npn_class_list() const
  {
    return conv_list(mCellClassList);
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 論理セルグループの情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数0セルのグループを返す．
  const CiCellGroup*
  const0_func() const
  {
    // 決め打ち
    return mLogicGroup[0];
  }

  /// @brief 定数1セルのグループを返す．
  const CiCellGroup*
  const1_func() const
  {
    // 決め打ち
    return mLogicGroup[1];
  }

  /// @brief バッファセルのグループを返す．
  const CiCellGroup*
  buf_func() const
  {
    // 決め打ち
    return mLogicGroup[2];
  }

  /// @brief インバータセルのグループを返す．
  const CiCellGroup*
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
  const CiCellClass*
  simple_ff_class(
    bool master_slave,   ///< [in] master/slave 型の時 true
    bool has_xq,         ///< [in] xq 端子を持つ時 true
    ClibSeqType seq_type ///< [in] clear 端子と preset 端子の有無
  ) const;

  /// @brief 単純な型のFFクラスを返す．
  ///
  /// - cpv1, cpv2 の値は has_clear, has_preset がともに true
  ///   の時のみ意味を持つ．
  /// - 該当するセルがないときでも空のセルクラスが返される．
  const CiCellClass*
  simple_ff_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_xq,       ///< [in] xq 端子を持つ時 true
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
  const CiCellClass*
  simple_latch_class(
    bool master_slave,   ///< [in] master/slave 型の時 true
    bool has_xq,         ///< [in] xq 端子を持つ時 true
    ClibSeqType seq_type ///< [in] clear 端子と preset 端子の有無
  ) const;

  /// @brief 単純な型のラッチクラスを返す．
  ///
  /// - cpv1, cpv2 の値は has_clear, has_preset がともに true
  ///   の時のみ意味を持つ．
  /// - 該当するセルがないときでも空のセルクラスが返される．
  const CiCellClass*
  simple_latch_class(
    bool master_slave, ///< [in] master/slave 型の時 true
    bool has_xq,       ///< [in] xq 端子を持つ時 true
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
  static
  CiCellLibrary*
  restore(
    istream& s ///< [in] 入力ストリーム
  );

  /// @brief restore() の本体
  void
  _restore(
    Deserializer& s
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

  /// @brief 区間関係のパラメータを設定する．
  void
  set_piece_params(
    ClibVarType piece_type,          ///< [in] 区間のタイプ
    const vector<double>& piece_list ///< [in] 区間のリスト
  )
  {
    mPieceType = piece_type;
    mPieceDefine = piece_list;
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

  /// @brief 設定後の最終処理を行う．
  void
  wrap_up();

  /// @brief セルグループ/セルクラスの設定を行なう．
  void
  compile();


public:
  //////////////////////////////////////////////////////////////////////
  // CiXXX の生成関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1次元の LUT のテンプレートを作る．
  CiLutTemplate*
  add_lut_template1(
    ClibVarType var_type1,
    const vector<double>& index_list1
  );

  /// @brief 2次元の LUT のテンプレートを作る．
  CiLutTemplate*
  add_lut_template2(
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2
  );

  /// @brief 3次元の LUT のテンプレートを作る．
  CiLutTemplate*
  add_lut_template3(
    ClibVarType var_type1,
    const vector<double>& index_list1,
    ClibVarType var_type2,
    const vector<double>& index_list2,
    ClibVarType var_type3,
    const vector<double>& index_list3
  );

  /// @brief セルクラスを作る．
  CiCellClass*
  add_cell_class(
    const vector<ClibIOMap>& idmap_list ///< [in] 同位体変換のリスト
  );

  /// @brief セルグループを作る．
  CiCellGroup*
  add_cell_group(
    const CiCellClass* rep_class, ///< [in] 親のセルクラス
    const ClibIOMap& iomap        ///< [in] 変換マップ
  );

  /// @brief 論理セルを追加する．
  CiCell*
  add_logic_cell(
    const ShString& name,     ///< [in] 名前
    ClibArea area             ///< [in] 面積
  );

  /// @brief FFセルを追加する．
  CiCell*
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
  CiCell*
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
  CiCell*
  add_fsm_cell(
    const ShString& name,      ///< [in] 名前
    ClibArea area              ///< [in] 面積
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
    return mCellClassList[id].get();
  }

  /// @brief セルグループを得る．
  CiCellGroup*
  _cell_group(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mCellGroupList[id].get();
  }

  /// @brief セルを得る．
  CiCell*
  _cell(
    SizeType id ///< [in] ID番号
  ) const
  {
    return mCellList[id].get();
  }

  /// @brief パタンを得る．
  const CiPatGraph*
  _pat_graph(
    SizeType id ///< [in] ID番号
  ) const
  {
    return &mPatMgr.pat(id);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // dump() で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素をシリアライズする．
  void
  serialize(
    Serializer& s ///< [in] シリアライザ
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // restore で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 'capacitive_load_unit' を読み込む．
  void
  restore_capacitive_load_unit(
    Deserializer& s ///< [in] デシリアライザ
  );


public:
  //////////////////////////////////////////////////////////////////////
  // ピンハッシュ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン名からピンを取り出す．
  ///
  /// 見つからない場合は nullptr を返す．
  const CiPin*
  find_pin(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] ピン名
  ) const
  {
    return mPinDict.get(cell, name);
  }

  /// @brief バス名からバスを取り出す．
  ///
  /// 見つからない場合は nullptr を返す．
  const CiBus*
  find_bus(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] バス名
  ) const
  {
    return mBusDict.get(cell, name);
  }

  /// @brief バンドル名からバンドル番号を取り出す．
  ///
  /// 見つからない場合は nullptr を返す．
  const CiBundle*
  find_bundle(
    const CiCell* cell, ///< [in] セル番号
    ShString name       ///< [in] バンドル名
  ) const
  {
    return mBundleDict.get(cell, name);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をクリアする．
  void
  clear();

  /// @brief セルを登録する．
  /// @return セルを返す．
  CiCell*
  reg_cell(
    unique_ptr<CiCell>& ptr ///< [in] セルへのポインタ
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

  // 区間のタイプ
  ClibVarType mPieceType;

  // 区間(の下限)のリスト
  vector<double> mPieceDefine;

  // バスタイプのリスト
  vector<unique_ptr<CiBusType>> mBusTypeList;

  // 遅延テンプレートの実体のリスト
  vector<unique_ptr<CiLutTemplate>> mLutTemplateList;

  // セルの所有権管理用のリスト
  vector<unique_ptr<CiCell>> mCellList;

  // 名前をキーにしたセルの辞書
  unordered_map<ShString, const CiCell*> mCellDict;

  // セルとピン名をキーにしたピンの辞書
  CiCellNameHash<CiPin> mPinDict;

  // セルとバス名をキーにしたバスの辞書
  CiCellNameHash<CiBus> mBusDict;

  // セルとバンドル名をキーにしたバンドルの辞書
  CiCellNameHash<CiBundle> mBundleDict;

  // セルグループの所有権管理用のリスト
  vector<unique_ptr<CiCellGroup>> mCellGroupList;

  // NPN同値クラスの所有権管理用のリスト
  vector<unique_ptr<CiCellClass>> mCellClassList;

  // 論理セルグループの情報
  // 0: 定数0
  // 1: 定数1
  // 2: バッファ
  // 3: インバータ
  const CiCellGroup* mLogicGroup[4];

  // 単純なFFクラスの情報
  // インデックスは CiSeqInfo で作る．
  vector<const CiCellClass*> mSimpleFFClass;

  // 単純なラッチクラスの情報
  // インデックスは CiSeqInfo で作る．
  vector<const CiCellClass*> mSimpleLatchClass;

  // パタングラフを管理するクラス
  CiPatMgr mPatMgr;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLLIBRARY_H
