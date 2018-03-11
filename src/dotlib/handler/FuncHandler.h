﻿#ifndef FUNCHANDLER_H
#define FUNCHANDLER_H

/// @file FuncHandler.h
/// @brief FuncHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"
#include "FhScanner.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FuncHandler FuncHandler.h "FuncHandler.h"
/// @brief function 属性の値をパーズする simple attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class FuncHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FuncHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~FuncHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @return 値を表す DotlibNode を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  /// ここでは function 属性用の論理式のパースを行う．
  virtual
  DotlibNode*
  read_value();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief primary を読み込む．
  DotlibExpr*
  read_primary();

  /// @brief プライム付きの primary を読み込む．
  DotlibExpr*
  read_primary2();

  /// @brief product を読み込む．
  DotlibExpr*
  read_product();

  /// @brief expression を読み込む．
  DotlibExpr*
  read_expr(TokenType end_marker);

  /// @brief トークンを読み込む．
  /// @param[out] loc 対応するファイル上の位置情報を格納する変数
  TokenType
  read_token(FileRegion& loc);

  /// @brief 読み込んだトークンを戻す．
  /// @param[in] type トークンの型
  /// @param[in] loc トークンの位置
  void
  unget_token(TokenType type,
	      const FileRegion& loc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  FhScanner mScanner;

  // 読み戻したトークンの型
  TokenType mUngetType;

  // 読み戻したトークンの位置
  FileRegion mUngetLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // FUNCHANDLER_H