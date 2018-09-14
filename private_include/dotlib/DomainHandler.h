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
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'domain' Group Statement の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstDomain*& dst);


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


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
  const AstVariableRange* mVar1Range;

  // variable_2_range
  const AstVariableRange* mVar2Range;

  // variable_3_range
  const AstVariableRange* mVar3Range;


  // 読み込んだ値
  const AstDomain* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOMAINHANDLER_H
