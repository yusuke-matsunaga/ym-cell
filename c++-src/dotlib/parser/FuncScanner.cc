
/// @file FuncScanner.cc
/// @brief FuncScanner の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "FuncScanner.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FuncScanner
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] str 文字列
// @param[in] str のファイル上の位置
FuncScanner::FuncScanner(const string& str,
			 const FileRegion& loc)
  : mSrcString{str},
    mSrcLoc{loc},
    mCurPos{0},
    mUngetType{TokenType::ERROR}
{
}

// @brief デストラクタ
FuncScanner::~FuncScanner()
{
}

// @brief トークンを読み込む．
// @param[out] loc 対応するファイル上の位置情報を格納する変数
TokenType
FuncScanner::read_token(FileRegion& loc)
{
  if ( mUngetType != TokenType::ERROR ) {
    TokenType ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }

  mCurString.clear();

  int c;

 ST_INIT: // 初期状態
  c = get();
  set_first_loc();
  if ( isalpha(c) || c == '_' ) {
    mCurString.put_char(c);
    goto ST_ID;
  }
  if ( c == '0' || c == '1' ) {
    mCurString.put_char(c);
    goto ST_NUM;
  }

  switch ( c ) {
  case '\0':
    loc = cur_loc();
    return TokenType::END;

  case ' ':
  case '\t':
    goto ST_INIT; // 最初の空白は読み飛ばす．

  case '!':
    loc = cur_loc();
    return TokenType::NOT;

  case '|':
  case '+':
    loc = cur_loc();
    return TokenType::OR;

  case '&':
  case '*':
    loc = cur_loc();
    return TokenType::AND;

  case '^':
    loc = cur_loc();
    return TokenType::XOR;

  case '(':
    loc = cur_loc();
    return TokenType::LP;

  case ')':
    loc = cur_loc();
    return TokenType::RP;

  case '\'':
    loc = cur_loc();
    return TokenType::PRIME;

  default:
    // それ以外はエラー
    MsgMgr::put_msg(__FILE__, __LINE__,
		    cur_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error");
    loc = cur_loc();
    return TokenType::ERROR;
  }

 ST_ID: // 文字列モード
  c = peek();
  if ( isalnum(c) || c == '_' ) {
    accept();
    mCurString.put_char(c);
    goto ST_ID;
  }
  loc = cur_loc();
  return TokenType::SYMBOL;

 ST_NUM: // 数字モード
  c = peek();
  if ( c == '0' || c == '1' ) {
    accept();
    mCurString.put_char(c);
    goto ST_NUM;
  }
  loc = cur_loc();
  return TokenType::INT_NUM;
}

// @brief 読み込んだトークンを戻す．
// @param[in] type トークンの型
// @param[in] loc トークンの位置
void
FuncScanner::unget_token(TokenType type,
			 const FileRegion& loc)
{
  mUngetType = type;
  mUngetLoc = loc;
}

// @brief 直前の read_token() で読んだトークン文字列を返す．
const char*
FuncScanner::cur_string()
{
  return mCurString.c_str();
}

// @brief 直前の read_token() で読んだトークンの整数値を返す．
int
FuncScanner::cur_int()
{
  return strtol(mCurString.c_str(), nullptr, 10);
}

// @brief 一文字読み出す．
int
FuncScanner::get()
{

  int c = peek();
  accept();
  return c;
}

// @brief 一文字先読みする．
int
FuncScanner::peek()
{
  return mSrcString[mCurPos];
}

// @brief 先読みを確定する．
void
FuncScanner::accept()
{
  ++ mCurPos;
}

// @brief トークンの先頭のファイル位置を設定する．
void
FuncScanner::set_first_loc()
{
  mFirstColumn = mCurPos;
}

// @brief 現在のファイル位置を返す．
FileRegion
FuncScanner::cur_loc()
{
  return FileRegion(mSrcLoc.start_file_info(),
		    mSrcLoc.start_line(), mSrcLoc.start_column() + mFirstColumn,
		    mSrcLoc.start_line(), mSrcLoc.start_column() + mCurPos);
}

END_NAMESPACE_YM_DOTLIB
