
/// @file Scanner.cc
/// @brief Scanner の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Scanner.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
Scanner::Scanner(InputFileObj& in) ///< [in] 入力ファイルオブジェクト
  : mIn{in},
    mSymbolMode{false}
{
}

// @brief 属性を読み込む．
AttrKwd
Scanner::read_attr()
{
  Token token;

  // 空行を読み飛ばす．
  for ( token = read_token(); token.type() == TokenType::NL; token = read_token() ) { }

  if ( token.type() != TokenType::SYMBOL ) {
    cout << "token.type() = " << token.type() << endl;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
		    "attribute keyword is expected");
    return AttrKwd{};
  }

  const char* attr_name = cur_string();
  return AttrKwd(attr_name, token.loc());
}

// @brief float のリストを読み込む．
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// dst_list は初期化せず，末尾に追加する．
bool
Scanner::read_raw_float_vector(vector<double>& dst_list, ///< [out] 値を格納するリスト
			       FileRegion& loc)    ///< [out] ファイル上の位置
{
  Token token = read_token();
  if ( token.type() != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return false;
  }

  const char* tmp_str = cur_string();
  string buf;
  char c = '\0';
  for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			token.loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return false;
      }
      char* end;
      double val = strtod(buf.c_str(), &end);
      if ( end[0] != '\0' ) {
	ostringstream emsg;
	emsg << "Syntax error: "
	     << buf << ": Could not convert to a number.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			token.loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			emsg.str());
	return false;
      }
      dst_list.push_back(val);
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(strtod(buf.c_str(), nullptr));
  }
  loc = token.loc();

  return true;
}

// @brief 文字列を読み込む．
// @return 文字列を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
const char*
Scanner::read_raw_string(FileRegion& value_loc) ///< [out] トークンのファイル上の位置
{
  auto old_symbol_flag{mSymbolMode};
  mSymbolMode = true;
  Token token = read_token();
  mSymbolMode = old_symbol_flag;
  if ( token.type() == TokenType::SYMBOL ) {
    value_loc = token.loc();
    return cur_string();
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return {};
  }
}

// @brief 次のトークンを調べる．
// @return トークンを返す．
//
// このトークンは読み込まれない．
Token
Scanner::peek_token()
{
  if ( mCurToken.type() == TokenType::ERROR ) {
    auto type = _scan();
    mCurToken = {type, FileRegion(mFirstLoc, mIn.cur_loc())};
  }
  return mCurToken;
}

// @brief 調べたトークンを読み込む．
void
Scanner::accept_token()
{
  mCurToken = Token{}; // 不正値
}

// @brief トークンを一つとってくる．
Token
Scanner::read_token()
{
  auto ans{peek_token()};
  accept_token();
  return ans;
}

// @brief トークンを読み込み，期待値と比較する．
Token
Scanner::read_and_verify(TokenType token_type)
{
  auto token{read_token()};
  if ( token.type() == token_type ) {
    return token;
  }

  // エラーメッセージを作る．
  const char* type_str = nullptr;
  switch ( token_type ) {
  case TokenType::COLON:      type_str = "':'"; break;
  case TokenType::SEMI:       type_str = "';'"; break;
  case TokenType::COMMA:      type_str = "','"; break;
  case TokenType::PLUS:       type_str = "'+'"; break;
  case TokenType::MINUS:      type_str = "'-'"; break;
  case TokenType::MULT:       type_str = "'*'"; break;
  case TokenType::DIV:        type_str = "'/'"; break;
  case TokenType::NOT:        type_str = "'!'"; break;
  case TokenType::AND:        type_str = "'&'"; break;
  case TokenType::OR:         type_str = "'|'"; break;
  case TokenType::XOR:        type_str = "'^'"; break;
  case TokenType::PRIME:      type_str = "'";   break;
  case TokenType::LP:         type_str = "'('"; break;
  case TokenType::RP:         type_str = "')'"; break;
  case TokenType::LCB:        type_str = "'{'"; break;
  case TokenType::RCB:        type_str = "'}'"; break;
  case TokenType::SYMBOL:     type_str = "STR"; break;
  case TokenType::INT_NUM:    type_str = "INT"; break;
  case TokenType::FLOAT_NUM:  type_str = "FLOAT"; break;
  case TokenType::EXPRESSION: type_str = "EXPRESSION"; break;
  case TokenType::NL:         type_str = "new-line"; break;
  default:                    ASSERT_NOT_REACHED;
  }
  ostringstream buf;
  buf << "syntax error. " << type_str << " is expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
  return Token{};
}

// @brief read_token() の下請け関数
// @return トークンの型を返す．
TokenType
Scanner::_scan()
{
  int c;

  mCurString.clear();

 ST_INIT: // 初期状態
  c = mIn.get();
  mFirstLoc = mIn.cur_loc();
  if ( _is_symbol(c) ) {
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
    ostringstream emsg;
    emsg << "Syntax error: " << c << ": Unexpected charactor.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
		    emsg.str());
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
  if ( _is_delimiter(c) ) {
    return TokenType::INT_NUM;
  }
  { // 数字の後に不適切な文字が付いている．
    mCurString.put_char(c);
    ostringstream emsg;
    emsg << "Syntx error: " << mCurString << ": Not a number value.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
		    emsg.str());
    return TokenType::ERROR;
  }

 ST_DOT: // [0-9]*'.' を読み込んだ時
  c = mIn.peek();
  if ( isdigit(c) ) {
    mIn.accept();
    mCurString.put_char(c);
    goto ST_NUM2;
  }
  { // '.' の直後はかならず数字
    mCurString.put_char(c);
    ostringstream buf;
    buf << "Syntax error: " << mCurString << ": Digit number expected after dot";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
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
  if ( _is_delimiter(c) ) {
    return TokenType::FLOAT_NUM;
  }
  { // 数字の後に不適切な文字が付いている．
    mCurString.put_char(c);
    ostringstream emsg;
    emsg << "Syntax error: " << mCurString << ": Not a number value.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
		    emsg.str());
    return TokenType::ERROR;
  }

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
		    "DOTLIB_SCANNER",
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
  if ( _is_symbol(c) || isdigit(c) ) {
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
		    "DOTLIB_SCANNER",
		    buf.str());
    return TokenType::ERROR;
  }
  if ( c == EOF ) {
    ostringstream buf;
    buf << "unexpected end-of-file in quoted string.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    mIn.cur_loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
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
		    "DOTLIB_SCANNER",
		    buf.str());
  }
  return TokenType::ERROR;
}

// @brief c が区切り文字の時に true を返す．
bool
Scanner::_is_delimiter(int c)
{
  if ( c == ' ' || c == '\t' || c == '\n' ||
       c == ',' || c == ';' || c == ')' ||
       c == EOF ) {
    return true;
  }
  return false;
}

// @brief c が文字の時に true を返す．
// @note mSymbolMode が true なら数字も文字とみなす．
bool
Scanner::_is_symbol(int c)
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
