﻿
/// @file MislibParserImpl.cc
/// @brief MislibParserImpl の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibParserImpl.h"
#include "MislibMgrImpl.h"
#include "ym/HashSet.h"
#include "ym/HashMap.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_MISLIB

BEGIN_NONAMESPACE

// MislibScanner::read_token() をデバッグする時に true にする．
bool debug_read_token = false;

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス MislibParserImpl
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibParserImpl::MislibParserImpl()
{
  mScanner = nullptr;
  mUngetToken = END;
}

// デストラクタ
MislibParserImpl::~MislibParserImpl()
{
}


BEGIN_NONAMESPACE

// 論理式中に現れる名前を ipin_set に積む．
void
get_ipin_names(const MislibNode* expr_node,
	       HashSet<ShString>& ipin_set)
{
  ShString name;

  switch ( expr_node->type() ) {
  case MislibNode::kConst0:
  case MislibNode::kConst1:
    // 定数は無視
    return;

  case MislibNode::kStr:
    if ( !ipin_set.check(expr_node->str()) ) {
      ipin_set.add(expr_node->str());
    }
    break;

  case MislibNode::kNot:
    get_ipin_names(expr_node->child1(), ipin_set);
    break;

  case MislibNode::kAnd:
  case MislibNode::kOr:
  case MislibNode::kXor:
    get_ipin_names(expr_node->child1(), ipin_set);
    get_ipin_names(expr_node->child2(), ipin_set);
    break;

  default:
    ASSERT_NOT_REACHED;
  }
}

END_NONAMESPACE

// @brief mislib ファイルを読み込んでライブラリを生成する．
// @param[in] filename ファイル名
// @param[in] mgr MislibNode を管理するオブジェクト
// @return パース木の根のノードを返す．
// @note 読み込みが失敗したら false を返す．
bool
MislibParserImpl::read_file(const string& filename,
			    MislibMgrImpl* mgr,
			    vector<const MislibNode*>& gate_list)
{
  FileIDO ido;
  if ( !ido.open(filename) ) {
    // エラー
    ostringstream buf;
    buf << filename << " : No such file.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    kMsgFailure,
		    "MISLIB_PARSER",
		    buf.str());
    return false;
  }

  // 初期化
  mMislibMgr = mgr;
  mMislibMgr->clear();

  int prev_errnum = MsgMgr::error_num();

  // パース木を作る．
  bool stat = parse(ido, gate_list);

  if ( MsgMgr::error_num() > prev_errnum ) {
    // 異常終了
    return false;
  }

  // 重複したセル名がないかチェック
  // また，セル内のピン名が重複していないか，出力ピンの論理式に現れるピン名
  // と入力ピンに齟齬がないかもチェックする．
  HashMap<ShString, const MislibNode*> cell_map;
  for ( auto gate: gate_list ) {
    ASSERT_COND( gate->type() == MislibNode::kGate );
    ShString name = gate->name()->str();
    const MislibNode* dummy_node;
    if ( cell_map.find(name, dummy_node) ) {
      ostringstream buf;
      buf << "Clib name, " << name << " is defined more than once. "
	  << "Previous definition is " << dummy_node->name()->loc() << ".";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      gate->name()->loc(),
		      kMsgError,
		      "MISLIB_PARSER",
		      buf.str());
      // このセルについては以降のチェックをスキップする．
      continue;
    }
    // 情報を登録する．
    cell_map.add(name, gate);

    // 入力ピン名のチェック
    HashMap<ShString, const MislibNode*> ipin_map;
    for ( auto ipin = gate->ipin_top(); ipin != nullptr; ipin = ipin->next() ) {
      ASSERT_COND( ipin->type() == MislibNode::kPin );
      ShString name = ipin->name()->str();
      const MislibNode* dummy_node;
      if ( ipin_map.find(name, dummy_node) ) {
	ostringstream buf;
	buf << "Pin name, " << name << " is defined more than once. "
	    << "Previous definition is "
	    << dummy_node->name()->loc() << ".";
	MsgMgr::put_msg(__FILE__, __LINE__,
			ipin->name()->loc(),
			kMsgError,
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
    for ( HashMapIterator<ShString, const MislibNode*> p = ipin_map.begin();
	  p != ipin_map.end(); ++ p ) {
      ShString name = p.key();
      if ( !ipin_set.check(name) ) {
	// ピン定義に現れる名前が論理式中に現れない．
	// エラーではないが，このピンのタイミング情報は意味をもたない．
	const MislibNode* node;
	ipin_map.find(name, node);
	ostringstream buf;
	buf << "Input pin, " << name
	    << " does not appear in the logic expression. "
	    << "Timing information will be ignored.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			node->loc(),
			kMsgWarning,
			"MISLIB_PARSER",
			buf.str());
      }
    }
    for ( HashSetIterator<ShString> p = ipin_set.begin();
	  p != ipin_set.end(); ++ p ) {
      ShString name = p.key();
      const MislibNode* dummy;
      if ( !ipin_map.find(name, dummy) ) {
	// 論理式中に現れる名前の入力ピンが存在しない．
	// これはエラー
	ostringstream buf;
	buf << name << " appears in the logic expression, "
	    << "but is not defined in PIN statement.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			gate->opin_expr()->loc(),
			kMsgError,
			"MISLIB_PARSER",
			buf.str());
      }
    }
  }

  if ( MsgMgr::error_num() > prev_errnum ) {
    // 異常終了
    return false;
  }
  // 読み込みまではうまくいった．
  return true;
}

// @brief ゲートを読み込む．
// @param[in] ido 入力データオブジェクト
// @param[out] gate_list ゲートのASTを格納するリスト
// @return 読み込みが成功したら true を返す．
bool
MislibParserImpl::parse(IDO& ido,
			vector<const MislibNode*>& gate_list)
{
  MislibScanner scanner(ido);
  mScanner = &scanner;
  for ( ; ; ) {
    MislibNodeImpl* node;
    FileRegion loc;

    MislibToken tok = scan(node, loc);
    if ( tok == END ) {
      return true;
    }

    if ( tok != GATE ) {
      // シンタックスエラー
      return false;
    }

    FileRegion loc0 = loc;
    // 次は STR
    tok = scan(node, loc);
    if ( tok != STR ) {
      // シンタックスエラー
      return false;
    }
    MislibNode* name = node;

    // 次は NUM
    tok = scan(node, loc);
    if ( tok != NUM ) {
      // シンタックスエラー
      return false;
    }
    MislibNode* area = node;

    // 次は STR
    tok = scan(node, loc);
    if ( tok != STR ) {
      // シンタックスエラー
      return false;
    }
    MislibNode* opin = node;

    // 次は EQ
    tok = scan(node, loc);
    if ( tok != EQ ) {
      // シンタックスエラー
      return false;
    }

    // 次は式
    MislibNode* expr = read_expr(SEMI);
    if ( expr == nullptr ) {
      // エラー
      return false;
    }

    // 次は SEMI
    tok = scan(node, loc);
    if ( tok != SEMI ) {
      // シンタックスエラー
      return false;
    }

    FileRegion loc1 = loc;

    // 次はピンリスト
    bool error = false;
    const MislibNode* ipin_top = read_pin_list(error);
    if ( error ) {
      // エラー
      return false;
    }
    // 末尾のノードを位置を loc1 に設定する．
    for ( auto pin = ipin_top; pin != nullptr; pin = pin->next() ) {
      loc1 = pin->loc();
    }

    MislibNode* gate = mMislibMgr->new_gate(FileRegion(loc0, loc1), name, area,
					    opin, expr, ipin_top);
    gate_list.push_back(gate);
  }
  mScanner = nullptr;
}

// @brief 式を読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibNode*
MislibParserImpl::read_expr(MislibToken end_token)
{
  MislibNode* expr1 = read_product();
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

    MislibNode* expr2 = read_product();
    if ( expr2 == nullptr ) {
      return nullptr;
    }
    if ( tok == PLUS ) {
      expr1 = mMislibMgr->new_or(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
    }
    else {
      expr1 = mMislibMgr->new_xor(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
    }
  }
}

// @brief 積項を読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibNode*
MislibParserImpl::read_product()
{
  MislibNode* expr1 = read_literal();
  if ( expr1 == nullptr ) {
    return nullptr;
  }
  while ( peek() == STAR ) {
    skip_token();

    MislibNode* expr2 = read_literal();
    if ( expr2 == nullptr ) {
      return nullptr;
    }
    expr1 = mMislibMgr->new_and(FileRegion(expr1->loc(), expr2->loc()), expr1, expr2);
  }
  return expr1;
}

// @brief リテラルを読み込む．
// @return 式を表す AST のノードを返す．
//
// エラーが起きたら nullptr を返す．
MislibNode*
MislibParserImpl::read_literal()
{
  MislibNodeImpl* node;
  FileRegion loc;
  MislibToken tok = scan(node, loc);
  switch ( tok ) {
  case STR:
  case CONST0:
  case CONST1:
    return node;

  case LP:
    {
      MislibNode* expr = read_expr(RP);
      MislibNodeImpl* dummy_node;
      FileRegion dummy_loc;
      tok = scan(dummy_node, dummy_loc);
      ASSERT_COND( tok == RP );
      return expr;
    }

  case NOT:
    {
      MislibNode* expr = read_literal();
      return mMislibMgr->new_not(FileRegion(loc, expr->loc()), expr);
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
MislibNode*
MislibParserImpl::read_pin_list(bool& error)
{
  MislibNodeImpl* top_node = nullptr;
  MislibNodeImpl* prev_node = nullptr;
  for ( ; ; ) {
    MislibNodeImpl* node;
    FileRegion loc;

    // 最初は PIN
    MislibToken tok = peek();
    if ( tok != PIN ) {
      // 終わる．
      break;
    }

    scan(node, loc);

    // 次は STR か STAR
    FileRegion loc0 = loc;
    tok = scan(node, loc);
    MislibNode* name = nullptr;
    if ( tok == STR ) {
      name = node;
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
    tok = scan(node, loc);
    if ( tok != NONINV && tok != INV && tok != UNKNOWN ) {
      // シンタックスエラー
      error = true;
      return nullptr;
    }
    MislibNode* phase = node;

    // あとは 6 個の NUM
    MislibNode* val[6];
    for (int i = 0; i < 6; ++ i) {
      tok = scan(node, loc);
      if ( tok != NUM ) {
	// シンタックスエラー
	error = true;
	return nullptr;
      }
      val[i] = node;
    }

    MislibNodeImpl* pin = mMislibMgr->new_pin(FileRegion(loc0, loc), name, phase,
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
  for ( const MislibNode* pin = top_node; pin != nullptr; pin = pin->next() ) {
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
MislibParserImpl::peek()
{
  if ( mUngetToken == END ) {
    mUngetToken = mScanner->read_token(mUngetLoc);
  }
  if ( debug_read_token ) {
    cout << "MislibParserImpl::peek(): "
	 << mUngetToken << endl;
  }
  return mUngetToken;
}

// @brief peek() で読んだトークンを捨てる．
void
MislibParserImpl::skip_token()
{
  if ( debug_read_token ) {
    cout << "MislibParserImpl::skip_token(): "
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
MislibParserImpl::scan(MislibNodeImpl*& lval,
		       FileRegion& lloc)
{
  MislibToken tok = mUngetToken;
  lloc = mUngetLoc;
  mUngetToken = END;
  if ( tok == END ) {
    tok = mScanner->read_token(lloc);
  }

  if ( debug_read_token ) {
    cout << "MislibParserImpl::scan(): ";
    switch ( tok ) {
    case STR:
      cout << "STR(" << mScanner->cur_string() << ")" << endl;
      break;

    case NUM:
      cout << "NUM(" << mScanner->cur_num() << ")" << endl;
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

  switch ( tok ) {
  case STR:
    lval =mMislibMgr->new_str(lloc, ShString(mScanner->cur_string()));
    break;

  case NUM:
    lval = mMislibMgr->new_num(lloc, mScanner->cur_num());
    break;

  case NONINV:
    lval = mMislibMgr->new_noninv(lloc);
    break;

  case INV:
    lval = mMislibMgr->new_inv(lloc);
    break;

  case UNKNOWN:
    lval = mMislibMgr->new_unknown(lloc);
    break;

  case CONST0:
    lval = mMislibMgr->new_const0(lloc);
    break;

  case CONST1:
    lval =mMislibMgr->new_const1(lloc);
    break;

  default:
    break;
  }

  return tok;
}

// @brief エラーメッセージを出力する．
void
MislibParserImpl::error(const FileRegion& loc,
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
		  kMsgError,
		  "MISLIB_PARSER",
		  msg2);
}

END_NAMESPACE_YM_MISLIB
