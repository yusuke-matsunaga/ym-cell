#ifndef STR1HANDLER_H
#define STR1HANDLER_H

/// @file Str1Handler.h
/// @brief Str1Handler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem1Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str1Str1Handler Str1Handler.h "dotlib/Str1Handler.h"
/// @brief ( string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str1Handler :
  public Elem1Handler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Str1Handler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Str1Handler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を返す．
  const AstString*
  value() const;


private:
  //////////////////////////////////////////////////////////////////////
  // Elem1Handler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  bool
  read_header_value1(TokenType value_type,
		     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstString* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を返す．
inline
const AstString*
Str1Handler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // STR1HANDLER_H
