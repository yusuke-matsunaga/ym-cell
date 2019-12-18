﻿#ifndef DOTLIBSCANNER_H
#define DOTLIBSCANNER_H

/// @file DotlibScanner.h
/// @brief DotlibScanner のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/Scanner.h"
#include "ym/FileRegion.h"
#include "ym/StrBuff.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibScanner DotlibScanner.h "DotlibScanner.h"
/// @brief dotlib フォーマットの字句解析器
//////////////////////////////////////////////////////////////////////
class DotlibScanner :
  public Scanner
{
public:

  /// @brief コンストラクタ
  /// @param[in] s 入力ストリーム
  /// @param[in] file_info ファイル情報
  DotlibScanner(istream& s,
		const FileInfo& file_info);

  /// @brief デストラクタ
  ~DotlibScanner();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

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
  /// @note 型が INT_NUM でなかったときの値は不定
  int
  cur_int() const;

  /// @brief 直前の read_token() に対応する実数値を返す．
  /// @note 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float() const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief read_token() の下請け関数
  /// @return トークンの型を返す．
  TokenType
  scan();

  /// @brief c が文字の時に true を返す．
  /// @note mSymbolMode が true なら数字も文字とみなす．
  bool
  is_symbol(int c);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // シンボルモード
  bool mSymbolMode;

  // read_token の結果の文字列を格納する
  StrBuff mCurString;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// 直前の read_token() に対応する文字列を返す．
inline
const char*
DotlibScanner::cur_string() const
{
  return mCurString.c_str();
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBSCANNER_H
