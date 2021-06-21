#ifndef SCANNER_H
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
#include "ym/InputFileObj.h"
#include "ym/FileRegion.h"
#include "ym/StrBuff.h"
#include "AttrDic.h"


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
class Scanner
{
public:

  /// @brief コンストラクタ
  Scanner(InputFileObj& in); ///< [in] 入力ファイルオブジェクト

  /// @brief デストラクタ
  ~Scanner() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性名(AttrKwd)を読み込む関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性を読み込む．
  /// @return 属性を返す．
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
  read_and_verify(TokenType exp_type); ///< [in] 期待値

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief float のリストを読み込む．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起こった．
  ///
  /// dst_list は初期化せず，末尾に追加する．
  bool
  read_raw_float_vector(vector<double>& dst_list, ///< [out] 値を格納するリスト
			FileRegion& loc);         ///< [out] ファイル上の位置

  /// @brief 文字列を読み込む．
  /// @return 文字列を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  const char*
  read_raw_string(FileRegion& value_loc); ///< [out] トークンのファイル上の位置

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string() const { return mCurString.c_str(); }

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int() const { return strtol(cur_string(), nullptr, 10); }

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float() const { return strtod(cur_string(), nullptr); }


private:
  //////////////////////////////////////////////////////////////////////
  // 式の読み込みに関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief expression を読み込む．
  /// @return 生成した AstExpr を返す．
  ///
  /// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
  AstExprPtr
  _read_expr(TokenType end_marker); ///< [in] 末尾のトークンのタイプ

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

  /// @brief read_token() の下請け関数
  /// @return トークンの型を返す．
  TokenType
  _scan();

  /// @brief c が区切り文字の時に true を返す．
  bool
  _is_delimiter(int c);

  /// @brief c が文字の時に true を返す．
  ///
  /// mSymbolMode が true なら数字も文字とみなす．
  bool
  _is_symbol(int c);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ファイルオブジェクト
  InputFileObj& mIn;

  // 属性用の辞書
  AttrDic mAttrDic;

  // シンボルモード
  bool mSymbolMode;

  // _scan の結果のトークン
  Token mCurToken{};

  // _scan で処理中のトークンの先頭の位置
  FileLoc mFirstLoc;

  // _scan の結果の文字列を格納する
  StrBuff mCurString;

};

END_NAMESPACE_YM_DOTLIB

#endif // SCANNER_H
