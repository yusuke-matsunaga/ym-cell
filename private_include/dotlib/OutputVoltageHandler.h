#ifndef OUTPUTVOLTAGEHANDLER_H
#define OUTPUTVOLTAGEHANDLER_H

/// @file OutputVoltageHandler.h
/// @brief OutputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
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
  /// @param[in] parser パーサー
  OutputVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~OutputVoltageHandler();


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
