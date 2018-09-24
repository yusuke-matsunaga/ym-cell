﻿#ifndef INTFLOATHEADERHANDLER_H
#define INTFLOATHEADERHANDLER_H

/// @file IntFloatHeaderHandler.h
/// @brief IntFloatHeaderHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class IntFloatHeaderHandler IntFloatHeaderHandler.h "dotlib/IntFloatHeaderHandler.h"
/// @brief ( integer, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class IntFloatHeaderHandler :
  public HeaderHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  IntFloatHeaderHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~IntFloatHeaderHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の要素を返す．
  const AstInt*
  value1() const;

  /// @brief 2番目の要素を返す．
  const AstFloat*
  value2() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // HeaderHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_header_value(TokenType value_type,
		    const FileRegion& value_loc,
		    int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の要素
  const AstInt* mValue1;

  // 2番目の要素
  const AstFloat* mValue2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の要素を返す．
inline
const AstInt*
IntFloatHeaderHandler::value1() const
{
  return mValue1;
}

// @brief 2番目の要素を返す．
inline
const AstFloat*
IntFloatHeaderHandler::value2() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // INTFLOATHEADERHANDLER_H
