#ifndef ASTpin_H
#define ASTpin_H

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
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] name_list ピン名のリスト
  /// @param[in] pin_direction 方向
  /// @param[in] capacitance 容量
  /// @param[in] rise_capacitance 立ち上がり容量
  /// @param[in] fall_capacitance 立ち下がり容量
  /// @param[in] max_fanout 最大ファンアウト
  /// @param[in] min_fanout 最小ファンアウト
  /// @param[in] max_capacitance 最大容量
  /// @param[in] min_capacitance 最小容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  /// @param[in] function 関数
  /// @param[in] three_state スリーステート条件
  /// @param[in] internal_node 対応する内部ノード
  /// @param[in] pin_func_type 'pin_func_type'
  /// @param[in] timing_list タイミングのリスト
  /// @param[in] alloc メモリアロケータ
  AstPin(const FileRegion& loc,
	 const vector<const AstString*>& name_list,
	 const AstPinDirection* pin_direction,
	 const AstFloat* capacitance,
	 const AstFloat* rise_capacitance,
	 const AstFloat* fall_capacitance,
	 const AstFloat* max_fanout,
	 const AstFloat* min_fanout,
	 const AstFloat* max_capacitance,
	 const AstFloat* min_capacitance,
	 const AstFloat* max_transition,
	 const AstFloat* min_transition,
	 const AstExpr* function,
	 const AstExpr* three_state,
	 const AstNode* internal_node,
	 const AstNode* pin_func_type,
	 const vector<const AstTiming*>& timing_list,
	 Alloc& alloc);

  /// @brief デストラクタ
  virtual
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
  const AstPinDirection*
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
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン名のリストの要素数
  int mNameNum;

  // ピン名のリスト
  const AstString** mNameList;

  // "direction"
  const AstPinDirection* mPinDirection;

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
const AstPinDirection*
AstPin::direction() const
{
  return mPinDirection;
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

#endif // ASTpin_H
