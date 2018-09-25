﻿#ifndef STRFLOATHANDLER_H
#define STRFLOATHANDLER_H

/// @file StrFloatHandler.h
/// @brief StrFloatHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem2Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrFloatHandler StrFloatHandler.h "dotlib/StrFloatHandler.h"
/// @brief ( string, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class StrFloatHandler :
  public Elem2Handler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrFloatHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrFloatHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の要素を返す．
  const AstString*
  value1() const;

  /// @brief 2番目の要素を返す．
  const AstFloat*
  value2() const;


private:
  //////////////////////////////////////////////////////////////////////
  // Elem2Handler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief 1つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  bool
  read_header_value1(TokenType value_type,
		     const FileRegion& value_loc) override;

  /// @brief 2つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  bool
  read_header_value2(TokenType value_type,
		     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の要素
  const AstString* mValue1;

  // 2番目の要素
  const AstFloat* mValue2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の要素を返す．
inline
const AstString*
StrFloatHandler::value1() const
{
  return mValue1;
}

// @brief 2番目の要素を返す．
inline
const AstFloat*
StrFloatHandler::value2() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // STRFLOATHANDLER_H
