#ifndef DOTLIBCELL_H
#define DOTLIBCELL_H

/// @file DotlibCell.h
/// @brief DotlibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
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

  /// @brief ピングループのリストを返す．
  const vector<const DotlibNode*>&
  pin_list() const;

  /// @brief バスグループのリストを返す．
  const vector<const DotlibNode*>&
  bus_list() const;

  /// @brief バンドルグループのリストを返す．
  const vector<const DotlibNode*>&
  bundle_list() const;

  /// @brief ff グループを返す．
  /// @note なければ nullptr を返す．
  const DotlibNode*
  ff() const;

  /// @brief latch グループを返す．
  /// @note なければ nullptr を返す．
  const DotlibNode*
  latch() const;

  /// @brief statetable グループを返す．
  /// @note なければ nullptr を返す．
  const DotlibNode*
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

  // ピングループのリスト
  vector<const DotlibNode*> mPinList;

  // バスグループのリスト
  vector<const DotlibNode*> mBusList;

  // バンドルグループのリスト
  vector<const DotlibNode*> mBundleList;

  // ff グループ
  const DotlibNode* mFF;

  // latch グループ
  const DotlibNode* mLatch;

  // statetable グループ
  const DotlibNode* mStateTable;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBCELL_H
