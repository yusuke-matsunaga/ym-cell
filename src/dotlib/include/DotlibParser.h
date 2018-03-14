#ifndef DOTLIBPARSER_H
#define DOTLIBPARSER_H

/// @file DotlibParser.h
/// @brief DotlibParser のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "AttrDic.h"
#include "DotlibScanner.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibParser DotlibParser.h "DotlibParser.h"
/// @brief DotlibParser の実装クラス
//////////////////////////////////////////////////////////////////////
class DotlibParser
{
public:

  /// @brief コンストラクタ
  /// @param[in] ido 入力データオブジェクト
  /// @param[in] mgr AstNode を管理するオブジェクト
  /// @param[in] debug デバッグモード
  /// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
  DotlibParser(IDO& ido,
	       AstMgr& mgr,
	       bool debug,
	       bool allow_no_semi = true);

  /// @brief デストラクタ
  ~DotlibParser();


public:

  /// @brief パーズする
  /// @return 読み込んだ AST を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  const AstLibrary*
  parse();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler から用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  bool
  expect(TokenType type);

  /// @brief 行末まで読み込む．
  bool
  expect_nl();

  /// @brief トークンを一つ読み込む．
  /// @param[out] loc ファイル上の位置情報を格納する変数
  /// @param[in] symbol_mode 数字も文字とみなすモード
  /// @return トークンの型を返す．
  TokenType
  read_token(FileRegion& loc,
	     bool symbol_mode = false);

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string() const;

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int() const;

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float() const;

  /// @brief 直前の read_token() に対応する位置を返す．
  FileRegion
  cur_loc() const;

  /// @brief 文字列を属性値に変換する．
  AttrType
  conv_to_attr(const char* str);

  /// @brief AstMgr を返す．
  AstMgr&
  mgr();

  /// @brief デバッグモードの時 true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 字句解析器
  DotlibScanner mScanner;

  // AstNode を管理するオブジェクト
  AstMgr& mAstMgr;

  // library グループを処理するハンドラ
  DotlibHandler* mLibraryHandler;

  // 直前の位置
  FileRegion mCurLoc;

  // 属性用の辞書
  AttrDic mAttrDic;

  // デバッグモード
  bool mDebug;

  // 行末のセミコロンなしを許すかどうかのフラグ
  bool mAllowNoSemi;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief トークンを一つ読み込む．
// @param[out] loc ファイル上の位置情報を格納する変数
// @param[in] symbol_mode 数字も文字とみなすモード
// @return トークンの型を返す．
inline
TokenType
DotlibParser::read_token(FileRegion& loc,
			 bool symbol_mode)
{
  auto ans = mScanner.read_token(loc, symbol_mode);
  mCurLoc = loc;
  return ans;
}

// @brief 直前の read_token() に対応する文字列を返す．
inline
const char*
DotlibParser::cur_string() const
{
  return mScanner.cur_string();
}

// @brief 直前の read_token() に対応する整数値を返す．
// @note 型が INT_NUM でなかったときの値は不定
inline
int
DotlibParser::cur_int() const
{
  return mScanner.cur_int();
}

// @brief 直前の read_token() に対応する実数値を返す．
// @note 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
inline
double
DotlibParser::cur_float() const
{
  return mScanner.cur_float();
}

// @brief AstMgr を返す．
inline
AstMgr&
DotlibParser::mgr()
{
  return mAstMgr;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPARSER_H
