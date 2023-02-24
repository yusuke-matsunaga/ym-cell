#ifndef ASTCELLINFO_H
#define ASTCELLINFO_H

/// @file AstCellInfo.h
/// @brief AstCellInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AstFFInfo.h"
#include "dotlib/AstLatchInfo.h"
#include "dotlib/AstFSMInfo.h"
#include "dotlib/AstPinInfo.h"
#include "ym/ShString.h"
#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstCellInfo AstCellInfo.h "AstCellInfo.h"
/// @brief セルのパース情報
//////////////////////////////////////////////////////////////////////
class AstCellInfo
{
public:

  /// @brief コンストラクタ
  AstCellInfo() = default;

  /// @brief デストラクタ
  ~AstCellInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue* cell_val,  ///< [in] セル情報のパース木
    ClibDelayModel delay_model ///< [in] ディレイモデル
  );

  /// @brief セルを作る．
  bool
  add_cell(
    CiCellLibrary* library
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief FF セルを作る．
  SizeType
  add_ff_cell(
    CiCellLibrary* library
  ) const;

  /// @brief ラッチセルを作る．
  SizeType
  add_latch_cell(
    CiCellLibrary* library
  ) const;

  /// @brief FSM セルを作る．
  SizeType
  add_fsm_cell(
    CiCellLibrary* library
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // 面積
  ClibArea mArea;

  // FF 関係の情報
  bool mHasFF;
  AstFFInfo mFFInfo;

  // ラッチ関係の情報
  bool mHasLatch;
  AstLatchInfo mLatchInfo;

  // FSM 関係の情報
  bool mHasFSM;
  AstFSMInfo mFSMInfo;

  // ピンの情報
  vector<AstPinInfo> mPinInfoList;

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

#endif // ASTCELLINFO_H
