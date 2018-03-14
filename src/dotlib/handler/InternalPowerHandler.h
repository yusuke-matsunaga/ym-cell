#ifndef INTERNALpowerHANDLER_H
#define INTERNALpowerHANDLER_H

/// @file InternalPowerHandler.h
/// @brief InternalPowerHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InternalPowerHandler InternalPowerHandler.h "InternalPowerHandler.h"
/// @brief internal power グループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class InternalPowerHandler :
  public EmptyGroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  InternalPowerHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~InternalPowerHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を作る．
  virtual
  const AstNode*
  gen_node(const FileRegion& loc,
	   const vector<const AstAttr*>& attr_list) override;


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

#endif // INTERNALpowerHANDLER_H
