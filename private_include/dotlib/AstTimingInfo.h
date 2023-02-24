#ifndef ASTTIMINGINFO_H
#define ASTTIMINGINFO_H

/// @file AstTimingInfo.h
/// @brief AstTimingInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstTableInfo.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

class AstElemDict;

//////////////////////////////////////////////////////////////////////
/// @class AstTimingInfo AstTimingInfo.h "AstTimingInfo.h"
/// @brief タイミングのパース情報
//////////////////////////////////////////////////////////////////////
class AstTimingInfo
{
public:

  /// @brief コンストラクタ
  AstTimingInfo() = default;

  /// @brief デストラクタ
  ~AstTimingInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* timing_val, ///< [in] タイミング情報のパース木
    ClibDelayModel delay_model  ///< [in] ディレイモデル
  );

  /// @brief タイミング情報を作る．
  bool
  add_timing(
    CiCellLibrary* library,
    CiCell* cell,
    const Expr& function_expr,
    SizeType ni,
    const vector<SizeType>& opin_list,
    const unordered_map<ShString, SizeType>& ipin_map
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の共通なパラメータを得る．
  bool
  get_timing_common_params(
    const AstElemDict& elem_dict
  );

  /// @brief generic タイプのタイミング情報のパラメータを得る．
  bool
  get_timing_generic_params(
    const AstElemDict& elem_dict
  );

  /// @brief table-lookup タイプのタイミング情報のパラメータを得る．
  int
  get_timing_table_lookup_params(
    const AstElemDict& elem_dict
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前(オプショナル)
  ShString mName;

  // 遅延モデル
  ClibDelayModel mDelayModel;

  // 各モデルに共通のパラメータ
  ClibTimingType mTimingType;
  const AstExpr* mWhen;
  ClibTimingSense mTimingSense;
  vector<ShString> mRelatedPin;

  // generic cmos モデルのパラメータ
  ClibTime mIntrinsicRise;
  ClibTime mIntrinsicFall;
  ClibTime mSlopeRise;
  ClibTime mSlopeFall;
  ClibResistance mRiseResistance;
  ClibResistance mFallResistance;

  // table lookup モデルのパラメータ
  int mLutType;
  AstTableInfo mCellRise;
  AstTableInfo mCellFall;
  AstTableInfo mRiseTransition;
  AstTableInfo mFallTransition;
  AstTableInfo mRisePropagation;
  AstTableInfo mFallPropagation;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGINFO_H
