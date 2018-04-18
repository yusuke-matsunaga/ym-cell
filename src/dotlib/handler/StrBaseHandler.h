﻿#ifndef STRBASEHANDLER_H
#define STRBASEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrBaseHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 文字列を取る属性用のハンドラの基底クラス
//////////////////////////////////////////////////////////////////////
class StrBaseHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] sym_mode シンボルモード
  StrBaseHandler(DotlibParser& parser,
		 bool sym_mode);

  /// @brief デストラクタ
  ~StrBaseHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // StrBaseHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 文字列を読み込んだ時の処理
  /// @param[in] str 文字列
  /// @param[in] value_loc 文字列トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_str_value(const char* str,
		 const FileRegion& value_loc) = 0;

};


//////////////////////////////////////////////////////////////////////
/// @class StrHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 文字列を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstString*
  value() const;


private:
  //////////////////////////////////////////////////////////////////////
  // StrBaseHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 文字列を読み込んだ時の処理
  /// @param[in] str 文字列
  /// @param[in] value_loc 文字列トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  read_str_value(const char* str,
		 const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstString* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // STRBASEHANDLER_H
