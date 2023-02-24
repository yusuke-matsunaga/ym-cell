#ifndef CICELL_H
#define CICELL_H

/// @file CiCell.h
/// @brief CiCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibArea.h"
#include "ym/logic.h"
#include "ym/ShString.h"
#include "ci/CiPin.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiInputPin;
class CiOutputPin;
class CiInoutPin;
class CgSignature;

//////////////////////////////////////////////////////////////////////
/// @class CiCell CiCell.h "CiCell.h"
/// @brief ClibCell の実装クラス
///
/// このクラスはデフォルトの仮想関数を実装している．
//////////////////////////////////////////////////////////////////////
class CiCell
{
  friend class CiCellLibrary;

public:

  /// @brief コンストラクタ
  CiCell(
    const ShString& name, ///< [in] 名前
    ClibArea area         ///< [in] 面積
  ) : mName{name},
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

  /// @brief ID番号の取得
  SizeType
  id() const { return mId; }

  /// @brief 名前の取得
  string
  name() const  { return mName; }

  /// @brief 面積の取得
  ClibArea
  area() const { return mArea; }


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

  /// @brief ピン番号の取得
  /// @return ピン情報を返す．
  SizeType
  pin(
    SizeType pos ///< [in] ピン番号 ( 0 <= pos < pin_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < pin_num() );
    return mPinList[pos];
  }

  /// @brief ピン番号のリストの取得
  const vector<SizeType>&
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
  SizeType
  input(
    SizeType pos ///< [in] 入力番号 ( 0 <= pos < input2_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < input2_num() );
    return mInputList[pos];
  }

  /// @brief 入力ピン番号のリストの取得
  const vector<SizeType>&
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
  SizeType
  output(
    SizeType pos ///< [in] 出力番号 ( 0 <= id < output2_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < output2_num() );
    return mOutputList[pos];
  }

  /// @brief 出力ピン番号のリスト
  const vector<SizeType>&
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
  SizeType
  inout(
    SizeType id ///< [in] 番号 ( 0 <= id < inout_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < inout_num() );
    return mInputList[id + input_num()];
  }

  /// @brief 入出力ピン番号のリストの先頭
  vector<SizeType>::const_iterator
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
  SizeType
  internal(
    SizeType pos ///< [in] 内部ピン番号 ( 0 <= pos < internal_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < mInternalList.size() );
    return mInternalList[pos];
  }

  /// @brief 内部ピン番号のリスト
  const vector<SizeType>&
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
  SizeType
  bus(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bus_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < bus_num() );
    return mBusList[pos];
  }

  /// @brief バス番号のリスト
  const vector<SizeType>&
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
  SizeType
  bundle(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < bundle_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < bundle_num() );
    return mBundleList[pos];
  }

  /// @brief バンドル番号のリスト
  const vector<SizeType>&
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
  SizeType
  timing(
    SizeType pos ///< [in] インデックス ( 0 <= pos < timing_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < timing_num() );
    return mTimingList[pos];
  }

  /// @brief タイミングIDのリストを返す．
  const vector<SizeType>&
  timing_list() const
  {
    return mTimingList;
  }

  /// @brief 条件に合致するタイミング情報のインデックスのリストを返す．
  const vector<SizeType>&
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

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const;


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
  void
  add_input(
    CiInputPin* pin, ///< [in] ピン
    SizeType id      ///< [in] ピン番号
  )
  {
    SizeType pid = mPinList.size();
    pin->set_pin_id(pid);
    mPinList.push_back(id);
    SizeType iid = mInputList.size();
    pin->set_input_id(iid);
    mInputList.push_back(id);
    ++ mInputNum;
  }

  /// @brief 出力ピンを追加する．
  void
  add_output(
    CiOutputPin* pin, ///< [in] ピン
    SizeType id       ///< [in] ピン番号
  )
  {
    SizeType pid = mPinList.size();
    pin->set_pin_id(pid);
    mPinList.push_back(id);
    SizeType oid = mOutputList.size();
    pin->set_output_id(oid);
    mOutputList.push_back(id);
    ++ mOutputNum;
  }

  /// @brief 入出力ピンを追加する．
  void
  add_inout(
    CiInoutPin* pin, ///< [in] ピン
    SizeType id      ///< [in] ピン番号
  )
  {
    SizeType pid = mPinList.size();
    pin->set_pin_id(pid);
    mPinList.push_back(id);
    SizeType iid = mInputList.size();
    pin->set_input_id(iid);
    mInputList.push_back(id);
    SizeType oid = mOutputList.size();
    pin->set_output_id(oid);
    mOutputList.push_back(id);
    ++ mInoutNum;
  }

  /// @brief 内部ピンを追加する．
  void
  add_internal(
    CiInternalPin* pin, ///< [in] ピン
    SizeType id         ///< [in] ピン番号
  )
  {
    auto iid = mInternalList.size();
    pin->set_internal_id(iid);
    mInternalList.push_back(id);
  }

  /// @brief バスを追加する．
  void
  add_bus(
    SizeType id ///< [in] バス番号
  )
  {
    mBusList.push_back(id);
  }

  /// @brief バンドルを追加する．
  void
  add_bundle(
    SizeType id ///< [in] バンドル番号
  )
  {
    mBundleList.push_back(id);
  }

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
  make_signature(
    const CiCellLibrary* library ///< [in] ライブラリ
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

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

  // ピン番号のリスト
  vector<SizeType> mPinList;

  // 入力ピン+入出力ピンの番号のリスト
  // サイズ mInputNum + mInoutNum
  vector<SizeType> mInputList;

  // 出力ピン+入出力ピンの番号のリスト
  // サイズ mOutputNum + mInoutNum
  vector<SizeType> mOutputList;

  // 内部ピン番号のリスト
  vector<SizeType> mInternalList;

  // バス番号のリスト
  vector<SizeType> mBusList;

  // バンドル番号のリスト
  vector<SizeType> mBundleList;

  // 全体のタイミング情報の番号のリスト
  vector<SizeType> mTimingList;

  // 条件ごとのタイミング番号のリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  vector<vector<SizeType>> mTimingMap;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
