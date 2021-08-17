#ifndef CIPIN_H
#define CIPIN_H

/// @file CiCellPin.h
/// @brief CiCellPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellPin.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/Expr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class ClibCellPinBase CiCellPin.h "CiCellPin.h"
/// @brief ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiCellPin :
  public ClibCellPin
{
  friend class CiCell;
  friend class CiCellPinHash;

protected:

  /// @brief コンストラクタ
  CiCellPin(
    const ShString& name ///< [in] ピン名
  );

  /// @brief デストラクタ
  ~CiCellPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン番号を返す．
  int
  pin_id() const override;

  /// @brief ピン名を返す．
  string
  name() const override;

  /// @brief 入力ピンの時に true を返す．
  bool
  is_input() const override;

  /// @brief 出力ピンの時に true を返す．
  bool
  is_output() const override;

  /// @brief 入出力ピンの時に true を返す．
  bool
  is_inout() const override;

  /// @brief 内部ピンの時に true を返す．
  bool
  is_internal() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  int
  input_id() const override;

  /// @brief 負荷容量を返す．
  ClibCapacitance
  capacitance() const override;

  /// @brief 立ち上がり時の負荷容量を返す．
  ClibCapacitance
  rise_capacitance() const override;

  /// @brief 立ち下がり時の負荷容量を返す．
  ClibCapacitance
  fall_capacitance() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  /// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  int
  output_id() const override;

  /// @brief 論理式を持っているときに true を返す．
  bool
  has_function() const override;

  /// @brief 機能を表す論理式を返す．
  Expr
  function() const override;

  /// @brief three_state 属性を持っているときに true を返す．
  bool
  has_three_state() const override;

  /// @brief three_state 論理式を返す．
  Expr
  three_state() const override;

  /// @brief 最大ファンアウト容量を返す．
  ClibCapacitance
  max_fanout() const override;

  /// @brief 最小ファンアウト容量を返す．
  ClibCapacitance
  min_fanout() const override;

  /// @brief 最大負荷容量を返す．
  ClibCapacitance
  max_capacitance() const override;

  /// @brief 最小負荷容量を返す．
  ClibCapacitance
  min_capacitance() const override;

  /// @brief 最大遷移時間を返す．
  ClibTime
  max_transition() const override;

  /// @brief 最小遷移時間を返す．
  ClibTime
  min_transition() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  /// @note 内部ピンの時のみ意味を持つ．
  int
  internal_id() const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief dump 用の共通情報を出力する．
  void
  dump_common(
    ostream& s ///< [in] 出力ストリーム
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハッシュ表のためのリンク
  CiCellPin* mLink;

  // 親のセル
  CiCell* mCell;

  // ピン番号
  int mId;

  // 名前
  ShString mName;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの入力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInputPin :
  public CiCellPin
{
  friend class CiCell;
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiInputPin(
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance  ///< [in] 立ち下がり時の負荷容量
  );

  /// @brief デストラクタ
  ~CiInputPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 入力ピンの時に true を返す．
  bool
  is_input() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  int
  input_id() const override;

  /// @brief 負荷容量を返す．
  ClibCapacitance
  capacitance() const override;

  /// @brief 立ち上がり時の負荷容量を返す．
  ClibCapacitance
  rise_capacitance() const override;

  /// @brief 立ち下がり時の負荷容量を返す．
  ClibCapacitance
  fall_capacitance() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピン番号
  int mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの出力ピンと入出力ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiOutputPinBase :
  public CiCellPin
{
  friend class CiCell;

protected:

  /// @brief コンストラクタ
  CiOutputPinBase(
    const ShString& name,            ///< [in] ピン名
    bool has_logic,                  ///< [in] 論理式を持つとき true にするフラグ
    const Expr& logic_expr,          ///< [in] 論理式
    const Expr& tristate_expr,       ///< [in] tristate 条件式
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最小負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition          ///< [in] 最小遷移時間
  );

  /// @brief デストラクタ
  ~CiOutputPinBase();


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  /// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  int
  output_id() const override;

  /// @brief 論理式を持っているときに true を返す．
  bool
  has_function() const override;

  /// @brief 機能を表す論理式を返す．
  Expr
  function() const override;

  /// @brief three_state 属性を持っているときに true を返す．
  bool
  has_three_state() const override;

  /// @brief three_state 論理式を返す．
  Expr
  three_state() const override;

  /// @brief 最大ファンアウト容量を返す．
  ClibCapacitance
  max_fanout() const override;

  /// @brief 最小ファンアウト容量を返す．
  ClibCapacitance
  min_fanout() const override;

  /// @brief 最大負荷容量を返す．
  ClibCapacitance
  max_capacitance() const override;

  /// @brief 最小負荷容量を返す．
  ClibCapacitance
  min_capacitance() const override;

  /// @brief 最大遷移時間を返す．
  ClibTime
  max_transition() const override;

  /// @brief 最小遷移時間を返す．
  ClibTime
  min_transition() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力ピン番号
  int mOutputId;

  // 論理式を持っているかどうかを表すフラグ
  ymuint8 mHasFunction;

  // 出力の論理式
  Expr mFunction;

  // three_state 属性の論理式
  Expr mThreeState;

  // ファンアウトの負荷
  ClibCapacitance mFanoutLoad;

  // 最大ファンアウト容量
  ClibCapacitance mMaxFanout;

  // 最小ファンアウト容量
  ClibCapacitance mMinFanout;

  // 最大負荷容量
  ClibCapacitance mMaxCapacitance;

  // 最小負荷容量
  ClibCapacitance mMinCapacitance;

  // 最大遷移時間
  ClibTime mMaxTransition;

  // 最小遷移時間
  ClibTime mMinTransition;

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの出力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiOutputPin :
  public CiOutputPinBase
{
  friend class CiCell;
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiOutputPin(
    const ShString& name,            ///< [in] ピン名
    bool has_logic,                  ///< [in] 論理式を持つとき true にするフラグ
    const Expr& logic_expr,          ///< [in] 論理式
    const Expr& tristate_expr,       ///< [in] tristate 条件式
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最小負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition          ///< [in] 最小遷移時間
  );

  /// @brief デストラクタ
  ~CiOutputPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 出力ピンの時に true を返す．
  bool
  is_output() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInoutPin CiCellPin.h "CiCellPin.h"
/// @brief セルの入出力ピンを表すクラス
/// @note 多重継承はオーバーヘッドがかかるので愚直な実装を用いている．
//////////////////////////////////////////////////////////////////////
class CiInoutPin :
  public CiOutputPinBase
{
  friend class CiCell;
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiInoutPin(
    const ShString& name,             ///< [in] ピン名
    bool has_logic,                   ///< [in] 論理式を持つとき true にするフラグ
    const Expr& logic_expr,           ///< [in] 論理式
    const Expr& tristate_expr,        ///< [in] tristate 条件式
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance, ///< [in] 立ち下がり時の負荷容量
    ClibCapacitance max_fanout,       ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,       ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance,  ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance,  ///< [in] 最小負荷容量
    ClibTime max_transition,          ///< [in] 最大遷移時間
    ClibTime min_transition           ///< [in] 最小遷移時間
  );

  /// @brief デストラクタ
  ~CiInoutPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 入出力ピンの時に true を返す．
  bool
  is_inout() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  int
  input_id() const override;

  /// @brief 負荷容量を返す．
  ClibCapacitance
  capacitance() const override;

  /// @brief 立ち上がり時の負荷容量を返す．
  ClibCapacitance
  rise_capacitance() const override;

  /// @brief 立ち下がり時の負荷容量を返す．
  ClibCapacitance
  fall_capacitance() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピン番号
  int mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInternalPin CiCellPin.h "CiCellPin.h"
/// @brief セルの内部ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInternalPin :
  public CiCellPin
{
  friend class CiCell;
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiInternalPin(
    const ShString& name ///< [in] ピン名
  );

  /// @brief デストラクタ
  ~CiInternalPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 内部ピンの時に true を返す．
  bool
  is_internal() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  /// @note 内部ピンの時のみ意味を持つ．
  int
  internal_id() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 内部ピン番号
  int mInternalId;

};

END_NAMESPACE_YM_CLIB

#endif // CIPIN_H
