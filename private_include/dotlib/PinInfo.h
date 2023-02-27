#ifndef PININFO_H
#define PININFO_H

/// @file PinInfo.h
/// @brief PinInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/TimingInfo.h"
#include "dotlib/ElemDict.h"
#include "ci/CiCell.h"
#include "ym/Expr.h"
#include "ym/ShString.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

class LibraryInfo;
class AstElemDict;

//////////////////////////////////////////////////////////////////////
/// @class PinInfo PinInfo.h "PinInfo.h"
/// @brief ピンのパース情報
//////////////////////////////////////////////////////////////////////
class PinInfo
{
public:

  /// @brief コンストラクタ
  PinInfo(
    LibraryInfo& library_info ///< [in] ライブラリのパース情報
  ) : mLibraryInfo{library_info}
  {
  }

  /// @brief デストラクタ
  ~PinInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* pin_val ///< [in] ピン情報のパース木
  );

  /// @brief 向きを得る．
  ClibDirection
  direction() const
  {
    return mDirection;
  }

  /// @brief 名前のリストを得る．
  const vector<ShString>&
  name_list() const
  {
    return mNameList;
  }

  /// @brief ピンを生成する．
  bool
  add_pin(
    SizeType cell_id,                                ///< [in] セル番号
    const unordered_map<ShString, SizeType>& pin_map ///< [in] 入力ピン番号の辞書
  );

  /// @brief タイミングを生成する．
  bool
  add_timing(
    SizeType cell_id,                                ///< [in] セル番号
    const unordered_map<ShString, SizeType>& pin_map ///< [in] 入力ピン番号の辞書
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン用のパラメータを取り出す．
  ///
  /// エラーの場合には false を返す．
  bool
  get_input_params();

  /// @brief 出力ピン用のパラメータを取り出す．
  ///
  /// 指定がない場合にはデフォルト値を入れている．
  /// エラーの場合には false を返す．
  /// 現時点ではエラーにならない．
  bool
  get_output_params();

  /// @brief ライブラリを取り出す．
  CiCellLibrary*
  library() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリのパース情報
  LibraryInfo& mLibraryInfo;

  // 要素の辞書
  ElemDict mElemDict;

  // 名前のリスト
  vector<ShString> mNameList;

  // direction
  ClibDirection mDirection;

  // 入力ピン用のパラメータ
  ClibCapacitance mCapacitance;
  ClibCapacitance mRiseCapacitance;
  ClibCapacitance mFallCapacitance;

  // 出力ピン用のパラメータ
  ClibCapacitance mMaxFanout;
  ClibCapacitance mMinFanout;
  ClibCapacitance mMaxCapacitance;
  ClibCapacitance mMinCapacitance;
  ClibTime mMaxTransition;
  ClibTime mMinTransition;
  const AstExpr* mFunction{nullptr};
  const AstExpr* mTristate{nullptr};
  Expr mFunctionExpr;
  vector<SizeType> mOpinList;

  // タイミング情報
  vector<TimingInfo> mTimingInfoList;

};

END_NAMESPACE_YM_DOTLIB

#endif // PININFO_H
