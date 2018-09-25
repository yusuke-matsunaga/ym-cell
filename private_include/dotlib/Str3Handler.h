#ifndef STR3HANDLER_H
#define STR3HANDLER_H

/// @file Str3Handler.h
/// @brief Str3Handler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem3Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str3Str3Handler Str3Handler.h "dotlib/Str3Handler.h"
/// @brief ( string, string, string ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str3Handler :
  public Elem3Handler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Str3Handler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Str3Handler();


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

  /// @brief 3番目の値を返す．
  const AstString*
  value3() const;


private:
  //////////////////////////////////////////////////////////////////////
  // Elem3Handler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  virtual
  void
  initialize() override;

  /// @brief 1つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  virtual
  bool
  read_header_value1(TokenType value_type,
		     const FileRegion& value_loc) override;

  /// @brief 2つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  virtual
  bool
  read_header_value2(TokenType value_type,
		     const FileRegion& value_loc) override;

  /// @brief 3つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  virtual
  bool
  read_header_value3(TokenType value_type,
		     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の値
  const AstString* mValue1;

  // 2番目の値
  const AstString* mValue2;

  // 3番目の値
  const AstString* mValue3;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を返す．
inline
const AstString*
Str3Handler::value1() const
{
  return mValue1;
}

// @brief 2番目の値を返す．
inline
const AstString*
Str3Handler::value2() const
{
  return mValue2;
}

// @brief 3番目の値を返す．
inline
const AstString*
Str3Handler::value3() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // STR3HANDLER_H
