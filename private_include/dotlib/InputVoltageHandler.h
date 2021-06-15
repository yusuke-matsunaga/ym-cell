#ifndef INPUTVOLTAGEHANDLER_H
#define INPUTVOLTAGEHANDLER_H

/// @file InputVoltageHandler.h
/// @brief InputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InputVoltageHandler InputVoltageHandler.h "InputVoltageHandler.h"
/// @brief 'input_voltage' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class InputVoltageHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  InputVoltageHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~InputVoltageHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief vil の値を返す．
  const AstExpr*
  vil() const
  {
    return mVil;
  }

  /// @brief vih の値を返す．
  const AstExpr*
  vih() const
  {
    return mVih;
  }

  /// @brief vimin の値を返す．
  const AstExpr*
  vimin() const
  {
    return mVimin;
  }

  /// @brief vimax の値を返す．
  const AstExpr*
  vimax() const
  {
    return mVimax;
  }


public:
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

  // vil
  const AstExpr* mVil;

  // vih
  const AstExpr* mVih;

  // vimin
  const AstExpr* mVimin;

  // vimax
  const AstExpr* mVimax;

};

END_NAMESPACE_YM_DOTLIB

#endif // INPUTVOLTAGEHANDLER_H
