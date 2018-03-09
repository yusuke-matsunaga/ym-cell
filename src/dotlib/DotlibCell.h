#ifndef DOTLIBCELL_H
#define DOTLIBCELL_H

/// @file DotlibCell.h
/// @brief DotlibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibPin.h"
#include "DotlibFF.h"
#include "DotlibLatch.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibCell DotlibCell.h "DotlibCell.h"
/// @brief DotlibNode の木から取り出したセルの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibCell
{
public:

  /// @brief コンストラクタ
  DotlibCell();

  /// @brief デストラクタ
  ~DotlibCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set_data(const DotlibNode* node);

  /// @brief 名前を返す．
  ShString
  name() const;

  /// @brief 面積を返す．
  double
  area() const;

  /// @brief ピングループのリストの先頭を返す．
  const DotlibPin*
  pin_top() const;

  /// @brief バスグループのリストの先頭を返す．
  const DotlibBus*
  bus_top() const;

  /// @brief バンドルグループのリストの先頭を返す．
  const DotlibBundle*
  bundle_top() const;

  /// @brief ff グループを返す．
  const DotlibFF*
  ff() const;

  /// @brief latch グループを返す．
  const DotlibLatch*
  latch() const;

  /// @brief statetable グループを返す．
  const DotlibStateTable*
  statetable() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // セル名
  ShString mName;

  // 面積
  double mArea;

  // "bus_naming_style"
  const DotlibNode* mBusNamingStyle;

  // ピングループのリストの先頭
  const DotlibPin* mPinTop;

  // バスグループのリストの先頭
  const DotlibBus* mBusTop;

  // バンドルグループのリストの先頭
  const DotlibBundle* mBundleTop;

  // ff グループ
  const DotlibFF* mFF;

  // latch グループ
  const DotlibLatch* mLatch;

  // statetable グループ
  const DotlibStateTable* mStateTable;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
ShString
DotlibCell::name() const
{
  return mName;
}

// @brief 面積を返す．
inline
double
DotlibCell::area() const
{
  return mArea;
}

// @brief ピングループのリストの先頭を返す．
inline
const DotlibPin*
DotlibCell::pin_top() const
{
  return mPinTop;
}

// @brief バスグループのリストの先頭を返す．
const DotlibBus*
DotlibCell::bus_top() const
{
  return mBusTop;
}

// @brief バンドルグループのリストの先頭を返す．
const DotlibBundle*
DotlibCell::bundle_top() const
{
  return mBundleTop;
}

// @brief ff グループを返す．
const DotlibFF*
DotlibCell::ff() const
{
  return mFF;
}

// @brief latch グループを返す．
const DotlibLatch*
DotlibCell::latch() const
{
  return mLatch;
}

// @brief statetable グループを返す．
const DotlibStateTable*
DotlibCell::statetable() const
{
  return mStateTable;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBCELL_H
