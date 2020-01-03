
/// @file MislibScanner.cc
/// @brief MislibScanner の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "MislibScanner.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_MISLIB

// コンストラクタ
// @param[in] in 入力ファイルオブジェクト
MislibScanner::MislibScanner(InputFileObj& in) :
  mIn{in}
{
}

// トークンを一つとってくる．
// @param[out] loc 対応するファイル上の位置を格納する変数
MislibToken
MislibScanner::read_token(FileRegion& loc)
{
  MislibToken token = scan();
  loc = FileRegion{mFirstLoc, mIn.cur_loc()};
  return token;
}

// @brief read_token の下請け関数
// @return トークンを返す．
MislibToken
MislibScanner::scan()
{
  int c = 0;

  mCurString.clear();

 state1:
  c = mIn.get();
  mFirstLoc = mIn.cur_loc();
  if ( isalpha(c) || (c == '_') ) {
    mCurString.put_char(c);
    goto state2;
  }
  if ( isdigit(c) || (c == '-') ) {
    mCurString.put_char(c);
    goto state3;
  }
  switch (c) {
  case EOF: return END;
  case ' ':
  case '\t': goto state1;
  case '\n': goto state1;
  case '.': mCurString.put_char(c); goto state4;
  case ';': return SEMI;
  case '=': return EQ;
  case '(': return LP;
  case ')': return RP;
  case '!': return NOT;
  case '*': return STAR;
  case '&': return STAR;
  case '+': return PLUS;
  case '|': return PLUS;
  case '^': return HAT;
  case '#': goto state6;
  case '\"': goto state7;
  }
  goto error;

  // 一文字目が[a-zA-Z_]の時
 state2:
  c = mIn.peek();
  if ( isalpha(c) || isdigit(c) || (c == '_') ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state2;
  }

  // 予約語（？）の検査
  // 数が少ないのでナイーブな方法をとっている．
  if ( mCurString == "GATE" ) {
    return GATE;
  }
  if ( mCurString == "PIN" ) {
    return PIN;
  }
  if ( mCurString == "NONINV" ) {
    return NONINV;
  }
  if ( mCurString == "INV" ) {
    return INV;
  }
  if ( mCurString == "UNKNOWN" ) {
    return UNKNOWN;
  }
  if ( mCurString == "CONST0" ) {
    return CONST0;
  }
  if ( mCurString == "CONST1" ) {
    return CONST1;
  }
  return STR;

  // 一文字目が[0-9]の時
 state3:
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state3;
  }
  if ( c == '.' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state5;
  }
  if ( c == 'E' || c == 'e' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state8;
  }
  return NUM;

  // 一文字目が"."の時
 state4:
  c = mIn.get();
  if ( isdigit(c) ) {
    mCurString.put_char(c);
    goto state5;
  }
  goto error;

  // [0-9]*"."を読み終えたところ
 state5:
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state5;
  }
  if ( c == 'E' || c == 'e' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state8;
  }
  return NUM;

  // [0-9]*"."[Ee]を読み終えたところ
 state8:
  c = mIn.peek();
  if ( c == '-' ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state9;
  }
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state9;
  }
  return NUM;

  // [0-9]*"."[Ee]-?を読み終えたところ
 state9:
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto state9;
  }
  return NUM;

  // '#'があったら改行までループする．
 state6:
  c = mIn.get();
  if ( c == '\n' ) {
    goto state1;
  }
  goto state6;

  // "があったら次の"までを強制的に文字列だと思う．
 state7:
  c = mIn.get();
  if ( c == '\"' ) {
    return STR;
  }
  mCurString.put_char(c);
  goto state7;

 error:
  {
    ostringstream buf;
    buf << "Syntax error: illegal input (" << mCurString << ").";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "MISLIB_PARSE",
		    buf.str().c_str());
  }
  return ERROR;
}

END_NAMESPACE_YM_MISLIB
