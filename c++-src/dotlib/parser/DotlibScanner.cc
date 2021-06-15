
/// @file DotlibScanner.cc
/// @brief DotlibScanner の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibScanner.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief トークンを一つとってくる．
// @param[out] loc ファイル上の位置情報を格納する変数
// @param[in] symbol_mode 数字も文字とみなすモード
TokenType
DotlibScanner::read_token(FileRegion& loc,
			  bool symbol_mode)
{
  mSymbolMode = symbol_mode;
  TokenType type = scan();
  loc = FileRegion{mFirstLoc, mIn.cur_loc()};
  return type;
}

// @brief read_token() の下請け関数
// @return トークンの型を返す．
TokenType
DotlibScanner::scan()
{
  int c;

  mCurString.clear();

 ST_INIT: // 初期状態
  c = mIn.get();
  mFirstLoc = mIn.cur_loc();
  if ( is_symbol(c) ) {
    mCurString.put_char(c);
    goto ST_ID;
  }
  if ( isdigit(c) ) {
    mCurString.put_char(c);
    goto ST_NUM1;
  }

  switch (c) {
  case '.':
    mCurString.put_char(c);
    goto ST_DOT;

  case EOF:
    return TokenType::END;

  case ' ':
  case '\t':
    goto ST_INIT; // 最初の空白は読み飛ばす．

  case '\n':
    return TokenType::NL;

  case '\"':
    goto ST_DQ;

  case '\\':
    c = mIn.peek();
    if ( c == '\n' ) {
      // 無視する．
      mIn.accept();
      goto ST_INIT;
    }
    // それ以外はバックスラッシュがなかったことにする．
    goto ST_INIT;

  case '/':
    goto ST_comment1;

  case ':':
    return TokenType::COLON;

  case ';':
    return TokenType::SEMI;

  case ',':
    return TokenType::COMMA;

  case '+':
    return TokenType::PLUS;

  case '-':
    goto ST_MINUS;

  case '*':
    return TokenType::MULT;

  case '(':
    return TokenType::LP;

  case ')':
    return TokenType::RP;

  case '{':
    return TokenType::LCB;

  case '}':
    return TokenType::RCB;

  default:
    // それ以外はエラーなんじゃない？
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    "syntax error");
    return TokenType::ERROR;
  }
  ASSERT_NOT_REACHED;

 ST_MINUS: // '-' を読み込んだ時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char('-');
    mCurString.put_char(c);
    goto ST_NUM1;
  }
  return TokenType::MINUS;

 ST_NUM1: // 一文字目が[0-9]の時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM1;
  }
  if ( c == '.' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_DOT;
  }
  return TokenType::INT_NUM;

 ST_DOT: // [0-9]*'.' を読み込んだ時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM2;
  }
  { // '.' の直後はかならず数字
    ostringstream buf;
    buf << "digit number expected after dot";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    buf.str());
    return TokenType::ERROR;
  }

 ST_NUM2: // [0-9]*'.'[0-9]* を読み込んだ時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM2;
  }
  if ( c == 'e' || c == 'E' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM3;
  }
  return TokenType::FLOAT_NUM;

 ST_NUM3: // [0-9]*'.'[0-9]*(e|E)を読み込んだ時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM4;
  }
  if ( c == '+' || c == '-' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM4;
  }
  { // (e|E) の直後はかならず数字か符号
    ostringstream buf;
    buf << "exponent value expected";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    buf.str());
    return TokenType::ERROR;
  }

 ST_NUM4: // [0-9]*'.'[0-9]*(e|E)(+|-)?[0-9]*を読み込んだ直後
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM4;
  }
  return TokenType::FLOAT_NUM;

 ST_ID: // 一文字目が[a-zA-Z_]の時
  c = mIn.peek();
  if ( is_symbol(c) || isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_ID;
  }
  return TokenType::SYMBOL;

 ST_DQ: // "があったら次の"までを強制的に文字列だと思う．
  c = mIn.get();
  if ( c == '\"' ) {
    return TokenType::SYMBOL;
  }
  if ( c == '\n' ) {
    ostringstream buf;
    buf << "unexpected newline in quoted string.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    buf.str());
    return TokenType::ERROR;
  }
  if ( c == EOF ) {
    ostringstream buf;
    buf << "unexpected end-of-file in quoted string.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    buf.str());
    return TokenType::ERROR;
  }
  if ( c == '\\' ) {
    c = mIn.get();
    if ( c != '\n' ) {
      // 改行以外はバックスラッシュをそのまま解釈する．
      mCurString.put_char('\\');
    }
  }
  mCurString.put_char(c);
  goto ST_DQ;

 ST_comment1: // '/' を読み込んだ直後
  c = mIn.peek();
  if ( c == '/' ) { // C++ スタイルのコメント
    mIn.accept();
    goto ST_comment2;
  }
  if ( c == '*' ) { // C スタイルのコメント
    mIn.accept();
    goto ST_comment3;
  }
  return TokenType::DIV;

 ST_comment2: // 改行まで読み飛ばす．
  c = mIn.get();
  if ( c == '\n' ) {
    goto ST_INIT;
  }
  if ( c == EOF ) {
    return TokenType::END;
  }
  goto ST_comment2;

 ST_comment3: // "/*" を読み込んだ直後
  c = mIn.get();
  if ( c == EOF ) {
    goto ST_EOF;
  }
  if ( c == '*' ) {
    goto ST_comment4;
  }
  goto ST_comment3;

 ST_comment4: // "/* 〜 *" まで読み込んだ直後
  c = mIn.get();
  if ( c == EOF ) {
    goto ST_EOF;
  }
  if ( c == '/' ) {
    goto ST_INIT;
  }
  if ( c == '*' ) {
    goto ST_comment4;
  }
  goto ST_comment3;

 ST_EOF:
  {
    ostringstream buf;
    buf << "Unexpected end-of-file in comment block.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_LEX",
		    buf.str());
  }
  return TokenType::ERROR;
}

// @brief c が文字の時に true を返す．
// @note mSymbolMode が true なら数字も文字とみなす．
bool
DotlibScanner::is_symbol(int c)
{
  if ( isalpha(c) || c == '_' ) {
    return true;
  }
  if ( mSymbolMode ) {
    if ( isdigit(c) || c == '.' ) {
      return true;
    }
  }
  return false;
}

END_NAMESPACE_YM_DOTLIB
