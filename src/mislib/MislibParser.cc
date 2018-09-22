
/// @file MislibParser.cc
/// @brief MislibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibParser.h"
#include "MislibMgr.h"
#include "MislibStr.h"
#include "MislibNum.h"
#include "MislibExpr.h"
#include "MislibGate.h"
#include "MislibPin.h"
#include "ym/HashMap.h"
#include "ym/HashSet.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_MISLIB

BEGIN_NONAMESPACE

// MislibScanner::read_token() をデバッグする時に true にする．
bool debug_read_token = false;

END_NONAMESPACE

BEGIN_NONAMESPACE

// 論理式中に現れる名前を ipin_set に積む．
void
get_ipin_names(const MislibExpr* expr_node,
	       HashSet<ShString>& ipin_set)
{
  ShString name;

  switch ( expr_node->type() ) {
  case MislibExpr::Const0:
  case MislibExpr::Const1:
    // 定数は無視
    return;

  case MislibExpr::VarName:
    if ( !ipin_set.check(expr_node->varname()) ) {
      ipin_set.add(expr_node->varname());
    }
    break;

  case MislibExpr::Not:
    get_ipin_names(expr_node->child1(), ipin_set);
    break;

  case MislibExpr::And:
  case MislibExpr::Or:
  case MislibExpr::Xor:
    get_ipin_names(expr_node->child1(), ipin_set);
    get_ipin_names(expr_node->child2(), ipin_set);
    break;

  default:
    ASSERT_NOT_REACHED;
  }
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス MislibParser
//////////////////////////////////////////////////////////////////////

// コンストラクタ
// @param[in] ido 入力データオブジェクト
// @param[in] mgr MislibNode を管理するオブジェクト
MislibParser::MislibParser(IDO& ido,
			   MislibMgr& mgr) :
  mMgr(mgr),
  mScanner(ido)
{
  mMgr.clear();
  mUngetToken = END;
}

// デストラクタ
MislibParser::~MislibParser()
{
}

// @brief ゲートを読み込む．
// @param[out] gate_list ゲートのASTを格納するリスト
// @return 読み込みが成功したら true を返す．
bool
MislibParser::parse(vector<const MislibGate*>& gate_list)
{
  for ( ; ; ) {
    FileRegion loc;
    MislibToken tok = scan(loc);
    if ( tok == END ) {
      break;
    }

    if ( tok != GATE ) {
      // シンタックスエラー
      return false;
    }

    FileRegion loc0 = loc;
    // 次は STR
    tok = scan(loc);
    if ( tok != STR ) {
      // シンタックスエラー
      return false;
    }
    MislibStr* name = new_str(loc);

    // 次は NUM
    tok = scan(loc);
    if ( tok != NUM ) {
      // シンタックスエラー
      return false;
    }
    MislibNum* area = new_num(loc);

    // 次は STR
    tok = scan(loc);
    if ( tok != STR ) {
      // シンタックスエラー
      return false;
    }
    MislibStr* opin = new_str(loc);

    // 次は EQ
    tok = scan(loc);
    if ( tok != EQ ) {
      // シンタックスエラー
      return false;
    }

    // 次は式
    MislibExpr* expr = read_expr(SEMI);
    if ( expr == nullptr ) {
      // エラー
      return false;
    }

    // 次は SEMI
    tok = scan(loc);
    if ( tok != SEMI ) {
      // シンタックスエラー
      return false;
    }

    FileRegion loc1 = loc;

    // 次はピンリスト
    bool error = false;
    const MislibPin* ipin_top = read_pin_list(error);
    if ( error ) {
      // エラー
      return false;
    }
    // 末尾のノードを位置を loc1 に設定する．
    for ( auto pin = ipin_top; pin != nullptr; pin = pin->next() ) {
      loc1 = pin->loc();
    }

    MislibGate* gate = mMgr.new_gate(FileRegion(loc0, loc1), name, area,
				     opin, expr, ipin_top);
    gate_list.push_back(gate);
  }
  return check_gate_list(gate_list);
}

// @brief 読み込んだゲートリストが正しいかチェックする．
bool
MislibParser::check_gate_list(const vector<const MislibGate*>& gate_list)
{
  int prev_errnum = MsgMgr::error_num();

  // 重複したセル名がないかチェック
  // また，セル内のピン名が重複していないか，出力ピンの論理式に現れるピン名
  // と入力ピンに齟齬がないかもチェックする．
  HashMap<ShString, const MislibGate*> cell_map;
  for ( auto gate: gate_list ) {
    ShString name = gate->name()->str();
    const MislibGate* dummy_node;
    if ( cell_map.find(name, dummy_node) ) {
      ostringstream buf;
      buf << "Clib name, " << name << " is defined more than once. "
	  << "Previous definition is " << dummy_node->name()->loc() << ".";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      gate->name()->loc(),
		      MsgType::Error,
		      "MISLIB_PARSER",
		      buf.str());
      // このセルについては以降のチェックをスキップする．
      continue;
    }
    // 情報を登録する．
    cell_map.add(name, gate);

    // 入力ピン名のチェック
    HashMap<ShString, const MislibPin*> ipin_map;
    for ( auto ipin = gate->ipin_top(); ipin != nullptr; ipin = ipin->next() ) {
      ShString name = ipin->name()->str();
      const MislibPin* dummy_node;
      if ( ipin_map.find(name, dummy_node) ) {
	ostringstream buf;
	buf << "Pin name, " << name << " is defined more than once. "
	    << "Previous definition is "
	    << dummy_node->name()->loc() << ".";
	MsgMgr::put_msg(__FILE__, __LINE__,
			ipin->name()->loc(),
			MsgType::Error,
			"MISLIB_PARSER",
			buf.str());
      }
      else {
	ipin_map.add(name, ipin);
      }
    }
    // 論理式に現れる名前の集合を求める．
    HashSet<ShString> ipin_set;
    get_ipin_names(gate->opin_expr(), ipin_set);
    for ( HashMapIterator<ShString, const MislibPin*> p = ipin_map.begin();
	  p != ipin_map.end(); ++ p ) {
      ShString name = p.key();
      if ( !ipin_set.check(name) ) {
	// ピン定義に現れる名前が論理式中に現れない．
	// エラーではないが，このピンのタイミング情報は意味をもたない．
	const MislibPin* node;
	ipin_map.find(name, node);
	ostringstream buf;
	buf << "Input pin, " << name
	    << " does not appear in the logic expression. "
	    << "Timing information will be ignored.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			node->loc(),
			MsgType::Warning,
			"MISLIB_PARSER",
			buf.str());
      }
    }
    for ( auto name: ipin_set ) {
      const MislibPin* dummy;
      if ( !ipin_map.find(name, dummy) ) {
	// 論理式中に現れる名前の入力ピンが存在しない．
	// これはエラー
	ostringstream buf;
	buf << name << " appears in the logic expression, "
	    << "but is not defined in PIN statement.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			gate->opin_expr()->loc(),
			MsgType::Error,
			"MISLIB_PARSER",
			buf.str());
      }
    }
  }

  if ( MsgMgr::error_num() > prev_errnum ) {
    // 異常終了
    return false;
  }
  return true;
}

// @brief 式を読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibExpr*
MislibParser::read_expr(MislibToken end_token)
{
  MislibExpr* expr1 = read_product();
  if ( expr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    MislibToken tok = peek();
    if ( tok == end_token ) {
      return expr1;
    }
    if ( tok != PLUS && tok != HAT ) {
      // シンタックスエラー
      cout << "Error in read_expr(): PLUS or HAT is expected" << endl;
      return nullptr;
    }
    skip_token();

    MislibExpr* expr2 = read_product();
    if ( expr2 == nullptr ) {
      return nullptr;
    }
    if ( tok == PLUS ) {
      expr1 = mMgr.new_or(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
    }
    else {
      expr1 = mMgr.new_xor(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
    }
  }
}

// @brief 積項を読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibExpr*
MislibParser::read_product()
{
  MislibExpr* expr1 = read_literal();
  if ( expr1 == nullptr ) {
    return nullptr;
  }
  while ( peek() == STAR ) {
    skip_token();

    MislibExpr* expr2 = read_literal();
    if ( expr2 == nullptr ) {
      return nullptr;
    }
    expr1 = mMgr.new_and(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
  }
  return expr1;
}

// @brief リテラルを読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibExpr*
MislibParser::read_literal()
{
  FileRegion loc;
  MislibToken tok = scan(loc);
  switch ( tok ) {
  case STR:
    return mMgr.new_varname(loc, ShString(mScanner.cur_string()));

  case CONST0:
    return mMgr.new_const0(loc);

  case CONST1:
    return mMgr.new_const1(loc);

  case LP:
    {
      MislibExpr* expr = read_expr(RP);
      FileRegion dummy_loc;
      tok = scan(dummy_loc);
      ASSERT_COND( tok == RP );
      return expr;
    }

  case NOT:
    {
      MislibExpr* expr = read_literal();
      return mMgr.new_not(FileRegion(loc, expr->loc()), expr);
    }

  default:
    break;
  }
  // シンタックスエラー
  cout << "Error in read_literal(): STR/CONST0/CONST1/LP/NOT is expected" << endl;
  return nullptr;
}

// @brief ピンリスト記述を読み込む．
// @return ピンリストを表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
// ピン名の代わりに * の場合があるので注意
MislibPin*
MislibParser::read_pin_list(bool& error)
{
  MislibPin* top_node = nullptr;
  MislibPin* prev_node = nullptr;
  for ( ; ; ) {
    MislibPin* node;
    FileRegion loc;

    // 最初は PIN
    MislibToken tok = peek();
    if ( tok != PIN ) {
      // 終わる．
      break;
    }
    // peek したトークンを読み込む．
    scan(loc);

    // 次は STR か STAR
    FileRegion loc0 = loc;
    tok = scan(loc);
    MislibStr* name = nullptr;
    if ( tok == STR ) {
      name = new_str(loc);
    }
    else if ( tok == STAR ) {
      // name は nullptr のまま
    }
    else {
      // シンタックスエラー
      error = true;
      return nullptr;
    }

    // 次は NONINV/INV/UNKNOWN のいずれか
    tok = scan(loc);
    MislibPhase* phase = nullptr;
    switch ( tok ) {
    case NONINV:  phase = mMgr.new_noninv(loc); break;
    case INV:     phase = mMgr.new_inv(loc); break;
    case UNKNOWN: phase = mMgr.new_unknown(loc); break;
    default: error = true; return nullptr;
    }

    // あとは 6 個の NUM
    MislibNum* val[6];
    for ( int i = 0; i < 6; ++ i ) {
      tok = scan(loc);
      if ( tok != NUM ) {
	// シンタックスエラー
	error = true;
	return nullptr;
      }
      val[i] = new_num(loc);
    }

    MislibPin* pin = mMgr.new_pin(FileRegion(loc0, loc), name, phase,
				  val[0], val[1], val[2],
				  val[3], val[4], val[5]);
    if ( prev_node != nullptr ) {
      prev_node->set_next(pin);
    }
    else {
      top_node = pin;
    }
    prev_node = pin;
  }

  // 名前が nullptr (STAR) のピンがある場合はそれが唯一の要素である場合に限る．
  bool has_star = false;
  for ( const MislibPin* pin = top_node; pin != nullptr; pin = pin->next() ) {
    if ( pin->name() == nullptr ) {
      has_star = true;
    }
  }
  if ( has_star && top_node->next() != nullptr ) {
    // シンタックスエラー
    error = true;
  }

  return top_node;
}

// @brief 次のトークンを盗み見る．
MislibToken
MislibParser::peek()
{
  if ( mUngetToken == END ) {
    mUngetToken = mScanner.read_token(mUngetLoc);
  }
  if ( debug_read_token ) {
    cout << "MislibParser::peek(): "
	 << mUngetToken << endl;
  }
  return mUngetToken;
}

// @brief peek() で読んだトークンを捨てる．
void
MislibParser::skip_token()
{
  if ( debug_read_token ) {
    cout << "MislibParser::skip_token(): "
	 << mUngetToken << " is discarded" << endl;
  }
  mUngetToken = END;
}

// @brief 字句解析を行う．
// @param[out] lval トークンの値を格納する変数
// @return トークンの型を返す．
//
// lval に値がセットされない場合もある．
MislibToken
MislibParser::scan(FileRegion& lloc)
{
  MislibToken tok = mUngetToken;
  lloc = mUngetLoc;
  mUngetToken = END;
  if ( tok == END ) {
    tok = mScanner.read_token(lloc);
  }

  if ( debug_read_token ) {
    cout << "MislibParser::scan(): ";
    switch ( tok ) {
    case STR:
      cout << "STR(" << mScanner.cur_string() << ")" << endl;
      break;

    case NUM:
      cout << "NUM(" << mScanner.cur_num() << ")" << endl;
      break;

    case NONINV:
      cout << "NONINV" << endl;
      break;

    case INV:
      cout << "INV" << endl;
      break;

    case UNKNOWN:
      cout << "UNKNOWN" << endl;
      break;

    case CONST0:
      cout << "CONST0" << endl;
      break;

    case CONST1:
      cout << "CONST1" << endl;
      break;

    case LP:
      cout << "LP" << endl;
      break;

    case RP:
      cout << "RP" << endl;
      break;

    case SEMI:
      cout << "SEMI" << endl;
      break;

    case EQ:
      cout << "EQ" << endl;
      break;

    case GATE:
      cout << "GATE" << endl;
      break;

    case PIN:
      cout << "PIN" << endl;
      break;

    case ERROR:
      cout << "ERROR" << endl;
      break;

    case PLUS:
      cout << "PLUS" << endl;
      break;

    case HAT:
      cout << "HAT" << endl;
      break;

    case STAR:
      cout << "STAR" << endl;
      break;

    case NOT:
      cout << "NOT" << endl;
      break;

    case END:
      cout << "END" << endl;
      break;

    default:
      cout << tok << endl;
      break;
    }
  }
  return tok;
}

// @brief 直前のトークンが文字列の場合に文字列ノードを返す．
MislibStr*
MislibParser::new_str(const FileRegion& loc)
{
  return mMgr.new_str(loc, ShString(mScanner.cur_string()));
}

// @brief 直前のトークンが数字の場合に数字ノードを返す．
MislibNum*
MislibParser::new_num(const FileRegion& loc)
{
  return mMgr.new_num(loc, mScanner.cur_num());
}

// @brief エラーメッセージを出力する．
void
MislibParser::error(const FileRegion& loc,
		    const char* msg)
{
  string buff;
  const char* msg2;
  // 好みの問題だけど "parse error" よりは "syntax error" の方が好き．
  if ( !strncmp(msg, "parse error", 11) ) {
    buff ="syntax error";
    buff += (msg + 11);
    msg2 = buff.c_str();
  }
  else {
    msg2 = msg;
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "MISLIB_PARSER",
		  msg2);
}

END_NAMESPACE_YM_MISLIB
