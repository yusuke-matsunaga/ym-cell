#ifndef OUTPUTVOLTAGEHANDLER_H
#define OUTPUTVOLTAGEHANDLER_H

/// @file OutputVoltageHandler.h
/// @brief OutputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class OutputVoltageHandler OutputVoltageHandler.h "OutputVoltageHandler.h"
/// @brief input voltage 用のハンドラ
//////////////////////////////////////////////////////////////////////
class OutputVoltageHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  OutputVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~OutputVoltageHandler();


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
  gen_value(const FileRegion& loc,
	    const DotlibString* name,
	    const vector<DotlibAttr*>& attr_list) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // OUTPUTVOLTAGEHANDLER_H
