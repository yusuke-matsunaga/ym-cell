#ifndef MISLIBPARSERIMPL_H
#define MISLIBPARSERIMPL_H

/// @file MislibParserImpl.h
/// @brief MislibParserImpl のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"

#include "MislibMgrImpl.h"
#include "MislibNodeImpl.h"
#include "MislibScanner.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibParserImpl MislibParserImpl.h "MislibParserImpl.h"
/// @brief MislibParser の実装クラス
//////////////////////////////////////////////////////////////////////
class MislibParserImpl
{
public:

  /// @brief コンストラクタ
  MislibParserImpl();

  /// @brief デストラクタ
  ~MislibParserImpl();


public:
  //////////////////////////////////////////////////////////////////////
  // メインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mislib ファイルを読み込む．
  /// @param[in] filename ファイル名
  /// @param[in] mgr MislibNode を管理するオブジェクト
  /// @param[out] gate_list ゲートのASTを格納するリスト
  /// @retval true 読み込みが成功した．
  /// @retval false読み込みが失敗した．
  bool
  read_file(const string& filename,
	    MislibMgrImpl* mgr,
	    vector<const MislibNode*>& gate_list);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[in] ido 入力データオブジェクト
  /// @param[out] gate_list ゲートのASTを格納するリスト
  /// @return 読み込みが成功したら true を返す．
  bool
  parse(IDO& ido,
	vector<const MislibNode*>& gate_list);

  /// @brief 式を読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibNode*
  read_expr(MislibToken end_token);

  /// @brief 積項を読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibNode*
  read_product();

  /// @brief リテラルを読み込む．
  /// @return 式を表す AST のノードを返す．
  ///
  /// エラーが起きたら nullptr を返す．
  MislibNode*
  read_literal();

  /// @brief ピンリスト記述を読み込む．
  /// @param[out] pin_list ピンリストを表す AST のノードを格納するリスト
  /// @return 成功したら true を返す．
  ///
  /// ピン名の代わりに * の場合があるので注意
  MislibNode*
  read_pin_list(bool& error);


private:
  //////////////////////////////////////////////////////////////////////
  // mislib_grammer.yy で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 次のトークンを盗み見る．
  MislibToken
  peek();

  /// @brief peek() で読んだトークンを捨てる．
  void
  skip_token();

  /// @brief 字句解析を行う．
  /// @param[out] lval トークンの値を格納する変数
  /// @param[out] lloc 場所を格納する変数
  /// @return トークンの型を返す．
  ///
  /// lval に値がセットされない場合もある．
  MislibToken
  scan(MislibNodeImpl*& lval,
       FileRegion& lloc);

  /// @brief エラーメッセージを出力する．
  void
  error(const FileRegion& loc,
	const char* msg);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  MislibScanner* mScanner;

  // 戻したトークン
  MislibToken mUngetToken;

  // 戻したトークンの位置
  FileRegion mUngetLoc;

  // MislibNode を管理するオブジェクト
  MislibMgrImpl* mMislibMgr;

};

END_NAMESPACE_YM_MISLIB

#endif // MISLIBPARSERIMPL_H
