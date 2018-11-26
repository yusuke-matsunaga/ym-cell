#ifndef CICELL_H
#define CICELL_H

/// @file CiClibl.h
/// @brief CiClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCell.h"
#include "ym/ClibObjList.h"
#include "ym/Expr.h"
#include "ym/ShString.h"
#include "ym/Alloc.h"
#include "ym/ODO.h"


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

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCell();

  /// @brief デストラクタ
  ~CiCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  /// @note ここで返される番号は ClibCellLibrary::cell() の引数に対応する．
  int
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
  int
  pin_num() const override;

  /// @brief ピンのリストの取得
  const ClibCellPinList&
  pin_list() const override;

  /// @brief ピンの取得
  /// @param[in] pin_id ピン番号 ( 0 <= pin_id < pin_num() )
  /// @return ピン情報を返す．
  const ClibCellPin&
  pin(int pin_id) const override;

  /// @brief 名前からピン番号の取得
  /// @param[in] name ピン名
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ -1 を返す．
  int
  pin_id(const char* name) const override;

  /// @brief 名前からピン番号の取得
  /// @param[in] name ピン名
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ -1 を返す．
  int
  pin_id(const string& name) const override;

  /// @brief 入力ピン数の取得
  int
  input_num() const override;

  /// @brief 出力ピン数の取得
  int
  output_num() const override;

  /// @brief 入出力ピン数の取得
  int
  inout_num() const override;

  /// @brief 内部ピン数の取得
  int
  internal_num() const override;

  /// @brief 入力ピン+入出力ピン数の取得
  /// @note input_num() + inout_num() に等しい．
  int
  input_num2() const override;

  /// @brief 入力ピンの取得
  /// @param[in] id 入力番号 ( 0 <= id < input_num2() )
  /// @note id >= input_num() の場合には入出力ピンが返される．
  const ClibCellPin&
  input(int id) const override;

  /// @brief 出力ピン+入出力ピン数の取得
  /// @note output_num() + inout_num() に等しい．
  int
  output_num2() const override;

  /// @brief 出力ピンの取得
  /// @param[in] id 出力番号 ( 0 <= id < output_num2() )
  /// @note id >= output_num() の場合には入出力ピンが返される．
  const ClibCellPin&
  output(int id) const override;

  /// @brief 入出力ピンの取得
  /// @param[in] id 番号 ( 0 <= id < inout_num() )
  const ClibCellPin&
  inout(int id) const override;

  /// @brief 内部ピンの取得
  /// @param[in] id 内部ピン番号 ( 0 <= id < internal_num() )
  const ClibCellPin&
  internal(int id) const override;

  /// @brief バス数の取得
  int
  bus_num() const override;

  /// @brief バスの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
  const ClibBus&
  bus(int pos) const override;

  /// @brief 名前からバス番号の取得
  /// @param[in] name バス名
  /// @return name という名前のバス番号を返す．
  ///
  /// なければ -1 を返す．
  int
  bus_id(const string& name) const override;

  /// @brief バンドル数の取得
  int
  bundle_num() const override;

  /// @brief バンドルの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
  const ClibBundle&
  bundle(int pos) const override;

  /// @brief 名前からバンドル番号の取得
  /// @param[in] name バンドル名
  /// @return name という名前のバンドル番号を返す．
  ///
  /// なければ -1 を返す．
  int
  bundle_id(const string& name) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報のリストを返す．
  const ClibTimingList&
  timing_list() const override;

  /// @brief 条件に合致するタイミング情報のリストを返す．
  /// @param[in] ipos 開始ピン番号 ( 0 <= ipos < input_num2() )
  /// @param[in] opos 終了ピン番号 ( 0 <= opos < output_num2() )
  /// @param[in] timing_sense タイミング情報の摘要条件
  const ClibTimingList&
  timing_list(int ipos,
	      int opos,
	      ClibTimingSense sense) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 属している ClibCellGroup を返す．
  const ClibCellGroup&
  cell_group() const override;

  /// @brief 組み合わせ論理セルの時に true を返す．
  bool
  is_logic() const override;

  /// @brief FFセルの時に true を返す．
  bool
  is_ff() const override;

  /// @brief ラッチセルの時に true を返す．
  bool
  is_latch() const override;

  /// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
  bool
  is_fsm() const override;

  /// @brief 出力の論理式を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  bool
  has_logic(int pin_id) const override;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(int pin_id) const override;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  bool
  has_tristate(int pin_id) const override;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  /// @note 通常の論理セルの場合には定数0を返す．
  Expr
  tristate_expr(int pin_id) const override;

  /// @brief FFセルの場合にFFのピン情報を得る．
  ClibFFInfo
  ff_info() const override;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  next_state_expr() const override;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock_expr() const override;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  clock2_expr() const override;

  /// @brief ラッチセルの場合にFFのピン情報を得る．
  ClibLatchInfo
  latch_info() const override;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  data_in_expr() const override;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  enable_expr() const override;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  /// @note それ以外の型の場合の返り値は不定
  Expr
  enable2_expr() const override;

  /// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
  bool
  has_clear() const override;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  /// @note クリア端子がない場合の返り値は不定
  Expr
  clear_expr() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
  bool
  has_preset() const override;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  /// @note プリセット端子がない場合の返り値は不定
  Expr
  preset_expr() const override;

  /// @brief clear_preset_var1 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  int
  clear_preset_var1() const override;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  int
  clear_preset_var2() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  void
  dump(ODO& s) const override;


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

  /// @brief 名前からピン番号の取得
  /// @param[in] name ピン名
  /// @return name という名前のピン番号を返す．
  ///
  /// なければ -1 を返す．
  int
  pin_id(const ShString& name) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  CiCellLibrary* mLibrary;

  // ID番号
  int mId;

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea;

  // ピンのリスト
  ClibCellPinList mPinList;

  // 入力ピン数
  int mInputNum;

  // 出力ピン数
  int mOutputNum;

  // 入出力ピン数
  int mInOutNum;

  // 入力ピン+入出力ピンのリスト
  ClibCellPinList mInputList;

  // 出力ピン+入出力ピンのリスト
  ClibCellPinList mOutputList;

  // 内部ピンのリスト
  ClibCellPinList mInternalList;

  // バス数
  int mBusNum;

  // バスピンの配列
  CiBus* mBusArray;

  // バンドル数
  int mBundleNum;

  // バンドルピンの配列
  CiBundle* mBundleArray;

  // 全体のタイミング情報のリスト
  ClibTimingList mTimingList;

  // 条件ごとのタイミング情報のリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  ClibTimingList* mTimingMap;

  // セルグループ
  const ClibCellGroup* mCellGroup;

  // ハッシュ表のリンクポインタ
  CiCell* mLink;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
