#ifndef TIMINGINFO_H
#define TIMINGINFO_H

/// @file TimingInfo.h
/// @brief TimingInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/ElemInfo.h"
#include "dotlib/TableInfo.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingInfo TimingInfo.h "TimingInfo.h"
/// @brief タイミングのパース情報
//////////////////////////////////////////////////////////////////////
class TimingInfo :
  public ElemInfo
{
public:

  /// @brief コンストラクタ
  TimingInfo(
    LibraryInfo& library_info ///< [in] ライブラリのパース情報
  ) : ElemInfo{library_info},
      mCellRise{library_info},
      mCellFall{library_info},
      mRiseTransition{library_info},
      mFallTransition{library_info},
      mRisePropagation{library_info},
      mFallPropagation{library_info}
  {
  }

  /// @brief デストラクタ
  ~TimingInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* timing_val ///< [in] タイミング情報のパース木
  );

  /// @brief タイミング情報を作る．
  bool
  add_timing(
    CiCell* cell,
    const Expr& function_expr,
    const vector<SizeType>& opin_list,
    const unordered_map<ShString, SizeType>& ipin_map
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief タイミング情報の共通なパラメータを得る．
  bool
  set_timing_common_params();

  /// @brief generic タイプのタイミング情報のパラメータを得る．
  bool
  set_timing_generic_params();

  /// @brief table-lookup タイプのタイミング情報のパラメータを得る．
  int
  set_timing_table_lookup_params();


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
  const AstExpr* mWhen{nullptr};
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
  TableInfo mCellRise;
  TableInfo mCellFall;
  TableInfo mRiseTransition;
  TableInfo mFallTransition;
  TableInfo mRisePropagation;
  TableInfo mFallPropagation;

};

END_NAMESPACE_YM_DOTLIB

#endif // TIMINGINFO_H
