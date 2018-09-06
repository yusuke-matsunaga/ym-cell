#ifndef EXPRHANDLER_H
#define EXPRHANDLER_H

/// @file ExprHandler.h
/// @brief ExprHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ExprHandler ExprHandler.h "ExprHandler.h"
/// @brief expression の値をとる simple attribute 用のハンドラ
///
/// 見かけは SimpleHandler に似ているが，値が複数のトークンから構成される
/// ため別のクラスを用いる．
//////////////////////////////////////////////////////////////////////
class ExprHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ExprHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~ExprHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief expression 値の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstExpr*& dst);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstExpr* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // EXPRHANDLER_H
