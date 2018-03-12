#ifndef VARTYPEHANDLER_H
#define VARTYPEHANDLER_H

/// @file VarTypeHandler.h
/// @brief VarTypeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class VarTypeHandler VarTypeHandler.h "VarTypeHandler.h"
/// @brief VarType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class VarTypeHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  VarTypeHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~VarTypeHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};

END_NAMESPACE_YM_DOTLIB

#endif // VARTYPEHANDLER_H
