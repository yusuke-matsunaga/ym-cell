#ifndef EXPRHANDLER_H
#define EXPRHANDLER_H

/// @file ExprHandler.h
/// @brief ExprHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ExprHandler ExprHandler.h "ExprHandler.h"
/// @brief expression の値をとる simple attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class ExprHandler :
  public SimpleHandler
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
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ値を表す AstNode を返す．
  ///
  /// エラーの場合には nullptr を返す．
  virtual
  const AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ式を表す AstExpr を返す．
  ///
  /// エラーの場合には nullptr を返す．
  const AstExpr*
  parse(AttrType attr_type,
	const FileRegion& attr_loc);

  /// @brief パーズして代入する．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] dst 代入先
  /// @retval true 正常に処理した．
  /// @retval false 処理中にエラーが起こった．
  ///
  /// dst が nullptr でない場合には二重定義エラーとなる．
  bool
  parse_and_assign(AttrType attr_type,
		   const FileRegion& attr_loc,
		   const AstExpr*& dst);


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @return 値を表す AstNode を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  /// ここでは expression のパースを行う．
  virtual
  AstNode*
  gen_node() override;


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

};

END_NAMESPACE_YM_DOTLIB

#endif // EXPRHANDLER_H
