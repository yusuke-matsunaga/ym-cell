#ifndef COMPLEXHANDLER_H
#define COMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class ComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief complex attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class ComplexHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] vector_mode ベクターモードで読み込むとき true にするフラグ
  ComplexHandler(DotlibParser& parser,
		 bool vector_mode = false);

  /// @brief デストラクタ
  virtual
  ~ComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ属性値を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  virtual
  DotlibNode*
  read_attr(AttrType attr_type,
	    const FileRegion& attr_loc);


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を表すノードを作る．
  /// @param[in] value_list 値のリスト
  virtual
  DotlibNode*
  gen_value(DotlibList* value_list) = 0;

private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // parse_complex() 中でベクターモードで読み込む時 true にするフラグ
  bool mVectorMode;

};


//////////////////////////////////////////////////////////////////////
/// @class Str1ComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief 1つの文字列型をとる complex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class Str1ComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Str1ComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str1ComplexHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

};


//////////////////////////////////////////////////////////////////////
/// @class PwComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief 折れ線近似モデル用ののcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class PwComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PwComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~PwComplexHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込んだ時の処理
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  /// @param[in] end_loc 右括弧の位置
  virtual
  bool
  set_value(AttrType attr_type,
	    const FileRegion& attr_loc,
	    DotlibList* value_list,
	    const FileRegion& end_loc);

};

END_NAMESPACE_YM_DOTLIB

#endif // COMPLEXHANDLER_H
