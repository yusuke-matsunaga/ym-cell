#ifndef MISLIBPIN_H
#define MISLIBPIN_H

/// @file MislibPin.h
/// @brief MislibPin の派生クラスのヘッダファイル(その2)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibPin MislibPin.h "MislibPin.h"
/// @brief ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class MislibPin :
  public MislibNode
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] name ピン名
  /// @param[in] phase 極性
  /// @param[in] input_load 入力負荷
  /// @param[in] max_load 最大駆動負荷
  /// @param[in] rise_block_delay 立ち上がり固定遅延
  /// @param[in] rise_fanout_delay 立ち上がり負荷依存遅延
  /// @param[in] fall_block_delay 立ち下がり固定遅延
  /// @param[in] fall_fanout_delay 立ち下がり負荷依存遅延
  MislibPin(const FileRegion& loc,
	    const MislibStr* name,
	    const MislibPhase* phase,
	    const MislibNum* input_load,
	    const MislibNum* max_load,
	    const MislibNum* rise_block_delay,
	    const MislibNum* rise_fanout_delay,
	    const MislibNum* fall_block_delay,
	    const MislibNum* fall_fanout_delay);

  /// @brief デストラクタ
  ~MislibPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン名を表すオブジェクトを取り出す．
  const MislibStr*
  name() const;

  /// @brief 極性情報を表すオブジェクトを取り出す．
  const MislibPhase*
  phase() const;

  /// @brief 入力負荷を表すオブジェクトを取り出す．
  const MislibNum*
  input_load() const;

  /// @brief 最大駆動負荷を表すオブジェクトを取り出す．
  const MislibNum*
  max_load() const;

  /// @brief 立ち上がり固定遅延を表すオブジェクトを取り出す．
  const MislibNum*
  rise_block_delay() const;

  /// @brief 立ち上がり負荷依存遅延を表すオブジェクトを取り出す．
  const MislibNum*
  rise_fanout_delay() const;

  /// @brief 立ち下がり固定遅延を表すオブジェクトを取り出す．
  const MislibNum*
  fall_block_delay() const;

  /// @brief 立ち下がり負荷依存遅延を表すオブジェクトを取り出す．
  const MislibNum*
  fall_fanout_delay() const;

  /// @brief 次のピンを設定する．
  void
  set_next(MislibPin* pin);

  /// @brief 次のピンを取り出す．
  const MislibPin*
  next() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  void
  dump(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピン名
  const MislibStr* mName;

  // 極性情報
  const MislibPhase* mPhase;

  // 入力負荷
  const MislibNum* mInputLoad;

  // 最大駆動負荷
  const MislibNum* mMaxLoad;

  // 立ち上がり固有遅延
  const MislibNum* mRiseBlockDelay;

  // 立ち上がり負荷依存遅延係数
  const MislibNum* mRiseFanoutDelay;

  // 立ち下がり固有遅延
  const MislibNum* mFallBlockDelay;

  // 立ち下がり負荷依存遅延係数
  const MislibNum* mFallFanoutDelay;

  // 次のピン
  MislibPin* mNext;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// ピン名を表すオブジェクトを取り出す．
inline
const MislibStr*
MislibPin::name() const
{
  return mName;
}

// 極性情報を表すオブジェクトを取り出す．
inline
const MislibPhase*
MislibPin::phase() const
{
  return mPhase;
}

// 入力負荷を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::input_load() const
{
  return mInputLoad;
}

// 最大駆動負荷を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::max_load() const
{
  return mMaxLoad;
}

// 立ち上がり固定遅延を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::rise_block_delay() const
{
  return mRiseBlockDelay;
}

// 立ち上がり負荷依存遅延を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::rise_fanout_delay() const
{
  return mRiseFanoutDelay;
}

// 立ち下がり固定遅延を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::fall_block_delay() const
{
  return mFallBlockDelay;
}

// 立ち下がり負荷依存遅延を表すオブジェクトを取り出す．
inline
const MislibNum*
MislibPin::fall_fanout_delay() const
{
  return mFallFanoutDelay;
}

// 次の要素を設定する．
inline
void
MislibPin::set_next(MislibPin* pin)
{
  mNext = pin;
}

// 次の要素を取り出す．
inline
const MislibPin*
MislibPin::next() const
{
  return mNext;
}

END_NAMESPACE_YM_MISLIB

#endif // MISLIBPIN_H
