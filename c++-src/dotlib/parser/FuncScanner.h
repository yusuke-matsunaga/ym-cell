#ifndef FUNCSCANNER_H
#define FUNCSCANNER_H

/// @file FuncScanner.h
/// @brief FuncScanner のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "ym/StrBuff.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FuncScanner FuncScanner.h "FuncScanner.h"
/// @brief FuncHandler 用の字句解析器
//////////////////////////////////////////////////////////////////////
class FuncScanner
{
public:

  /// @brief コンストラクタ
  /// @param[in] str 文字列
  /// @param[in] str のファイル上の位置
  FuncScanner(const string& str,
	      const FileRegion& loc);

  /// @brief デストラクタ
  ~FuncScanner();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief トークンを読み込む．
  /// @param[out] loc 対応するファイル上の位置情報を格納する変数
  TokenType
  peek_token(FileRegion& loc);

  /// @brief 読み込んだトークンを確定する．
  void
  accept_token();

  /// @brief トークンを読み込み確定する．
  /// @param[out] loc 対応するファイル上の位置情報を格納する変数
  TokenType
  read_token(FileRegion& loc);

  /// @brief 直前の read_token() で読んだトークンの文字列を返す．
  const char*
  cur_string();

  /// @brief 直前の read_token() で読んだトークンの整数値を返す．
  int
  cur_int();


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 一文字読み出す．
  int
  get();

  /// @brief 一文字先読みする．
  int
  peek();

  /// @brief 先読みを確定する．
  void
  accept();

  /// @brief トークンの先頭のファイル位置を設定する．
  void
  set_first_loc();

  /// @brief 現在のファイル位置を返す．
  FileRegion
  cur_loc();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // パーズ中の文字列
  string mSrcString;

  // mString のファイル位置
  FileRegion mSrcLoc;

  // 現在の読み出し位置
  int mCurPos;

  // 現在のトークン文字列
  StrBuff mCurString;

  // 最初のコラム位置
  int mFirstColumn;

  // 現在のトークンの型
  TokenType mCurType;

  // 現在のトークンの位置
  FileRegion mCurLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // FUNCSCANNER_H
