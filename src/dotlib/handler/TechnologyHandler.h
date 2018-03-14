#ifndef technologyHANDLER_H
#define technologyHANDLER_H

/// @file TechnologyHandler.h
/// @brief TechnologyHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TechnologyHandler TechnologyHandler.h "TechnologyHandler.h"
/// @brief Technology値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TechnologyHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TechnologyHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TechnologyHandler();


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

#endif // technologyHANDLER_H
