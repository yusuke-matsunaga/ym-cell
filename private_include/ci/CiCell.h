#ifndef CICELL_H
#define CICELL_H

/// @file CiClibl.h
/// @brief CiClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCell.h"
#include "ym/Expr.h"
#include "ym/ShString.h"
#include "ci/CiPin.h"
#include "ci/CiTiming.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiInputPin;
class CiOutputPin;
class CiInoutPin;
class CiBus;
class CiBundle;
class CiTiming;
class CgSignature;

//////////////////////////////////////////////////////////////////////
/// @class CiCell CiCell.h "CiCell.h"
/// @brief ClibCell の実装クラス
///
/// このクラスはデフォルトの仮想関数を実装している．
//////////////////////////////////////////////////////////////////////
class CiCell :
  public ClibCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area                            ///< [in] 面積
  );

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCell() = default;


public:

  /// @brief デストラクタ
  ~CiCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ライブラリの取得
  CiCellLibrary*
  library() const
  {
    return mLibrary;
  }

  /// @brief ID番号の取得
  SizeType
  id() const override;

  /// @brief 名前の取得
  string
  name() const override;

  /// @brief 面積の取得
  ClibArea
  area() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // ピン情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン数の取得
  SizeType
  pin_num() const override;

  /// @brief ピンの取得
  /// @return ピン情報を返す．
  const ClibPin&
  pin(
    SizeType pin_id ///< [in] ピン番号 ( 0 <= pin_id < pin_num() )
  ) const override;

  /// @brief 名前からピン番号の取得
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  pin_id(
    const string& name ///< [in] ピン名
  ) const override;

  /// @brief 名前からピン番号の取得
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  pin_id(
    const ShString& name ///< [in] ピン名
  ) const;

  /// @brief 入力ピン数の取得
  SizeType
  input_num() const override;

  /// @brief 出力ピン数の取得
  SizeType
  output_num() const override;

  /// @brief 入出力ピン数の取得
  SizeType
  inout_num() const override;

  /// @brief 内部ピン数の取得
  SizeType
  internal_num() const override;

  /// @brief 入力ピン+入出力ピン数の取得
  ///
  /// input_num() + inout_num() に等しい．
  SizeType
  input_num2() const override;

  /// @brief 入力ピンの取得
  ///
  /// id >= input_num() の場合には入出力ピンが返される．
  const ClibPin&
  input(
    SizeType id ///< [in] 入力番号 ( 0 <= id < input_num2() )
  ) const override;

  /// @brief 出力ピン+入出力ピン数の取得
  ///
  /// output_num() + inout_num() に等しい．
  SizeType
  output_num2() const override;

  /// @brief 出力ピンの取得
  ///
  /// id >= output_num() の場合には入出力ピンが返される．
  const ClibPin&
  output(
    SizeType id ///< [in] 出力番号 ( 0 <= id < output_num2() )
  ) const override;

  /// @brief 入出力ピンの取得
  const ClibPin&
  inout(
    SizeType id ///< [in] 番号 ( 0 <= id < inout_num() )
  ) const override;

  /// @brief 内部ピンの取得
  const ClibPin&
  internal(
    SizeType id ///< [in] 内部ピン番号 ( 0 <= id < internal_num() )
  ) const override;

  /// @brief バス数の取得
  SizeType
  bus_num() const override;

  /// @brief バスの取得
  const ClibBus&
  bus(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bus_num() )
  ) const override;

  /// @brief 名前からバス番号の取得
  /// @return name という名前のバス番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  bus_id(
    const string& name ///< [in] バス名
  ) const override;

  /// @brief バンドル数の取得
  SizeType
  bundle_num() const override;

  /// @brief バンドルの取得
  const ClibBundle&
  bundle(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bundle_num() )
  ) const override;

  /// @brief 名前からバンドル番号の取得
  /// @return name という名前のバンドル番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  bundle_id(
    const string& name ///< [in] バンドル名
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の数を返す．
  SizeType
  timing_num() const override;

  /// @brief タイミング情報を返す．
  const ClibTiming&
  timing(
    SizeType pos ///< [in] インデックス ( 0 <= pos < timing_num() )
  ) const override;

  /// @brief 条件に合致するタイミング情報のインデックスのリストを返す．
  const vector<SizeType>&
  timing_id_list(
    SizeType ipos,        ///< [in] 開始ピン番号 ( 0 <= ipos < input_num2() )
    SizeType opos,        ///< [in] 終了ピン番号 ( 0 <= opos < output_num2() )
    ClibTimingSense sense ///< [in] タイミング情報の摘要条件
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 機能情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief 組み合わせ論理タイプの時 true を返す．
  bool
  is_logic() const override;

  /// @brief FFタイプの時 true を返す．
  bool
  is_ff() const override;

  /// @brief ラッチタイプの時 true を返す．
  bool
  is_latch() const override;

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief 内部変数1の名前を返す．
  string
  qvar1() const override;

  /// @brief 内部変数1の名前を返す．
  string
  qvar2() const override;

  /// @brief 非同期 clear を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_clear() const override;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const override;

  /// @brief 非同期 preset を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_preset() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var1() const override;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  ClibCPV
  clear_preset_var2() const override;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const override;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const override;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const override;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ID を設定する．
  void
  set_id(
    SizeType id
  )
  {
    mId = id;
  }

  /// @brief 入力ピンを追加する．
  /// @return 生成されたピンを返す．
  CiInputPin*
  add_input(
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance  ///< [in] 立ち下がり時の負荷容量
  );

  /// @brief 出力ピンを追加する．
  /// @return 生成されたピンを返す．
  CiOutputPin*
  add_output(
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
  /// @return 生成されたピンを返す．
  CiInoutPin*
  add_inout(
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
  /// @return 生成されたピンを返す．
  CiInternalPin*
  add_internal(
    const ShString& name               ///< [in] 名前
  );

  /// @brief バスを追加する．
  CiBus*
  add_bus(
    const ShString& name,            ///< [in] 名前
    const ClibBusType* bus_type,     ///< [in] バスタイプ
    vector<const ClibPin*>& pin_list ///< [in] ピンリスト
  );

  /// @brief バンドルを追加する．
  CiBundle*
  add_bundle(
    const ShString& name,            ///< [in] 名前
    vector<const ClibPin*>& pin_list ///< [in] ピンリスト
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
    CiLut* cell_rise,
    CiLut* cell_fall,
    CiLut* rise_transition,
    CiLut* fall_transition
  );

  /// @brief タイミング情報を作る(非線形タイプ2)．
  /// @return 生成されたタイミング番号を返す．
  SizeType
  add_timing_lut2(
    ClibTimingType timing_type,
    const Expr& cond,
    CiLut* rise_transition,
    CiLut* fall_transition,
    CiLut* rise_propagation,
    CiLut* fall_propagation
  );

  /// @brief タイミング情報用のデータ構造を初期化する．
  void
  init_timing_map(
    SizeType input_num, ///< [in] 入力ピン数
    SizeType output_num ///< [in] 出力ピン数
  );

  /// @brief タイミング情報をセットする(単独のタイミング情報)．
  ///
  /// この関数を呼ぶ前に init_timing_map() を呼んでおくこと．
  void
  set_timing(
    SizeType ipin_id,                   ///< [in] 入力ピン番号
    SizeType opin_id,                   ///< [in] 出力ピン番号
    ClibTimingSense timing_sense,       ///< [in] タイミング条件
    SizeType timing_id                  ///< [in] 設定するタイミング番号
  )
  {
    set_timing(ipin_id, opin_id, timing_sense, vector<SizeType>{timing_id});
  }

  /// @brief タイミング情報をセットする(複数のタイミング情報)．
  ///
  /// この関数を呼ぶ前に init_timing_map() を呼んでおくこと．
  void
  set_timing(
    SizeType ipin_id,                   ///< [in] 入力ピン番号
    SizeType opin_id,                   ///< [in] 出力ピン番号
    ClibTimingSense timing_sense,       ///< [in] タイミング条件
    const vector<SizeType>& timing_list ///< [in] 設定するタイミング番号のリスト
  );

  /// @brief シグネチャを返す．
  virtual
  CgSignature
  make_signature() const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピンを登録する．
  void
  reg_pin(
    CiPin* pin ///< [in] 登録するピン
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  CiCellLibrary* mLibrary{nullptr};

  // ID番号
  SizeType mId{CLIB_NULLID};

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea{0};

  // 入力ピン数
  SizeType mInputNum{0};

  // 出力ピン数
  SizeType mOutputNum{0};

  // 入出力ピン数
  SizeType mInoutNum{0};

  // ピンのリスト
  vector<unique_ptr<CiPin>> mPinList;

  // 入力ピン+入出力ピンのリスト
  // サイズ mInputNum + mInoutNum
  vector<const ClibPin*> mInputList;

  // 出力ピン+入出力ピンのリスト
  // サイズ mOutputNum + mInoutNum
  vector<const ClibPin*> mOutputList;

  // 内部ピンのリスト
  vector<const ClibPin*> mInternalList;

  // バスのリスト
  vector<unique_ptr<CiBus>> mBusList;

  // バンドルのリスト
  vector<unique_ptr<CiBundle>> mBundleList;

  // 全体のタイミング情報のリスト
  vector<unique_ptr<CiTiming>> mTimingList;

  // 条件ごとのタイミングIDのリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  vector<vector<SizeType>> mTimingMap;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
