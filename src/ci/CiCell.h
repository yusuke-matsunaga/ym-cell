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


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellPin;
class CiBus;
class CiBundle;
class CiTiming;

struct CiTimingArray
{
  ymuint mNum;
  CiTiming* mArray[1];
};

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
  /// @param[in] id ID番号
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] ni 入力ピン数
  /// @param[in] no 出力ピン数
  /// @param[in] nio 入出力ピン数
  /// @param[in] nit 内部ピン数
  /// @param[in] nb バス数
  /// @param[in] nc バンドル数
  /// @param[in] output_array 出力の情報の配列(*1)
  /// @param[in] logic_array 出力の論理式の配列
  /// @param[in] tristated_array トライステート条件の論理式の配列
  /// @param[in] alloc メモリアロケータ
  /// *1: - false 論理式なし
  ///     - true 論理式あり
  CiCell(CiCellLibrary* library,
	 ymuint id,
	 const ShString& name,
	 ClibArea area,
	 ymuint ni,
	 ymuint no,
	 ymuint nio,
	 ymuint nit,
	 ymuint nb,
	 ymuint nc,
	 const vector<bool>& output_array,
	 const vector<Expr>& logic_array,
	 const vector<Expr>& tristate_array,
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
  ymuint
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
  ymuint
  pin_num() const;

  /// @brief ピンの取得
  /// @param[in] id ピン番号 ( 0 <= id < pin_num() )
  virtual
  const ClibCellPin*
  pin(ymuint id) const;

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
  ymuint
  input_num() const;

  /// @brief 出力ピン数の取得
  virtual
  ymuint
  output_num() const;

  /// @brief 入出力ピン数の取得
  virtual
  ymuint
  inout_num() const;

  /// @brief 内部ピン数の取得
  virtual
  ymuint
  internal_num() const;

  /// @brief 入力ピン+入出力ピン数の取得
  /// @note input_num() + inout_num() に等しい．
  virtual
  ymuint
  input_num2() const;

  /// @brief 入力ピンの取得
  /// @param[in] input_id 入力番号 ( 0 <= pos < input_num2() )
  /// @note pos >= input_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin*
  input(ymuint input_id) const;

  /// @brief 出力ピン+入出力ピン数の取得
  /// @note output_num() + inout_num() に等しい．
  virtual
  ymuint
  output_num2() const;

  /// @brief 出力ピンの取得
  /// @param[in] output_id 出力番号 ( 0 <= pos < output_num2() )
  /// @note pos >= output_num() の場合には入出力ピンが返される．
  virtual
  const ClibCellPin*
  output(ymuint output_id) const;

  /// @brief 内部ピンの取得
  /// @param[in] internal_id 内部ピン番号 ( 0 <= internal_id < internal_num() )
  virtual
  const ClibCellPin*
  internal(ymuint internal_id) const;

  /// @brief バス数の取得
  virtual
  ymuint
  bus_num() const;

  /// @brief バスの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
  virtual
  const ClibBus*
  bus(ymuint pos) const;

  /// @brief 名前からバスの取得
  /// @param[in] name バス名
  /// @return name という名前のバスを返す．
  /// @note なければ nullptr を返す．
  virtual
  const ClibBus*
  bus(const string& name) const;

  /// @brief バンドル数の取得
  virtual
  ymuint
  bundle_num() const;

  /// @brief バンドルの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
  virtual
  const ClibBundle*
  bundle(ymuint pos) const;

  /// @brief 名前からバンドルの取得
  virtual
  const ClibBundle*
  bundle(const string& name) const;


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の数の取得
  virtual
  ymuint
  timing_num() const;

  /// @brief タイミング情報の取得
  /// @param[in] pos 位置番号 ( 0 <= pos < timing_num() )
  virtual
  const ClibTiming*
  timing(ymuint pos) const;

  /// @brief 条件に合致するタイミング情報の数の取得
  /// @param[in] ipos 開始ピン番号 ( 0 <= ipos < input_num2() )
  /// @param[in] opos 終了ピン番号 ( 0 <= opos < output_num2() )
  /// @param[in] timing_sense タイミング情報の摘要条件
  virtual
  ymuint
  timing_num(ymuint ipos,
	     ymuint opos,
	     ClibTimingSense sense) const;

  /// @brief タイミング情報の取得
  /// @param[in] ipos 開始ピン番号
  /// @param[in] opos 終了ピン番号
  /// @param[in] timing_sense タイミング情報の摘要条件
  /// @param[in] pos 位置番号 ( 0 <= pos < timing_num(ipos, opos, timing_sense) )
  /// @return 条件に合致するタイミング情報を返す．
  virtual
  const ClibTiming*
  timing(ymuint ipos,
	 ymuint opos,
	 ClibTimingSense sense,
	 ymuint pos) const;


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
  has_logic(ymuint pin_id) const;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  virtual
  bool
  has_logic() const;

  /// @brief 論理セルの場合に出力の論理式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  virtual
  Expr
  logic_expr(ymuint pin_id) const;

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  virtual
  bool
  has_tristate(ymuint pin_id) const;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  /// @param[in] pin_id 出力ピン番号 ( 0 <= pin_id < output_num2() )
  /// @note 論理式中の変数番号は入力ピン番号に対応する．
  /// @note 通常の論理セルの場合には定数0を返す．
  virtual
  Expr
  tristate_expr(ymuint pin_id) const;

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
  ymuint
  clear_preset_var1() const;

  /// @brief clear_preset_var2 の取得
  /// @retval 0 "L"
  /// @retval 1 "H"
  /// @note FFセルとラッチセルの時に意味を持つ．
  virtual
  ymuint
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
  virtual
  void
  set_group(const ClibCellGroup* group);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  CiCellLibrary* mLibrary;

  // ハッシュ表のためのリンク
  CiCell* mLink;

  // ID番号
  ymuint mId;

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea;

  // ピン数
  ymuint mPinNum;

  // ピンの配列
  CiCellPin** mPinArray;

  // 入力ピン数
  ymuint mInputNum;

  // 出力ピン数
  ymuint mOutputNum;

  // 内部ピン数
  ymuint mInternalNum;

  // 入力ピンの配列
  CiCellPin** mInputArray;

  // 出力ピンの配列
  CiCellPin** mOutputArray;

  // 内部ピンの配列
  CiCellPin** mInternalArray;

  // バス数
  ymuint mBusNum;

  // バスピンの配列
  CiBus* mBusArray;

  // バンドル数
  ymuint mBundleNum;

  // バンドルピンの配列
  CiBundle* mBundleArray;

  // タイミング情報の数
  ymuint mTimingNum;

  // タイミング情報を格納する配列
  CiTiming** mTimingArray;

  // 条件ごとのタイミング情報のリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力ピン数)  x 2
  CiTimingArray** mTimingMap;

  // セルグループ
  const ClibCellGroup* mClibCellGroup;

  // 出力の情報を格納する配列
  // サイズは output_num2()
  ymuint8* mLTArray;

  // 出力の論理式を格納する配列
  // サイズは output_num2()
  Expr* mLogicArray;

  // 出力のトライステート条件を格納する配列
  // サイズは output_num2()
  Expr* mTristateArray;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
