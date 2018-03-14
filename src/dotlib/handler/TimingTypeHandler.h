#ifndef TIMINGTYPEHANDLER_H
#define TIMINGTYPEHANDLER_H

/// @file TimingTypeHandler.h
/// @brief TimingTypeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingTypeHandler TimingTypeHandler.h "TimingTypeHandler.h"
/// @brief TimingType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingTypeHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TimingTypeHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TimingTypeHandler();


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

#endif // TIMINGTYPEHANDLER_H
