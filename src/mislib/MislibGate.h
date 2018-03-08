#ifndef MISLIBGATE_H
#define MISLIBGATE_H

/// @file MislibGate.h
/// @brief MislibGate のヘッダファイル(その2)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibGate MislibGate.h "MislibGate.h"
/// @brief ゲート(セル)を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibGate :
  public MislibNode
{
  friend class MislibMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] name 名前を表すパース木
  /// @param[in] area 面積を表すパース木
  /// @param[in] opin_name 出力ピン名を表すパース木
  /// @param[in] opin_expr 出力の論理式を表すパース木
  /// @param[in] ipin_top 先頭の入力ピンを表すパース木
  MislibGate(const FileRegion& loc,
	     const MislibStr* name,
	     const MislibNum* area,
	     const MislibStr* opin_name,
	     const MislibExpr* opin_expr,
	     const MislibPin* ipin_top);

  /// @brief デストラクタ
  ~MislibGate();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ゲート名を表すオブジェクトを取り出す．
  const MislibStr*
  name() const;

  /// @brief 面積を表すオブジェクトを返す．
  const MislibNum*
  area() const;

  /// @brief 出力ピン名を表すオブジェクトを返す．
  const MislibStr*
  opin_name() const;

  /// @brief 出力の論理式を表すオブジェクトを返す．
  const MislibExpr*
  opin_expr() const;

  /// @brief 入力ピンのリストを返す．
  const MislibPin*
  ipin_top() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  void
  dump(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const MislibStr* mName;

  // 面積
  const MislibNum* mArea;

  // 出力ピン名
  const MislibStr* mOpinName;

  // 出力の論理式
  const MislibExpr* mOpinExpr;

  // 先頭の入力ピン
  const MislibPin* mIpinTop;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ゲート名を表すオブジェクトを取り出す．
inline
const MislibStr*
MislibGate::name() const
{
  return mName;
}

// @brief 面積を表すオブジェクトを返す．
inline
const MislibNum*
MislibGate::area() const
{
  return mArea;
}

// @brief 出力ピン名を表すオブジェクトを返す．
inline
const MislibStr*
MislibGate::opin_name() const
{
  return mOpinName;
}

// @brief 出力の論理式を表すオブジェクトを返す．
inline
const MislibExpr*
MislibGate::opin_expr() const
{
  return mOpinExpr;
}

// @brief 入力ピンのリストを返す．
inline
const MislibPin*
MislibGate::ipin_top() const
{
  return mIpinTop;
}

END_NAMESPACE_YM_MISLIB

#endif // MISLIBGATE_H
