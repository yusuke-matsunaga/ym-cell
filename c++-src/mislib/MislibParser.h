#ifndef MISLIBPARSER_H
#define MISLIBPARSER_H

/// @file MislibParser.h
/// @brief MislibParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"

#include "MislibMgr.h"
#include "MislibScanner.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibParser MislibParser.h "MislibParser.h"
/// @brief mislib(genlib)のパーサークラス
//////////////////////////////////////////////////////////////////////
class MislibParser
{
public:

  /// @brief コンストラクタ
  /// @param[in] ido 入力データオブジェクト
  /// @param[in] mgr MislibNode を管理するオブジェクト
  MislibParser(IDO& ido,
	       MislibMgr& mgr);

  /// @brief デストラクタ
  ~MislibParser();


public:
  //////////////////////////////////////////////////////////////////////
  // メインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[out] gate_list ゲートのASTを格納するリスト
  /// @return 読み込みが成功したら true を返す．
  bool
  parse(vector<const MislibGate*>& gate_list);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだゲートリストが正しいかチェックする．
  bool
  check_gate_list(const vector<const MislibGate*>& gate_list);

  /// @brief 式を読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibExpr*
  read_expr(MislibToken end_token);

  /// @brief 積項を読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibExpr*
  read_product();

  /// @brief リテラルを読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibExpr*
  read_literal();

  /// @brief ピンリスト記述を読み込む．
  /// @param[out] pin_list ピンリストを表す AST のノードを格納するリスト
  /// @return 成功したら true を返す．
  ///
  /// ピン名の代わりに * の場合があるので注意
  MislibPin*
  read_pin_list(bool& error);


private:
  //////////////////////////////////////////////////////////////////////
  // 低レベル関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 次のトークンを盗み見る．
  MislibToken
  peek();

  /// @brief peek() で読んだトークンを捨てる．
  void
  skip_token();

  /// @brief 字句解析を行う．
  /// @param[out] lloc 場所を格納する変数
  /// @return トークンの型を返す．
  ///
  /// lval に値がセットされない場合もある．
  MislibToken
  scan(FileRegion& lloc);

  /// @brief 直前のトークンが文字列の場合に文字列ノードを返す．
  MislibStr*
  new_str(const FileRegion& loc);

  /// @brief 直前のトークンが数字の場合に数字ノードを返す．
  MislibNum*
  new_num(const FileRegion& loc);

  /// @brief エラーメッセージを出力する．
  void
  error(const FileRegion& loc,
	const char* msg);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // MislibNode を管理するオブジェクト
  MislibMgr& mMgr;

  // 字句解析器
  MislibScanner mScanner;

  // 戻したトークン
  MislibToken mUngetToken;

  // 戻したトークンの位置
  FileRegion mUngetLoc;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBPARSER_H
