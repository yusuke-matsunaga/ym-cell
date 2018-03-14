#ifndef STR1COMPLEXHANDLER_H
#define STR1COMPLEXHANDLER_H

/// @file Str1ComplexHandler.h
/// @brief Str1ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str1Str1ComplexHandler Str1ComplexHandler.h "Str1ComplexHandler.h"
/// @brief 1つの文字列型をとる complex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class Str1ComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Str1ComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str1ComplexHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] value_list 値のリスト
  virtual
  const AstNode*
  gen_value(const vector<const AstNode*>& value_list);

};

END_NAMESPACE_YM_DOTLIB

#endif // STR1COMPLEXHANDLER_H
