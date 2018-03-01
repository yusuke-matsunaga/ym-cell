#ifndef CICELL_H
#define CICELL_H

/// @file CiClibl.h
/// @brief CiClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCell.h"
#include "ym/Expr.h"
#include "ym/ShString.h"
#include "ym/Alloc.h"
#include "ym/ODO.h"

#include "ci/CiCellPinList.h"
#include "ci/CiTimingList.h"

BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellPin;
class CiInputPin;
class CiOutputPin;
class CiInoutPin;
class CiInternalPin;
class CiBus;
class CiBundle;
class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @class CiCell CiCell.h "CiCell.h"
/// @brief Clib の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCell :
  public ClibCell
{
  friend class CiCellLibrary;
  friend class CiCellHash;

protected:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] internal_list 内部ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  /// @param[in] alloc メモリアロケータ
  CiCell(CiCellLibrary* library,
	 const ShString& name,
	 ClibArea area,
	 const vector<CiInputPin*>& input_list,
	 const vector<CiOutputPin*>& output_list,
	 const vector<CiInoutPin*>& inout_list,
	 const vector<CiInternalPin*>& internal_list,
	 const vector<CiBus*>& bus_list,
	 const vector<CiBundle*>& bundle_list,
	 const vector<CiTiming*>& timing_list,
	 Alloc& alloc);

  /// @brief デストラクタ
  virtual
  ~CiCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  /// @note ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
  virtual
  int
  id() const;

  /// @brief 名前の取得
  virtual
  string
  name() const;

  /// @brief 面積の取得
  virtual
  ClibArea
  area() const;


public:
  //////////////////////////////////////////////////////////////////////
  // ピン情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン数の取得
  virtual
  int
  pin_num() const;

  /// @brief ピンのリストの取得
  virtual
  const ClibCellPinList&
  pin_list() const;

  /// @brief 名前からピンの取得
  /// @param[in] name ピン名
  /// @return name という名前をピンを返す．
  /// @note なければ nullptr を返す．
  virtual
  const ClibCellPin*
  pin(const char* name) const;

  /// @brief 名前からピンの取得
  /// @param[in] name ピン名
  /// @return name という名前をピンを返す．
  /// @note なければ nullptr を返す．
  virtual
  const ClibCellPin*
  pin(const string& name) const;

  /// @brief 入力ピン数の取得
  virtual
  int
  input_num() const;

  /// @brief 出力ピン数の取得
  virtual
  int
  output_num() const;

  /// @brief 入出力ピン数の取得
  virtual
  int
  inout_num() const;

  /// @brief 内部ピン数の取得
  virtual
  int
  internal_num() const;

  /// @brief 入力ピン+入出力ピン数の取得
  /// @note input_num() + inout_num() に等しい．
  virtual
  int
  input_num2() const;

  /// @brief 入力ピンの取得
  /// @param[in] id 入力番号 ( 0 <= id < input_num2() )
  /// @note id >= input_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin*
  input(int id) const;

  /// @brief 出力ピン+入出力ピン数の取得
  /// @note output_num() + inout_num() に等しい．
  virtual
  int
  output_num2() const;

  /// @brief 出力ピンの取得
  /// @param[in] id 出力番号 ( 0 <= id < output_num2() )
  /// @note id >= output_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin*
  output(int id) const;

  /// @brief 入出力ピンの取得
  /// @param[in] id 番号 ( 0 <= id < inout_num() )
  virtual
  const ClibCellPin*
  inout(int id) const;

  /// @brief 内部ピンの取得
  /// @param[in] id 内部ピン番号 ( 0 <= id < internal_num() )
  virtual
  const ClibCellPin*
  internal(int id) const;

  /// @brief バス数の取得
  virtual
  int
  bus_num() const;

  /// @brief バスの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
  virtual
  const ClibBus*
  bus(int pos) const;

  /// @brief 名前からバスの取得
  /// @param[in] name バス名
  /// @return name という名前のバスを返す．
  /// @note なければ nullptr を返す．
  virtual
  const ClibBus*
  bus(const string& name) const;

  /// @brief バンドル数の取得
  virtual
  int
  bundle_num() const;

  /// @brief バンドルの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
  virtual
  const ClibBundle*
  bundle(int pos) const;

  /// @brief 名前からバンドルの取得
  virtual
  const ClibBundle*
  bundle(const string& name) const;


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報のリストを返す．
  virtual
  const ClibTimingList&
  timing_list() const;

  /// @brief 条件に合致するタイミング情報のリストを返す．
  /// @param[in] ipos 開始ピン番号 ( 0 <= ipos < input_num2() )
  /// @param[in] opos 終了ピン番号 ( 0 <= opos < output_num2() )
  /// @param[in] timing_sense タイミング情報の摘要条件
  virtual
  const ClibTimingList&
  timing_list(int ipos,
	      int opos,
	      ClibTimingSense sense) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 属している ClibCellGroup を返す．
  virtual
  const ClibCellGroup*
  cell_group() const;

  /// @brief 組み合わせ論理セルの時に true を返す．
  virtual
  bool
  is_logic() const;

  /// @brief FFセルの時に true を返す．
  virtual
  bool
  is_ff() const;

  /// @brief ラッチセルの時に true を返す．
  virtual
  bool
  is_latch() const;

  /// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
  virtual
  bool
  is_fsm() const;

  /// @brief 出力の論理式を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  virtual
  bool
  has_logic(int pin_id) const;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  virtual
  bool
  has_logic() const;

  /// @brief 論理セルの場合に出力の論理式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  virtual
  Expr
  logic_expr(int pin_id) const;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  virtual
  bool
  has_tristate(int pin_id) const;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  /// @note 通常の論理セルの場合には定数0を返す．
  virtual
  Expr
  tristate_expr(int pin_id) const;

  /// @brief FFセルの場合にFFのピン情報を得る．
  virtual
  ClibFFInfo
  ff_info() const;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  next_state_expr() const;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock_expr() const;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock2_expr() const;

  /// @brief ラッチセルの場合にFFのピン情報を得る．
  virtual
  ClibLatchInfo
  latch_info() const;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  data_in_expr() const;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable_expr() const;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable2_expr() const;

  /// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
  virtual
  bool
  has_clear() const;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  /// @note クリア端子がない場合の返り値は不定
  virtual
  Expr
  clear_expr() const;

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  virtual
  bool
  has_preset() const;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  virtual
  Expr
  preset_expr() const;

  /// @brief clear_preset_var1 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  virtual
  int
  clear_preset_var1() const;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  virtual
  int
  clear_preset_var2() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループを設定する．
  void
  set_group(const ClibCellGroup* group);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  CiCellLibrary* mLibrary;

  // ハッシュ表のためのリンク
  CiCell* mLink;

  // ID番号
  int mId;

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea;

  // ピンのリスト
  CiCellPinList mPinList;

  // 入力ピン数
  int mInputNum;

  // 出力ピン数
  int mOutputNum;

  // 入出力ピン数
  int mInOutNum;

  // 入力ピン+入出力ピンのリスト
  CiCellPinList mInputList;

  // 出力ピン+入出力ピンのリスト
  CiCellPinList mOutputList;

  // 内部ピンのリスト
  CiCellPinList mInternalList;

  // バス数
  int mBusNum;

  // バスピンの配列
  CiBus* mBusArray;

  // バンドル数
  int mBundleNum;

  // バンドルピンの配列
  CiBundle* mBundleArray;

  // 全体のタイミング情報のリスト
  CiTimingList mTimingList;

  // 条件ごとのタイミング情報のリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  CiTimingList* mTimingMap;

  // セルグループ
  const ClibCellGroup* mClibCellGroup;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
