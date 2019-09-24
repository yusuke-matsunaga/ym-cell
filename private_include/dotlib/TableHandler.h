#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

/// @file TableHandler.h
/// @brief TableHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TableHandler TableHandler.h "TableHandler.h"
/// @brief look-up table 用のハンドラ
//////////////////////////////////////////////////////////////////////
class TableHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TableHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TableHandler();


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

  // index_1
  const AstFloatVector* mIndex1;

  // index_2
  const AstFloatVector* mIndex2;

  // index_3
  const AstFloatVector* mIndex3;

  // values
  const AstFloatVector* mValues;

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

  // domain
  const AstDomain* mDomain;

};

END_NAMESPACE_YM_DOTLIB

#endif // TABLEHANDLER_H
