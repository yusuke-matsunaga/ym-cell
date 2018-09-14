#ifndef TEMPLATEHANDLER_H
#define TEMPLATEHANDLER_H

/// @file TemplateHandler.h
/// @brief TemplateHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TemplateHandler TemplateHandler.h "TemplateHandler.h"
/// @brief 'lut_template' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class TemplateHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TemplateHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TemplateHandler();


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
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // variable_1
  const AstVarType* mVar1;

  // variable_2
  const AstVarType* mVar2;

  // variable_3
  const AstVarType* mVar3;

  // index_1
  const AstFloatVector* mIndex1;

  // index_2
  const AstFloatVector* mIndex2;

  // index_3
  const AstFloatVector* mIndex3;

  // domain
  const AstDomain* mDomain;

};

END_NAMESPACE_YM_DOTLIB

#endif // TEMPLATEHANDLER_H
