#ifndef CELLINFO_H
#define CELLINFO_H

/// @file CellInfo.h
/// @brief CellInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/FFInfo.h"
#include "dotlib/LatchInfo.h"
#include "dotlib/FSMInfo.h"
#include "dotlib/PinInfo.h"
#include "dotlib/ElemDict.h"
#include "ym/ShString.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

class LibraryInfo;

//////////////////////////////////////////////////////////////////////
/// @class CellInfo CellInfo.h "CellInfo.h"
/// @brief セルのパース情報
//////////////////////////////////////////////////////////////////////
class CellInfo
{
public:

  /// @brief コンストラクタ
  CellInfo(
    LibraryInfo& library_info ///< [in] ライブラリのパース情報
  ) : mLibraryInfo{library_info}
  {
  }

  /// @brief デストラクタ
  ~CellInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* cell_val ///< [in] セル情報のパース木
  );

  /// @brief セルを作る．
  bool
  add_cell();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief FF セルを作る．
  SizeType
  add_ff_cell() const;

  /// @brief ラッチセルを作る．
  SizeType
  add_latch_cell() const;

  /// @brief FSM セルを作る．
  SizeType
  add_fsm_cell() const;

  /// @brief ライブラリを取り出す．
  CiCellLibrary*
  library() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリのパース情報
  LibraryInfo& mLibraryInfo;

  // 要素の辞書
  ElemDict mElemDict;

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea;

  // FF 関係の情報
  bool mHasFF;
  FFInfo mFFInfo;

  // ラッチ関係の情報
  bool mHasLatch;
  LatchInfo mLatchInfo;

  // FSM 関係の情報
  bool mHasFSM;
  FSMInfo mFSMInfo;

  // ピンの情報
  vector<PinInfo> mPinInfoList;

  // 割当済みの入力ピン番号
  SizeType mInputId;

  // 割当済みの出力ピン番号
  SizeType mOutputId;

  // ピン名をキーにして入力ピン番号を格納する辞書
  unordered_map<ShString, SizeType> mIpinMap;

  // ピン名をキーにして出力ピン番号を格納する辞書
  unordered_map<ShString, SizeType> mOpinMap;

};

END_NAMESPACE_YM_DOTLIB

#endif // CELLINFO_H
