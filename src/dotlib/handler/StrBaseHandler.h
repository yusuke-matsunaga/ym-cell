#ifndef STRBASEHANDLER_H
#define STRBASEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class StrBaseHandler StrBaseHandler.h "StrBaseHandler.h"
/// @brief 文字列を取る属性用のハンドラの基底クラス
///
/// SimpleHandler の仮想関数 read_value() は実装しているが，
/// そのなかで純粋仮想関数 read_str_value() を呼んでいる．
/// この関数は継承クラスで実装する必要がある．
///
/// 継承クラスは以下の通り
/// * BoolHandler
/// * DelayModelHandler
/// * PinDirectionHandler
/// * StringHandler
/// * TechnologyHandler
/// * TimingSenseHandler
/// * TimingTypeHandler
/// * VarTypeHandler
//////////////////////////////////////////////////////////////////////
class StrBaseHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  StrBaseHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~StrBaseHandler();


public:
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

END_NAMESPACE_YM_DOTLIB

#endif // STRBASEHANDLER_H
