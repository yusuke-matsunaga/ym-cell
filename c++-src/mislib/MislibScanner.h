#ifndef MISLIBSCANNER_H
#define MISLIBSCANNER_H

/// @file MislexScanner.h
/// @brief MislexScanner のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2013-2014 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "MislibToken.h"

#include "ym/InputFileObj.h"
#include "ym/StrBuff.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibScanner MislibScanner.h "MislibScanner.h"
/// @brief Mislib 用の LEX クラス
//////////////////////////////////////////////////////////////////////
class MislibScanner
{
public:

  /// @brief コンストラクタ
  /// @param[in] in 入力ファイルオブジェクト
  MislibScanner(InputFileObj& in);

  /// @brief デストラクタ
  ~MislibScanner() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief トークンを一つとってくる．
  /// @param[out] loc 対応するファイル上の位置を格納する変数
  MislibToken
  read_token(FileRegion& loc);

  /// @brief 直前の read_token() に対応する文字列を返す．
  const char*
  cur_string() const;

  /// @brief cur_string() を double に変換したものを返す．
  double
  cur_float() const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief read_token の下請け関数
  /// @return トークンを返す．
  MislibToken
  scan();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ファイルオブジェクト
  InputFileObj& mIn;

  // 現在読込中の文字列の先頭の位置
  FileLoc mFirstLoc;

  // 現在読込中の文字列を貯めておくバッファ
  StrBuff mCurString;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// 直前の read_token() に対応する文字列を返す．
inline
const char*
MislibScanner::cur_string() const
{
  return mCurString.c_str();
}

// @brief cur_string() を double に変換したものを返す．
inline
double
MislibScanner::cur_float() const
{
  return strtod(cur_string(), static_cast<char**>(nullptr));
}

END_NAMESPACE_YM_MISLIB

#endif // MISLIBSCANNER_H
