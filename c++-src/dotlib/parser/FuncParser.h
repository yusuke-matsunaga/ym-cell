#ifndef FUNCPARSER_H
#define FUNCPARSER_H

/// @file FuncParser.h
/// @brief FuncParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "FuncScanner.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FuncParser FuncParser.h "FuncParser.h"
/// @brief function 属性の値をパーズするクラス
///
/// やっていることは ExprHandler と似ているが，こっちはもとのデータが
/// 文字列なので一旦 FuncScanner に設定し直している．
//////////////////////////////////////////////////////////////////////
class FuncParser
{
public:

  /// @brief コンストラクタ
  /// @param[in] str 対象の文字列
  /// @param[in] loc ファイル上の位置
  /// @param[in] mgr AstMgr
  FuncParser(const string& str,
	     const FileRegion& loc,
	     AstMgr& mgr);

  /// @brief デストラクタ
  ~FuncParser();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 論理式を読み込む．
  unique_ptr<const AstValue>
  operator()();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief primary を読み込む．
  const AstExpr*
  read_primary();

  /// @brief プライム付きの primary を読み込む．
  const AstExpr*
  read_primary2();

  /// @brief product を読み込む．
  const AstExpr*
  read_product();

  /// @brief expression を読み込む．
  const AstExpr*
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
  FuncScanner mScanner;

  // 読み戻したトークンの型
  TokenType mUngetType;

  // 読み戻したトークンの位置
  FileRegion mUngetLoc;

  // AstMgr
  AstMgr& mMgr;

};

END_NAMESPACE_YM_DOTLIB

#endif // FUNCPARSER_H
