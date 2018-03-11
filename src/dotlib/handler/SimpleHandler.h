#ifndef SIMPLEHANDLER_H
#define SIMPLEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibHandler.h"


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
  /// @param[in] parent 親のハンドラ
  /// @param[in] sym_mode シンボルモード
  /// @note シンボルモードの時は数字で始まっていても文字列とみなす．
  SimpleHandler(GroupHandler* parent,
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
  DotlibNode*
  read_attr(AttrType attr_type,
	    const FileRegion& attr_loc);


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @return 値を表す DotlibNode を返す．
  /// @note エラーが起きたら nullptr を返す．
  /// @note デフォルトの実装では普通に DotlibParser::read_token() を呼ぶ．
  virtual
  DotlibNode*
  read_value();

  /// @brief 値を読み込んだ時の処理
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value 値
  virtual
  bool
  set_value(AttrType attr_type,
	    const FileRegion& attr_loc,
	    DotlibNodeImpl* value);


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
  /// @param[in] parent 親のハンドラ
  /// @param[in] sym_mode シンボルモード
  /// @note シンボルモードの時は数字で始まっていても文字列とみなす．
  StrSimpleHandler(GroupHandler* parent,
		   bool sym_mode);

  /// @brief デストラクタ
  ~StrSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

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
  /// @param[in] parent 親のハンドラ
  IntSimpleHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~IntSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class BoolSimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief ブール値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class BoolSimpleHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  BoolSimpleHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~BoolSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

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
  /// @param[in] parent 親のハンドラ
  FloatSimpleHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~FloatSimpleHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class TechnologyHandler SimpleHandler.h "SimpleHandler.h"
/// @brief Technology値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TechnologyHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  TechnologyHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~TechnologyHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class DelayModelHandler SimpleHandler.h "SimpleHandler.h"
/// @brief DelayModel値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class DelayModelHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  DelayModelHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~DelayModelHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class CellPinDirectionHandler SimpleHandler.h "SimpleHandler.h"
/// @brief CellPinDirection値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class CellPinDirectionHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  CellPinDirectionHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~CellPinDirectionHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class TimingSenseHandler SimpleHandler.h "SimpleHandler.h"
/// @brief TimingSense値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingSenseHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  TimingSenseHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~TimingSenseHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class TimingTypeHandler SimpleHandler.h "SimpleHandler.h"
/// @brief TimingType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingTypeHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  TimingTypeHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~TimingTypeHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};


//////////////////////////////////////////////////////////////////////
/// @class VarTypeHandler SimpleHandler.h "SimpleHandler.h"
/// @brief VarType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class VarTypeHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parent 親のハンドラ
  VarTypeHandler(GroupHandler* parent);

  /// @brief デストラクタ
  ~VarTypeHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む．
  virtual
  DotlibNode*
  read_value();

};

END_NAMESPACE_YM_DOTLIB

#endif // SIMPLEHANDLER_H
