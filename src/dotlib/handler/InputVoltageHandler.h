#ifndef INPUTVOLTAGEHANDLER_H
#define INPUTVOLTAGEHANDLER_H

/// @file InputVoltageHandler.h
/// @brief InputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InputVoltageHandler InputVoltageHandler.h "InputVoltageHandler.h"
/// @brief input voltage 用のハンドラ
//////////////////////////////////////////////////////////////////////
class InputVoltageHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  InputVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~InputVoltageHandler();


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
  AstNode*
  gen_node(const FileRegion& loc,
	   const AstString* name,
	   const vector<AstAttr*>& attr_list);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // INPUTVOLTAGEHANDLER_H
