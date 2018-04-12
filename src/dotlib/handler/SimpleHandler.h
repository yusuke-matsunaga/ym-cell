﻿#ifndef SIMPLEHANDLER_H
#define SIMPLEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class SimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief simple attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class SimpleHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] sym_mode シンボルモード
  ///
  /// シンボルモードの時は数字で始まっていても文字列とみなす．
  SimpleHandler(DotlibParser& parser,
		bool sym_mode);

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
  /// @return 読み込んだ属性値を返す．
  ///
  /// エラーが起きたら false を返す．
  virtual
  AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc);


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @return 値を表す AstNode を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  virtual
  AstNode*
  gen_node();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // シンボルメンバ
  bool mSymMode;

};


//////////////////////////////////////////////////////////////////////
/// @class StrSimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 文字列を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class StrSimpleHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] sym_mode シンボルモード
  ///
  /// シンボルモードの時は数字で始まっていても文字列とみなす．
  StrSimpleHandler(DotlibParser& parser,
		   bool sym_mode);

  /// @brief デストラクタ
  ~StrSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief AstString を作る．
  virtual
  AstNode*
  gen_node() override;

};


//////////////////////////////////////////////////////////////////////
/// @class IntSimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 整数値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class IntSimpleHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  IntSimpleHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~IntSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief AstInt を作る．
  virtual
  AstNode*
  gen_node() override;

};


//////////////////////////////////////////////////////////////////////
/// @class FloatSimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief 実数値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class FloatSimpleHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FloatSimpleHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~FloatSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief AstFloat を作る．
  virtual
  AstNode*
  gen_node() override;

};

END_NAMESPACE_YM_DOTLIB

#endif // SIMPLEHANDLER_H
