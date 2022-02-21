#ifndef ASTPININFO_H
#define ASTPININFO_H

/// @file AstPinInfo.h
/// @brief AstPinInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstTimingInfo.h"
#include "ci/CiCell.h"
#include "ym/Expr.h"
#include "ym/ShString.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

class AstElemDict;

//////////////////////////////////////////////////////////////////////
/// @class AstPinInfo AstPinInfo.h "AstPinInfo.h"
/// @brief ピンのパース情報
//////////////////////////////////////////////////////////////////////
class AstPinInfo
{
public:

  /// @brief コンストラクタ
  AstPinInfo() = default;

  /// @brief デストラクタ
  ~AstPinInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* pin_val,   ///< [in] ピン情報のパース木
    ClibDelayModel delay_model ///< [in] ディレイモデル
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
    CiCell* cell,
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
  get_input_params(
    const AstElemDict& elem_dict
  );

  /// @brief 出力ピン用のパラメータを取り出す．
  ///
  /// 指定がない場合にはデフォルト値を入れている．
  /// エラーの場合には false を返す．
  /// 現時点ではエラーにならない．
  bool
  get_output_params(
    const AstElemDict& elem_dict,
    ClibDelayModel delay_model
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

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
  vector<AstTimingInfo> mTimingInfoList;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTPININFO_H
