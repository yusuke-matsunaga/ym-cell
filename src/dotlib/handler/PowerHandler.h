#ifndef POWERHANDLER_H
#define POWERHANDLER_H

/// @file PowerHandler.h
/// @brief PowerHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PowerHandler PowerHandler.h "PowerHandler.h"
/// @brief power table 用のハンドラ
//////////////////////////////////////////////////////////////////////
class PowerHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PowerHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~PowerHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const DotlibList* value_list,
	    const DotlibAttr* attr_top);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // POWERHANDLER_H