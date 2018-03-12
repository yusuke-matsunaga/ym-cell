#ifndef DOTLIBCELL_H
#define DOTLIBCELL_H

/// @file DotlibCell.h
/// @brief DotlibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibCell DotlibCell.h "DotlibCell.h"
/// @brief DotlibNode の木から取り出したセルの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibCell :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] bus_naming_style 'bus_naming_style' の値
  /// @param[in] pin_top ピンの先頭
  /// @param[in] bus_top バスの先頭
  /// @param[in] bundle_top バンドルの先頭
  /// @param[in] ff FFグループ
  /// @param[in] latch ラッチグループ
  /// @param[in] statetable StateTable グループ
  DotlibCell(const FileRegion& loc,
	     const DotlibString* name,
	     const DotlibFloat* area,
	     const DotlibString* bus_naming_style,
	     const DotlibPin* pin_top,
	     const DotlibBus* bus_top,
	     const DotlibBundle* bundle_top,
	     const DotlibFF* ff,
	     const DotlibLatch* latch,
	     const DotlibStateTable* statetable);

  /// @brief デストラクタ
  ~DotlibCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const DotlibString*
  name() const;

  /// @brief 面積を返す．
  const DotlibFloat*
  area() const;

  /// @brief bus_naming_style を返す．
  const DotlibString*
  bus_nameing_style() const;

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

  // セル名
  const DotlibString* mName;

  // 面積
  const DotlibFloat* mArea;

  // "bus_naming_style"
  const DotlibString* mBusNamingStyle;

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
const DotlibString*
DotlibCell::name() const
{
  return mName;
}

// @brief 面積を返す．
inline
const DotlibFloat*
DotlibCell::area() const
{
  return mArea;
}

// @brief bus_naming_style を返す．
inline
const DotlibString*
DotlibCell::bus_nameing_style() const
{
  return mBusNamingStyle;
}

// @brief ピングループのリストの先頭を返す．
inline
const DotlibPin*
DotlibCell::pin_top() const
{
  return mPinTop;
}

// @brief バスグループのリストの先頭を返す．
inline
const DotlibBus*
DotlibCell::bus_top() const
{
  return mBusTop;
}

// @brief バンドルグループのリストの先頭を返す．
inline
const DotlibBundle*
DotlibCell::bundle_top() const
{
  return mBundleTop;
}

// @brief ff グループを返す．
inline
const DotlibFF*
DotlibCell::ff() const
{
  return mFF;
}

// @brief latch グループを返す．
inline
const DotlibLatch*
DotlibCell::latch() const
{
  return mLatch;
}

// @brief statetable グループを返す．
inline
const DotlibStateTable*
DotlibCell::statetable() const
{
  return mStateTable;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBCELL_H
