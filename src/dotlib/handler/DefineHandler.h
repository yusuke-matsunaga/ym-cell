#ifndef defineHANDLER_H
#define defineHANDLER_H

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
  /// @param[in] parser パーサー
  /// @param[in] parent 親のハンドラ
  DefineHandler(DotlibParser& parser,
		GroupHandler* parent);

  /// @brief デストラクタ
  ~DefineHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  ///
  /// エラーが起きたら nullptr を返す．
  bool
  parse_attr_value();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // defineHANDLER_H
