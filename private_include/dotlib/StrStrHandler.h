﻿#ifndef STRSTRHANDLER_H
#define STRSTRHANDLER_H

/// @file StrStrHandler.h
/// @brief StrStrHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrStrStrStrHandler StrStrHandler.h "dotlib/StrStrHandler.h"
/// @brief ( string, string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrStrHandler :
  public ElemHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrStrHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrStrHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の値を返す．
  const AstString*
  value1() const;

  /// @brief 2番目の値を返す．
  const AstString*
  value2() const;


private:
  //////////////////////////////////////////////////////////////////////
  // ElemHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_value(int count) override;

  /// @brief end_header() 内で呼ばれる終了処理関数
  void
  finalize() override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  const AstString* mValue[2];

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を返す．
inline
const AstString*
StrStrHandler::value1() const
{
  return mValue[0];
}

// @brief 2番目の値を返す．
inline
const AstString*
StrStrHandler::value2() const
{
  return mValue[1];
}

END_NAMESPACE_YM_DOTLIB

#endif // STRSTRHANDLER_H