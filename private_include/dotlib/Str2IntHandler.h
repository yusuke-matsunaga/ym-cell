#ifndef STR2INTHANDLER_H
#define STR2INTHANDLER_H

/// @file Str2IntHandler.h
/// @brief Str2IntHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem3Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str2IntHandler Str2IntHandler.h "dotlib/Str2IntHadler.h"
/// @brief ( string, string, integer ) の形式のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2IntHandler :
  public Elem3Handler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2IntHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Str2IntHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の値を取り出す．
  const AstString*
  value1() const;

  /// @brief 2番目の値を取り出す．
  const AstString*
  value2() const;

  /// @brief 3番目の値を取り出す．
  const AstInt*
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

  // ヘッダの値1
  const AstString* mValue1;

  // ヘッダの値2
  const AstString* mValue2;

  // ヘッダの値3
  const AstInt* mValue3;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を取り出す．
inline
const AstString*
Str2IntHandler::value1() const
{
  return mValue1;
}

// @brief 2番目の値を取り出す．
inline
const AstString*
Str2IntHandler::value2() const
{
  return mValue2;
}

// @brief 3番目の値を取り出す．
inline
const AstInt*
Str2IntHandler::value3() const
{
  return mValue3;
}

END_NAMESPACE_YM_DOTLIB

#endif // STR2INTHANDLER_H
