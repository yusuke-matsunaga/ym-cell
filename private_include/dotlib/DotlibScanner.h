﻿#ifndef SCANNER_H
#define SCANNER_H

/// @file Scanner.h
/// @brief Scanner のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AttrKwd.h"
#include "dotlib/AstValue.h"
#include "dotlib/Token.h"
#include "ym/FileRegion.h"
#include "ym/Scanner.h"
#include "ym/StrBuff.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Scanner Scanner.h "dotlib/Scanner.h"
/// @brief dotlib フォーマットの字句解析器
///
/// dotlib では次に読む値の種類が事前に予想できるので，
/// 個別の値を読み込む関数を用意する．
///
/// 結果は AstValue の unique_ptr (AstValuePtr) が返される．
//////////////////////////////////////////////////////////////////////
class DotlibScanner :
  public Scanner
{
public:

  /// @brief コンストラクタ
  DotlibScanner(
    istream& s,               ///< [in] 入力ストリーム
    const FileInfo& file_info ///< [in] ファイル情報
  ) : Scanner(s, file_info)
  {
  }

  /// @brief デストラクタ
  ~DotlibScanner() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性名(AttrKwd)を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性を読み込む．
  /// @return 属性を返す．
  ///
  /// 具体的には ':' または '(' をエンドマーカーとして
  /// 非空白文字からなる文字列を読み込む．
  /// " によるクォートやエスケープシーケンスはない．
  AttrKwd
  read_attr();


public:
  //////////////////////////////////////////////////////////////////////
  /// @{
  /// @name 値(AstValue) を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief int 型を値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーの時は nullptr を返す．
  AstValuePtr
  read_int();

  /// @brief float 型の値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_float();

  /// @brief string 型の値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_string();

  /// @brief bool 型の値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_bool();

  /// @brief delay_model 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_delay_model();

  /// @brief direction 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_direction();

  /// @brief technology 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_technology();

  /// @brief timing_sense 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_timing_sense();

  /// @brief timing_type 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_timing_type();

  /// @brief vartype 型の値を読み込む．
  /// @param[in] 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_vartype();

  /// @brief int vector 型の値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_int_vector();

  /// @brief float vector 型の値を読み込む．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_float_vector();

  /// @brief 式を表す AstValue を生成する．
  /// @return 生成した AstValue を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstValuePtr
  read_expr();

  /// @brief "式" を表す AstValue を生成する．
  AstValuePtr
  read_function();

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


public:
  //////////////////////////////////////////////////////////////////////
  /// @{
  /// @name トークンを読み込む関数
  ///
  /// Parser から用いられる．
  //////////////////////////////////////////////////////////////////////

  /// @brief 次のトークンを調べる．
  /// @return トークンを返す．
  ///
  /// このトークンは読み込まれない．
  Token
  peek_token();

  /// @brief 調べたトークンを読み込む．
  void
  accept_token();

  /// @brief トークンを一つ読み込む．
  /// @return トークンを返す．
  ///
  /// peek_token(); accept_token() と等価
  Token
  read_token();

  /// @brief トークンを読み込み，期待値と比較する．
  /// @return トークンを返す．
  ///
  /// 期待値と異なっていた場合，エラーメッセージを出力し
  /// 不正値(TokenType::none)を返す．
  Token
  read_and_verify(
    TokenType exp_type ///< [in] 期待値
  );

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // 式の読み込みに関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief expression を読み込む．
  /// @return 生成した AstExpr を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstExprPtr
  _read_expr(
    TokenType end_marker ///< [in] 末尾のトークンのタイプ
  );

  /// @brief primary を読み込む．
  AstExprPtr
  _read_primary();

  /// @brief prudct を読み込む．
  AstExprPtr
  _read_product();


private:
  //////////////////////////////////////////////////////////////////////
  // 低レベルの下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 一語読み込む．
  /// @return 読み込んだトークンを返す．
  ///
  /// Cスタイルのコメント '/* - */' と
  /// C++スタイルのコメント '//' を認識して
  /// 読み飛ばす．
  ///
  TokenType
  _scan();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // _scan の結果のトークン
  Token mCurToken{};

  // _scan の結果の文字列を格納する
  StrBuff mCurString;

};

END_NAMESPACE_YM_DOTLIB

#endif // SCANNER_H
