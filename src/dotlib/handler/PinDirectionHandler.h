#ifndef PINDIRECTIONHANDLER_H
#define PINDIRECTIONHANDLER_H

/// @file PinDirectionHandler.h
/// @brief PinDirectionHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PinDirectionHandler PinDirectionHandler.h "PinDirectionHandler.h"
/// @brief PinDirection値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class PinDirectionHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PinDirectionHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~PinDirectionHandler();


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

#endif // PINDIRECTIONHANDLER_H
