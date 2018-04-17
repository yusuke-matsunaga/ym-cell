#ifndef EXPRHANDLER_H
#define EXPRHANDLER_H

/// @file ExprHandler.h
/// @brief ExprHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
//#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ExprHandler ExprHandler.h "ExprHandler.h"
/// @brief expression の値をとる simple attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class ExprHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  ExprHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~ExprHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstExpr*
  value() const;


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief primary を読み込む．
  AstExpr*
  read_primary();

  /// @brief prudct を読み込む．
  AstExpr*
  read_product();

  /// @brief expression を読み込む．
  AstExpr*
  read_expr(TokenType end_marker);

  /// @brief トークンを読み込む．
  /// @param[out] loc 対応するファイル上の位置情報を格納する変数
  TokenType
  read_token(FileRegion& loc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み戻したトークンの型
  TokenType mUngetType;

  // 読み戻したトークンの位置
  FileRegion mUngetLoc;

  // 読み込んだ値
  AstExpr* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // EXPRHANDLER_H
