#ifndef DEFINEHANDLER_H
#define DEFINEHANDLER_H

/// @file DefineHandler.h
/// @brief DefineHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DefineHandler DefineHandler.h "DefineHandler.h"
/// @brief define attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class DefineHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  DefineHandler(GroupHandler* parent);

  /// @brief デストラクタ
  virtual
  ~DefineHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return エラーが起きたら false を返す．
  virtual
  bool
  read_attr(AttrType attr_type,
	    const FileRegion& attr_loc);

};

END_NAMESPACE_YM_DOTLIB

#endif // DEFINEHANDLER_H
