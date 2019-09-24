#ifndef DOMAINHANDLER_H
#define DOMAINHANDLER_H

/// @file DomainHandler.h
/// @brief DomainHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DomainHandler DomainHandler.h "DomainHandler.h"
/// @brief 'domain' Group Statement 用のハンドラ
///
/// 現時点ではこのクラスは syntactical にパースするだけ．
//////////////////////////////////////////////////////////////////////
class DomainHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DomainHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~DomainHandler();


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
  // 内部で使われる下請け関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // calc_mode
  const AstString* mCalcMode;

  // coefs
  const AstFloatVector* mCoefs;

  // orders
  const AstIntVector* mOrders;

  // variable_1_range
  const AstFloat2* mVar1Range;

  // variable_2_range
  const AstFloat2* mVar2Range;

  // variable_3_range
  const AstFloat2* mVar3Range;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOMAINHANDLER_H
