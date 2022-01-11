#ifndef CICELL_H
#define CICELL_H

/// @file CiClibl.h
/// @brief CiClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCell.h"
#include "ym/Expr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCellLibrary;
class CiCellGroup;
class CiPin;
class CiInputPin;
class CiOutputPin;
class CiInoutPin;
class CiInternalPin;
class CiBus;
class CiBundle;
class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @class CiCell CiCell.h "CiCell.h"
/// @brief ClibCell の実装クラス
//////////////////////////////////////////////////////////////////////
class CiCell :
  public ClibCell
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  CiCell(
    CiCellLibrary* library,                      ///< [in] 親のセルライブラリ
    CiCellGroup* group,                          ///< [in] 親のセルグループ
    const ShString& name,                        ///< [in] 名前
    ClibArea area,                               ///< [in] 面積
    const vector<CiInputPin*>& input_list,       ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list,     ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,       ///< [in] 入出力ピンのリスト
    const vector<CiInternalPin*>& internal_list, ///< [in] 内部ピンのリスト
    const vector<CiBus*>& bus_list,              ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,        ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list         ///< [in] タイミング情報のリスト
  );

  /// @brief エラーオブジェクト用のコンストラクタ
  CiCell();


public:

  /// @brief デストラクタ
  ~CiCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 基本情報の取得
  //////////////////////////////////////////////////////////////////////

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
    const char* name ///< [in] ピン名
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
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報をセットする．
  void
  set_timing(
    SizeType ipin_id,                   ///< [in] 入力ピン番号
    SizeType opin_id,                   ///< [in] 出力ピン番号
    ClibTimingSense timing_sense,       ///< [in] タイミング条件
    const vector<SizeType>& timing_list ///< [in] タイミング番号のリスト
  );


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief セルグループを返す．
  const ClibCellGroup&
  cgroup() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セルライブラリ
  CiCellLibrary* mLibrary{nullptr};

  // このセルが属するセルグループ
  CiCellGroup* mGroup{nullptr};

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
  SizeType mInOutNum{0};

  // ピンのリスト
  vector<unique_ptr<CiPin>> mPinList;

  // 入力ピン+入出力ピンのリスト
  // サイズ mInputNum + mInOutNum
  vector<const ClibPin*> mInputList;

  // 出力ピン+入出力ピンのリスト
  // サイズ mOutputNum + mInOutNum
  vector<const ClibPin*> mOutputList;

  // 内部ピンのリスト
  vector<const ClibPin*> mInternalList;

  // バスピンのリスト
  vector<unique_ptr<CiBus>> mBusList;

  // バンドルピンのリスト
  vector<unique_ptr<CiBundle>> mBundleList;

  // 全体のタイミング情報のリスト
  vector<unique_ptr<CiTiming>> mTimingList;

  // 条件ごとのタイミングIDのリストの配列
  // サイズは(入力数＋入出力数) x (出力数+入出力数)  x 2
  vector<vector<SizeType>> mTimingMap;

};

END_NAMESPACE_YM_CLIB

#endif // CICELL_H
