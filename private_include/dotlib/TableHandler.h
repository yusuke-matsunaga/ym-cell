#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

/// @file TableHandler.h
/// @brief TableHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
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
  TableHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~TableHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // インライン関数の定義
  //////////////////////////////////////////////////////////////////////

  /// @brief index_1 を返す．
  const AstFloatVector*
  index_1() const
  {
    return mIndex1;
  }

  /// @brief index_2 を返す．
  const AstFloatVector*
  index_2() const
  {
    return mIndex2;
  }

  /// @brief index_3 を返す．
  const AstFloatVector*
  index_3() const
  {
    return mIndex3;
  }

  /// @brief values を返す．
  const AstFloatVector*
  values() const
  {
    return mValues;
  }

  /// @brief coefs を返す．
  const AstFloatVector*
  coefs() const
  {
    return mCoefs;
  }

  /// @brief orders を返す．
  const AstIntVector*
  orders() const
  {
    return mOrders;
  }

  /// @brief variable_1_range を返す．
  const AstFloat2*
  variable_1_range() const
  {
    return mVar1Range;
  }

  /// @brief variable_2_range を返す．
  const AstFloat2*
  variable_2_range() const
  {
    return mVar2Range;
  }

  /// @brief variable_3_range を返す．
  const AstFloat2*
  variable_3_range() const
  {
    return mVar3Range;
  }

  /// @brief domain を返す．
  const AstDomain*
  domain() const
  {
    return mDomain;
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
