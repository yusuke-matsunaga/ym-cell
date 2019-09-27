#ifndef ASTPIN_H
#define ASTPIN_H

/// @file AstPin.h
/// @brief AstPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstPin AstPin.h "AstPin.h"
/// @brief AstNode の木から取り出したピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstPin :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  AstPin(const FileRegion& attr_loc,
	 const StrListHandler& header,
	 const PinHandler& group);

  /// @brief デストラクタ
  ~AstPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前のリストの要素数を返す．
  int
  name_num() const;

  /// @brief 名前を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < name_num() )
  const AstString*
  name(int pos) const;

  /// @brief "direction" を返す．
  const AstDirection*
  direction() const;

  /// @brief "capacitance" を返す．
  const AstFloat*
  capacitance() const;

  /// @brief "rise_capacitance" を返す．
  const AstFloat*
  rise_capacitance() const;

  /// @brief "fall_capacitance" を返す．
  const AstFloat*
  fall_capacitance() const;

  /// @brief "max_fanout" を返す．
  const AstFloat*
  max_fanout() const;

  /// @brief "min_fanout" を返す．
  const AstFloat*
  min_fanout() const;

  /// @brief "max_capacitance" を返す．
  const AstFloat*
  max_capacitance() const;

  /// @brief "min_capacitance" を返す．
  const AstFloat*
  min_capacitance() const;

  /// @brief "max_transition" を返す．
  const AstFloat*
  max_transition() const;

  /// @brief "min_transition" を返す．
  const AstFloat*
  min_transition() const;

  /// @brief "function" を返す．
  const AstExpr*
  function() const;

  /// @brief "three_state" を返す．
  const AstExpr*
  three_state() const;

  /// @brief "internal_node" を返す．
  const AstNode*
  internal_node() const;

  /// @brief "pin_func_type" を返す．
  const AstNode*
  pin_func_type() const;

  /// @brief 'timing' グループのリストの要素数を返す．
  int
  timing_num() const;

  /// @brief "timing" グループのリストの要素を得る．
  /// @param[in] pos 位置番号 ( 0 <= pos < timing_num() )
  const AstTiming*
  timing_elem(int pos) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン名のリストの要素数
  int mNameNum;

  // ピン名のリスト
  const AstString** mNameList;

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
  const AstNode* mInternalNode;

  // "pin_func_type"
  const AstNode* mPinFuncType;

  // 'timing' リストの要素数
  int mTimingNum;

  // "timing"リスト
  const AstTiming** mTimingList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前のリストの要素数を返す．
inline
int
AstPin::name_num() const
{
  return mNameNum;
}

// @brief 名前を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
inline
const AstString*
AstPin::name(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < name_num() );

  return mNameList[pos];
}

// @brief "direction" を返す．
inline
const AstDirection*
AstPin::direction() const
{
  return mDirection;
}

// @brief "capacitance" を返す．
inline
const AstFloat*
AstPin::capacitance() const
{
  return mCapacitance;
}

// @brief "rise_capacitance" を返す．
inline
const AstFloat*
AstPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief "fall_capacitance" を返す．
inline
const AstFloat*
AstPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief "max_fanout" を返す．
inline
const AstFloat*
AstPin::max_fanout() const
{
  return mMaxFanout;
}

// @brief "min_fanout" を返す．
inline
const AstFloat*
AstPin::min_fanout() const
{
  return mMinFanout;
}

// @brief "max_capacitance" を返す．
inline
const AstFloat*
AstPin::max_capacitance() const
{
  return mMaxCapacitance;
}

// @brief "min_capacitance" を返す．
inline
const AstFloat*
AstPin::min_capacitance() const
{
  return mMinCapacitance;
}

// @brief "max_transition" を返す．
inline
const AstFloat*
AstPin::max_transition() const
{
  return mMaxTransition;
}

// @brief "min_transition" を返す．
inline
const AstFloat*
AstPin::min_transition() const
{
  return mMinTransition;
}

// @brief "function" を返す．
inline
const AstExpr*
AstPin::function() const
{
  return mFunction;
}

// @brief "three_state" を返す．
inline
const AstExpr*
AstPin::three_state() const
{
  return mThreeState;
}

// @brief "internal_node" を返す．
inline
const AstNode*
AstPin::internal_node() const
{
  return mInternalNode;
}

// @brief "pin_func_type" を返す．
inline
const AstNode*
AstPin::pin_func_type() const
{
  return mPinFuncType;
}

// @brief 'timing' グループのリストの要素数を返す．
inline
int
AstPin::timing_num() const
{
  return mTimingNum;
}

// @brief "timing" グループのリストの要素を得る．
// @param[in] pos 位置番号 ( 0 <= pos < timing_num() )
inline
const AstTiming*
AstPin::timing_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < timing_num() );

  return mTimingList[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTPIN_H
