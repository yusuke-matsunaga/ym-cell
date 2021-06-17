#ifndef LIBRARIRYHANDLER_H
#define LIBRARIRYHANDLER_H

/// @file LibraryHandler.h
/// @brief LibraryHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class LibraryHandler LibraryHandler.h "LibraryHandler.h"
/// @brief 'library' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class LibraryHandler :
  public GroupHandler
{
  friend class AstLibrary;

public:

  /// @brief コンストラクタ
  LibraryHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~LibraryHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group() override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // string
  vector<const AstString*> mStrList;

  // "technology"
  const AstTechnology* mTechnology;

  // "delay_model"
  const AstDelayModel* mDelayModel;

  // "bus_naming_style"
  //const AstString* mBusNamingStyle;

  // "comment"
  //const AstString* mComment;

  // "date"
  //const AstString* mDate;

  // "revision"
  //const AstString* mRevision;

  // "capacitive_load_unit"
  const AstFloatStr* mCapacitiveLoadUnit;

  // "current_unit"
  //const AstString* mCurrentUnit;

  // "leakage_power_unit"
  //const AstString* mLeakagePowerUnit;

  // "pulling_resistance_unit"
  //const AstString* mPullingResistanceUnit;

  // "time_unit"
  //const AstString* mTimeUnit;

  // "voltage_unit"
  //const AstString* mVoltageUnit;

  // lu_table_template のリスト
  vector<const AstTemplate*> mLutTemplateList;

  // セルのリスト
  vector<const AstCell*> mCellList;

};

END_NAMESPACE_YM_DOTLIB

#endif // LIBRARIRYHANDLER_H
