#ifndef CICELL_H
#define CICELL_H

/// @file CiCell.h
/// @brief CiCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibArea.h"
#include "ym/logic.h"
#include "ym/ShString.h"
#include "ci/CiLibObj.h"
#include "ci/CiPin.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiInputPin;
class CiOutputPin;
class CiInoutPin;
class CiInternalPin;
class CiBundle;
class CiBus;
class CiTiming;
class CgSignature;
class Serializer;
class Deserializer;

//////////////////////////////////////////////////////////////////////
/// @class CiCell CiCell.h "CiCell.h"
/// @brief ClibCell の実装クラス
///
/// このクラスはデフォルトの仮想関数を実装している．
//////////////////////////////////////////////////////////////////////
class CiCell :
  public CiLibObj
{
public:

  /// @brief restore() 用のコンストラクタ
  CiCell(
    const CiCellLibrary* lib ///< [in] 親のライブラリ
  ) : CiLibObj{lib}
  {
  }

  /// @brief コンストラクタ
  CiCell(
    const CiCellLibrary* lib, ///< [in] 親のライブラリ
    const ShString& name,     ///< [in] 名前
    ClibArea area             ///< [in] 面積
  ) : CiLibObj{lib},
      mName{name},
      mArea{area}
  {
  }

  /// @brief デストラクタ
  virtual
  ~CiCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const
  {
    return mName;
  }

  /// @brief 名前の取得
  ShString
  _name() const
  {
    return mName;
  }

  /// @brief 面積の取得
  ClibArea
  area() const
  {
    return mArea;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // ピン情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン数の取得
  SizeType
  pin_num() const
  {
    return mPinList.size();
  }

  /// @brief ピンの取得
  const CiPin*
  pin(
    SizeType pos ///< [in] ピン番号 ( 0 <= pos < pin_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < pin_num() );
    return mPinList[pos];
  }

  /// @brief 名前からピンの取得
  ///
  /// なければ nullptr を返す．
  const CiPin*
  find_pin(
    const ShString& name ///< [in] ピン名
  ) const;

  /// @brief ピンのリストの取得
  const vector<const CiPin*>&
  pin_list() const
  {
    return mPinList;
  }

  /// @brief 入力ピン数の取得
  SizeType
  input_num() const
  {
    return mInputNum;
  }

  /// @brief 入力ピンの取得
  const CiPin*
  input(
    SizeType pos ///< [in] 入力番号 ( 0 <= pos < input2_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < input2_num() );
    return mInputList[pos];
  }

  /// @brief 入力ピンのリストの取得
  const vector<const CiPin*>&
  input_list() const
  {
    return mInputList;
  }

  /// @brief 出力ピン数の取得
  SizeType
  output_num() const
  {
    return mOutputNum;
  }

  /// @brief 出力ピンの取得
  ///
  /// pos >= output_num() の場合には入出力ピンが返される．
  const CiPin*
  output(
    SizeType pos ///< [in] 出力番号 ( 0 <= id < output2_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < output2_num() );
    return mOutputList[pos];
  }

  /// @brief 出力ピンのリスト
  const vector<const CiPin*>&
  output_list() const
  {
    return mOutputList;
  }

  /// @brief 入出力ピン数の取得
  SizeType
  inout_num() const
  {
    return mInoutNum;
  }

  /// @brief 入出力ピンの取得
  const CiPin*
  inout(
    SizeType id ///< [in] 番号 ( 0 <= id < inout_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < inout_num() );
    return mInputList[id + input_num()];
  }

  /// @brief 入出力ピン番号のリストの先頭
  vector<const CiPin*>::const_iterator
  inout_begin() const
  {
    return mInputList.begin() + input_num();
  }

  /// @brief 入力ピン+入出力ピン数の取得
  ///
  /// input_num() + inout_num() に等しい．
  SizeType
  input2_num() const
  {
    return mInputList.size();
  }

  /// @brief 出力ピン+入出力ピン数の取得
  ///
  /// output_num() + inout_num() に等しい．
  SizeType
  output2_num() const
  {
    return mOutputList.size();
  }

  /// @brief 内部ピン数の取得
  SizeType
  internal_num() const
  {
    return mInternalList.size();
  }

  /// @brief 内部ピンの取得
  const CiPin*
  internal(
    SizeType pos ///< [in] 内部ピン番号 ( 0 <= pos < internal_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < mInternalList.size() );
    return mInternalList[pos];
  }

  /// @brief 内部ピンのリスト
  const vector<const CiPin*>&
  internal_list() const
  {
    return mInternalList;
  }

  /// @brief バス数の取得
  SizeType
  bus_num() const
  {
    return mBusList.size();
  }

  /// @brief バスの取得
  const CiBus*
  bus(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bus_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < bus_num() );
    return mBusList[pos];
  }

  /// @brief 名前からバスの取得
  const CiBus*
  find_bus(
    const ShString& name ///< [in] 名前
  ) const;

  /// @brief バスのリスト
  const vector<const CiBus*>&
  bus_list() const
  {
    return mBusList;
  }

  /// @brief バンドル数の取得
  SizeType
  bundle_num() const
  {
    return mBundleList.size();
  }

  /// @brief バンドルの取得
  const CiBundle*
  bundle(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bundle_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < bundle_num() );
    return mBundleList[pos];
  }

  /// @brief 名前からバスの取得
  const CiBundle*
  find_bundle(
    const ShString& name ///< [in] 名前
  ) const;

  /// @brief バンドルのリスト
  const vector<const CiBundle*>&
  bundle_list() const
  {
    return mBundleList;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // タイミング情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の数を返す．
  SizeType
  timing_num() const
  {
    return mTimingList.size();
  }

  /// @brief タイミング情報を返す．
  const CiTiming*
  timing(
    SizeType pos ///< [in] インデックス ( 0 <= pos < timing_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < timing_num() );
    return mTimingList[pos];
  }

  /// @brief タイミングのリストを返す．
  const vector<const CiTiming*>&
  timing_list() const
  {
    return mTimingList;
  }

  /// @brief 条件に合致するタイミング情報のインデックスのリストを返す．
  const vector<const CiTiming*>&
  timing_list(
    SizeType ipos,        ///< [in] 開始ピン番号 ( 0 <= ipos < input_num2() )
    SizeType opos,        ///< [in] 終了ピン番号 ( 0 <= opos < output_num2() )
    ClibTimingSense sense ///< [in] タイミング情報の摘要条件
  ) const
  {
    SizeType base = (opos * input2_num() + ipos) * 2;
    switch ( sense ) {
    case ClibTimingSense::positive_unate: base += 0; break;
    case ClibTimingSense::negative_unate: base += 1; break;
    default:
      ASSERT_NOT_REACHED;
    }
    return mTimingMap[base];
  }


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 機能情報の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  virtual
  ClibCellType
  type() const;

  /// @brief 組み合わせ論理タイプの時 true を返す．
  virtual
  bool
  is_logic() const;

  /// @brief FFタイプの時 true を返す．
  virtual
  bool
  is_ff() const;

  /// @brief ラッチタイプの時 true を返す．
  virtual
  bool
  is_latch() const;

  /// @brief FSMタイプの時 true を返す．
  virtual
  bool
  is_fsm() const;

  /// @brief 内部変数1の名前を返す．
  virtual
  string
  qvar1() const;

  /// @brief 内部変数1の名前を返す．
  virtual
  string
  qvar2() const;

  /// @brief 非同期 clear を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_clear() const;

  /// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
  ///
  /// クリア端子がない場合の返り値は不定
  virtual
  Expr
  clear_expr() const;

  /// @brief 非同期 preset を持つ時 true を返す．
  ///
  /// FF/ラッチセル以外の場合には返り値は不定
  bool
  has_preset() const;

  /// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
  ///
  /// プリセット端子がない場合の返り値は不定
  virtual
  Expr
  preset_expr() const;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var1() const;

  /// @brief clear と preset が同時にアクティブになった時の値1
  ///
  /// has_clear() == true && has_preset() == true の時のみ意味を持つ．
  /// FF/ラッチセル以外の場合には返り値は不定
  virtual
  ClibCPV
  clear_preset_var2() const;

  /// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock_expr() const;

  /// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  clock2_expr() const;

  /// @brief FFセルの場合に次状態関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  next_state_expr() const;

  /// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable_expr() const;

  /// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  enable2_expr() const;

  /// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
  ///
  /// それ以外の型の場合の返り値は不定
  virtual
  Expr
  data_in_expr() const;

  /// @brief シグネチャを返す．
  virtual
  CgSignature
  make_signature(
    const CiCellLibrary* library ///< [in] ライブラリ
  ) const;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピンを追加する．
  void
  add_input(
    CiInputPin* pin ///< [in] ピン
  );

  /// @brief 出力ピンを追加する．
  void
  add_output(
    CiOutputPin* pin ///< [in] ピン
  );

  /// @brief 入出力ピンを追加する．
  void
  add_inout(
    CiInoutPin* pin ///< [in] ピン
  );

  /// @brief 内部ピンを追加する．
  void
  add_internal(
    CiInternalPin* pin ///< [in] ピン
  );

  /// @brief バスを追加する．
  void
  add_bus(
    const CiBus* bus ///< [in] バス
  );

  /// @brief バンドルを追加する．
  void
  add_bundle(
    const CiBundle* bundle ///< [in] バンドル
  );

  /// @brief タイミング情報用のデータ構造を初期化する．
  void
  init_timing_map();

  /// @brief タイミング情報をセットする(単独のタイミング情報)．
  ///
  /// この関数を呼ぶ前に init_timing_map() を呼んでおくこと．
  void
  set_timing(
    SizeType ipin_id,                   ///< [in] 入力ピン番号
    SizeType opin_id,                   ///< [in] 出力ピン番号
    ClibTimingSense timing_sense,       ///< [in] タイミング条件
    const CiTiming* timing              ///< [in] 設定するタイミング
  )
  {
    set_timing(ipin_id, opin_id, timing_sense,
	       vector<const CiTiming*>{timing});
  }

  /// @brief タイミング情報をセットする(複数のタイミング情報)．
  ///
  /// この関数を呼ぶ前に init_timing_map() を呼んでおくこと．
  void
  set_timing(
    SizeType ipin_id,                          ///< [in] 入力ピン番号
    SizeType opin_id,                          ///< [in] 出力ピン番号
    ClibTimingSense timing_sense,              ///< [in] タイミング条件
    const vector<const CiTiming*>& timing_list ///< [in] 設定するタイミング番号のリスト
  );


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をシリアライズする．
  void
  serialize(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容を読み込む．
  static
  CiCell*
  restore(
    Deserializer& s,   ///< [in] デシリアライザ
    CiCellLibrary* lib ///< [in] 親のセルライブラリ
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // dump/restore の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通部分のダンプ
  void
  dump_common(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief restore() の下請け関数
  virtual
  void
  _restore(
    Deserializer& s ///< [in] デシリアライザ
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  SizeType mId;

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
  vector<const CiPin*> mPinList;

  // 入力ピン+入出力ピンのリスト
  // サイズ mInputNum + mInoutNum
  vector<const CiPin*> mInputList;

  // 出力ピン+入出力ピンのリスト
  // サイズ mOutputNum + mInoutNum
  vector<const CiPin*> mOutputList;

  // 内部ピンのリスト
  vector<const CiPin*> mInternalList;

  // バスのリスト
  vector<const CiBus*> mBusList;

  // バンドルのリスト
  vector<const CiBundle*> mBundleList;

  // 全体のタイミング情報の番号のリスト
  vector<const CiTiming*> mTimingList;

  // 条件ごとのタイミングのリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  vector<vector<const CiTiming*>> mTimingMap;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
