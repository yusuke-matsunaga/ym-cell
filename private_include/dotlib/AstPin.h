#ifndef ASTPIN_H
#define ASTPIN_H

/// @file AstPin.h
/// @brief AstPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNameListNode.h"
#include "AstArray.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstPin AstPin.h "AstPin.h"
/// @brief AstNode の木から取り出したピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstPin :
  public AstNameListNode
{
public:

  /// @brief コンストラクタ
  AstPin(const FileRegion& attr_loc,   ///< [in] 属性のファイル上の位置
	 const StrListHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	 const PinHandler& group);     ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief "direction" を返す．
  const AstDirection*
  direction() const
  {
    return mDirection;
  }

  /// @brief "capacitance" を返す．
  const AstFloat*
  capacitance() const
  {
    return mCapacitance;
  }

  /// @brief "rise_capacitance" を返す．
  const AstFloat*
  rise_capacitance() const
  {
    return mRiseCapacitance;
  }

  /// @brief "fall_capacitance" を返す．
  const AstFloat*
  fall_capacitance() const
  {
    return mFallCapacitance;
  }

  /// @brief "max_fanout" を返す．
  const AstFloat*
  max_fanout() const
  {
    return mMaxFanout;
  }

  /// @brief "min_fanout" を返す．
  const AstFloat*
  min_fanout() const
  {
    return mMinFanout;
  }

  /// @brief "max_capacitance" を返す．
  const AstFloat*
  max_capacitance() const
  {
    return mMaxCapacitance;
  }

  /// @brief "min_capacitance" を返す．
  const AstFloat*
  min_capacitance() const
  {
    return mMinCapacitance;
  }

  /// @brief "max_transition" を返す．
  const AstFloat*
  max_transition() const
  {
    return mMaxTransition;
  }

  /// @brief "min_transition" を返す．
  const AstFloat*
  min_transition() const
  {
    return mMinTransition;
  }

  /// @brief "function" を返す．
  const AstExpr*
  function() const
  {
    return mFunction;
  }

  /// @brief "three_state" を返す．
  const AstExpr*
  three_state() const
  {
    return mThreeState;
  }

  /// @brief "internal_node" を返す．
  const AstString*
  internal_node() const
  {
    return mInternalNode;
  }

  /// @brief "pin_func_type" を返す．
  const AstString*
  pin_func_type() const
  {
    return mPinFuncType;
  }

  /// @brief 'timing' グループのリストを返す．
  AstArray<const AstTiming*>
  timing_list() const
  {
    return mTimingList;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // "direction"
  const AstDirection* mDirection;

  // "capacitance"
  const AstFloat* mCapacitance;

  // "rise_capacitance"
  const AstFloat* mRiseCapacitance;

  // "fall_capacitance"
  const AstFloat* mFallCapacitance;

  // "max_fanout"
  const AstFloat* mMaxFanout;

  // "min_fanout"
  const AstFloat* mMinFanout;

  // "max_capacitance"
  const AstFloat* mMaxCapacitance;

  // "min_capacitance"
  const AstFloat* mMinCapacitance;

  // "max_transition"
  const AstFloat* mMaxTransition;

  // "min_transition"
  const AstFloat* mMinTransition;

  // "function"
  const AstExpr* mFunction;

  // "three_state"
  const AstExpr* mThreeState;

  // "internal_node"
  const AstString* mInternalNode;

  // "pin_func_type"
  const AstString* mPinFuncType;

  // "timing"リスト
  AstArray<const AstTiming*> mTimingList;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTPIN_H
