﻿#ifndef PWCOMPLEXHANDLER_H
#define PWCOMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PwComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief 折れ線近似モデル用ののcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class PwComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  PwComplexHandler(GroupHandler* parent);

  /// @brief デストラクタ
  virtual
  ~PwComplexHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] value_list 値のリスト
  virtual
  DotlibNode*
  gen_value(DotlibList* value_list);

};

END_NAMESPACE_YM_DOTLIB

#endif // PWCOMPLEXHANDLER_H