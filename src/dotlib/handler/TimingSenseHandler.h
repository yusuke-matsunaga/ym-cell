#ifndef TIMINGSENSEHANDLER_H
#define TIMINGSENSEHANDLER_H

/// @file TimingSenseHandler.h
/// @brief TimingSenseHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingSenseHandler TimingSenseHandler.h "TimingSenseHandler.h"
/// @brief TimingSense値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingSenseHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TimingSenseHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TimingSenseHandler();


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

#endif // TIMINGSENSEHANDLER_H
