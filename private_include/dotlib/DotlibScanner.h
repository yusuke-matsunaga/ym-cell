#ifndef DOTLIBSCANNER_H
#define DOTLIBSCANNER_H

/// @file DotlibScanner.h
/// @brief DotlibScanner のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "ym/InputFileObj.h"
#include "ym/FileRegion.h"
#include "ym/StrBuff.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibScanner DotlibScanner.h "DotlibScanner.h"
/// @brief dotlib フォーマットの字句解析器
//////////////////////////////////////////////////////////////////////
class DotlibScanner
{
public:

  /// @brief コンストラクタ
  DotlibScanner(InputFileObj& in) ///< [in] 入力ファイルオブジェクト
    : mIn{in}
  {
  }

  /// @brief デストラクタ
  ~DotlibScanner() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief トークンを一つ読み込む．
  /// @return トークンの型を返す．
  TokenType
  read_token(FileRegion& loc,           ///< [out] ファイル上の位置情報を格納する変数
	     bool symbol_mode = false); ///< [in] 数字も文字とみなすモード

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string() const
  {
    return mCurString.c_str();
  }

  /// @brief 直前の read_token() に対応する整数値を返す．
  ///
  /// 型が INT_NUM でなかったときの値は不定
  int
  cur_int() const
  {
    return strtol(cur_string(), nullptr, 10);
  }

  /// @brief 直前の read_token() に対応する実数値を返す．
  ///
  /// 型が FLOAT_NUM/INT_NUM でなかったときの値は不定
  double
  cur_float() const
  {
    return strtod(cur_string(), nullptr);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief read_token() の下請け関数
  /// @return トークンの型を返す．
  TokenType
  scan();

  /// @brief c が文字の時に true を返す．
  ///
  /// mSymbolMode が true なら数字も文字とみなす．
  bool
  is_symbol(int c);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ファイルオブジェクト
  InputFileObj& mIn;

  // シンボルモード
  bool mSymbolMode;

  // read_token で処理中のトークンの先頭の位置
  FileLoc mFirstLoc;

  // read_token の結果の文字列を格納する
  StrBuff mCurString;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBSCANNER_H
