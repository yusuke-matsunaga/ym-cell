#ifndef DELAYMODELHANDLER_H
#define DELAYMODELHANDLER_H

/// @file DelayModelHandler.h
/// @brief DelayModelHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DelayModelHandler DelayModelHandler.h "DelayModelHandler.h"
/// @brief DelayModel値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class DelayModelHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DelayModelHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~DelayModelHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  AstNode*
  read_value();

};

END_NAMESPACE_YM_DOTLIB

#endif // DELAYMODELHANDLER_H
