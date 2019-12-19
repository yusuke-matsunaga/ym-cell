#ifndef MISLIBPARSER_H
#define MISLIBPARSER_H

/// @file MislibParser.h
/// @brief MislibParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"
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
  MislibParser();

  /// @brief デストラクタ
  ~MislibParser();


public:
  //////////////////////////////////////////////////////////////////////
  // メインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[in] filename ファイル名
  /// @param[out] gate_list ゲートのASTを格納するリスト
  /// @return 読み込みが成功したら true を返す．
  bool
  parse(const string& filename,
	vector<const MislibGate*>& gate_list);


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
  /// @return ピンの先頭を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  /// ピン名の代わりに * の場合があるので注意
  MislibPin*
  read_pin_list();


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

  /// @brief GATE ノードを生成する．(通常版)
  MislibGate*
  new_gate(const FileRegion& loc,
	   const MislibStr* name,
	   const MislibNum* area,
	   const MislibStr* oname,
	   const MislibExpr* expr,
	   const MislibPin* ipin_top);

  /// @brief PIN ノードを生成する．
  MislibPin*
  new_pin(const FileRegion& loc,
	  const MislibStr* name,
	  const MislibPhase* phase,
	  const MislibNum* input_load,
	  const MislibNum* max_load,
	  const MislibNum* rise_block_delay,
	  const MislibNum* rise_fanout_delay,
	  const MislibNum* fall_block_delay,
	  const MislibNum* fall_fanout_delay);

  /// @brief NOT ノードを生成する．
  MislibExpr*
  new_not(const FileRegion& loc,
	  const MislibExpr* child1);

  /// @brief AND ノードを生成する．
  MislibExpr*
  new_and(const FileRegion& loc,
	  const MislibExpr* child1,
	  const MislibExpr* child2);

  /// @brief OR ノードを生成する．
  MislibExpr*
  new_or(const FileRegion& loc,
	 const MislibExpr* child1,
	 const MislibExpr* child2);

  /// @brief XOR ノードを生成する．
  MislibExpr*
  new_xor(const FileRegion& loc,
	  const MislibExpr* child1,
	  const MislibExpr* child2);

  /// @brief 定数0ノードを生成する．
  MislibExpr*
  new_const0(const FileRegion& loc);

  /// @brief 定数1ノードを生成する．
  MislibExpr*
  new_const1(const FileRegion& loc);

  /// @brief 変数ノードを生成する．
  MislibExpr*
  new_varname(const FileRegion& loc,
	      ShString str);

  /// @brief NONINV ノードを生成する．
  MislibPhase*
  new_noninv(const FileRegion& loc);

  /// @brief INV ノードを生成する．
  MislibPhase*
  new_inv(const FileRegion& loc);

  /// @brief UNKNOWN ノードを生成する．
  MislibPhase*
  new_unknown(const FileRegion& loc);

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

  // 字句解析器
  unique_ptr<MislibScanner> mScanner;

  // 戻したトークン
  MislibToken mUngetToken;

  // 戻したトークンの位置
  FileRegion mUngetLoc;

  // 生成したノードのリスト
  vector<unique_ptr<MislibNode>> mNodeList;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBPARSER_H
