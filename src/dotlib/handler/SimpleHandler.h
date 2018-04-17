#ifndef SIMPLEHANDLER_H
#define SIMPLEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class SimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief simple attribute 用のハンドラ
///
/// このクラスで DotlibHandler の仮想関数である parse_attr_value()
/// を実装している．
/// 継承クラスで read_value() を実装する必要がある．
//////////////////////////////////////////////////////////////////////
class SimpleHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  SimpleHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~SimpleHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_name 属性名
  /// @param[in] attr_loc ファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) = 0;

};


//////////////////////////////////////////////////////////////////////
/// @class StrHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 文字列を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrHandler :
  public SimpleHandler
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


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  AstString* mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class IntHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 整数値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class IntHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  IntHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~IntHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstInt*
  value() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  AstInt* mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class FloatHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 実数値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class FloatHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FloatHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~FloatHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstFloat*
  value() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  AstFloat* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // SIMPLEHANDLER_H
