#ifndef CELLINTERNALPOWERHANDLER_H
#define CELLINTERNALPOWERHANDLER_H

/// @file CellInternalPowerHandler.h
/// @brief CellInternalPowerHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class CellInternalPowerHandler CellInternalPowerHandler.h "CellInternalPowerHandler.h"
/// @brief cell internal power 属性を読み込むためのハンドラ
//////////////////////////////////////////////////////////////////////
class CellInternalPowerHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  CellInternalPowerHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~CellInternalPowerHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  DotlibNode*
  gen_value(const DotlibList* value_list,
	    const DotlibAttr* attr_top);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // CELLINTERNALPOWERHANDLER_H
