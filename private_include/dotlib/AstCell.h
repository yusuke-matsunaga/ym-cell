#ifndef ASTCELL_H
#define ASTCELL_H

/// @file AstCell.h
/// @brief AstCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstCell AstCell.h "AstCell.h"
/// @brief セルの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstCell :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] bus_naming_style 'bus_naming_style' の値
  /// @param[in] pin_top ピンのリスト
  /// @param[in] bus_top バスのリスト
  /// @param[in] bundle_top バンドルのリスト
  /// @param[in] ff ffグループ
  /// @param[in] latch ラッチグループ
  /// @param[in] statetable StateTable グループ
  /// @param[in] alloc メモリアロケータ
  AstCell(const FileRegion& loc,
	  const AstString* name,
	  const AstFloat* area,
	  const AstString* bus_naming_style,
	  const vector<const AstPin*>& pin_list,
	  const vector<const AstBus*>& bus_list,
	  const vector<const AstBundle*>& bundle_list,
	  const AstFF* ff,
	  const AstLatch* latch,
	  const AstStateTable* statetable,
	  Alloc& alloc);

  /// @brief デストラクタ
  ~AstCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief 面積を返す．
  const AstFloat*
  area() const;

  /// @brief bus_naming_style を返す．
  const AstString*
  bus_nameing_style() const;

  /// @brief ピングループのリストの要素数を返す．
  int
  pin_num() const;

  /// @brief ピングループのリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
  const AstPin*
  pin_elem(int pos) const;

  /// @brief バスグループのリストの要素数を返す．
  int
  bus_num() const;

  /// @brief バスグループのリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
  const AstBus*
  bus_elem(int pos) const;

  /// @brief バンドルグループのリストの要素数を返す．
  int
  bundle_num() const;

  /// @brief バンドルグループのリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
  const AstBundle*
  bundle_elem(int pos) const;

  /// @brief ff グループを返す．
  const AstFF*
  ff() const;

  /// @brief latch グループを返す．
  const AstLatch*
  latch() const;

  /// @brief statetable グループを返す．
  const AstStateTable*
  state_table() const;

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

  // セル名
  const AstString* mName;

  // 面積
  const AstFloat* mArea;

  // "bus_naming_style"
  const AstString* mBusNamingStyle;

  // ピングループリストの要素数
  int mPinNum;

  // ピングループのリスト
  const AstPin** mPinList;

  // バスグループのリストの要素数
  int mBusNum;

  // バスグループのリスト
  const AstBus** mBusList;

  // バンドルグループのリストの要素数
  int mBundleNum;

  // バンドルグループのリスト
  const AstBundle** mBundleList;

  // ff グループ
  const AstFF* mFF;

  // latch グループ
  const AstLatch* mLatch;

  // statetable グループ
  const AstStateTable* mStateTable;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstCell::name() const
{
  return mName;
}

// @brief 面積を返す．
inline
const AstFloat*
AstCell::area() const
{
  return mArea;
}

// @brief bus_naming_style を返す．
inline
const AstString*
AstCell::bus_nameing_style() const
{
  return mBusNamingStyle;
}

// @brief ピングループのリストの要素数を返す．
inline
int
AstCell::pin_num() const
{
  return mPinNum;
}

// @brief ピングループのリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
inline
const AstPin*
AstCell::pin_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < pin_num() );

  return mPinList[pos];
}

// @brief バスグループのリストの要素数を返す．
inline
int
AstCell::bus_num() const
{
  return mBusNum;
}

// @brief バスグループのリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < bus_num() )
inline
const AstBus*
AstCell::bus_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < bus_num() );

  return mBusList[pos];
}

// @brief バンドルグループのリストの要素数を返す．
inline
int
AstCell::bundle_num() const
{
  return mBundleNum;
}

// @brief バンドルグループのリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < bundle_num() )
inline
const AstBundle*
AstCell::bundle_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < bundle_num() );

  return mBundleList[pos];
}

// @brief ff グループを返す．
inline
const AstFF*
AstCell::ff() const
{
  return mFF;
}

// @brief latch グループを返す．
inline
const AstLatch*
AstCell::latch() const
{
  return mLatch;
}

// @brief statetable グループを返す．
inline
const AstStateTable*
AstCell::state_table() const
{
  return mStateTable;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTCELL_H
