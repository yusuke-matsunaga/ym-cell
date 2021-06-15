#ifndef OUTPUTVOLTAGEHANDLER_H
#define OUTPUTVOLTAGEHANDLER_H

/// @file OutputVoltageHandler.h
/// @brief OutputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class OutputVoltageHandler OutputVoltageHandler.h "OutputVoltageHandler.h"
/// @brief 'output_voltage' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class OutputVoltageHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  OutputVoltageHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~OutputVoltageHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief vil の値を返す．
  const AstExpr*
  vol() const
  {
    return mVol;
  }

  /// @brief vih の値を返す．
  const AstExpr*
  voh() const
  {
    return mVoh;
  }

  /// @brief vimin の値を返す．
  const AstExpr*
  vomin() const
  {
    return mVomin;
  }

  /// @brief vimax の値を返す．
  const AstExpr*
  vomax() const
  {
    return mVomax;
  }


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

  // vol
  const AstExpr* mVol;

  // voh
  const AstExpr* mVoh;

  // vomin
  const AstExpr* mVomin;

  // vomax
  const AstExpr* mVomax;

};

END_NAMESPACE_YM_DOTLIB

#endif // OUTPUTVOLTAGEHANDLER_H
