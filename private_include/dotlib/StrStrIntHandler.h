#ifndef STRSTRINTHANDLER_H
#define STRSTRINTHANDLER_H

/// @file StrStrIntHandler.h
/// @brief StrStrIntHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ElemHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrStrIntHandler StrStrIntHandler.h "dotlib/StrStrIntHadler.h"
/// @brief ( string, string, integer ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrStrIntHandler :
  public ElemHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  StrStrIntHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrStrIntHandler();


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

  /// @brief 3番目の値を取り出す．
  const AstInt*
  value3() const;


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

  // ヘッダの値3
  const AstInt* mValue3;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を返す．
inline
const AstString*
StrStrIntHandler::value1() const
{
  return mValue[0];
}

// @brief 2番目の値を返す．
inline
const AstString*
StrStrIntHandler::value2() const
{
  return mValue[1];
}

// @brief 3番目の値を取り出す．
inline
const AstInt*
StrStrIntHandler::value3() const
{
  return mValue3;
}

END_NAMESPACE_YM_DOTLIB

#endif // STRSTRINTHANDLER_H
