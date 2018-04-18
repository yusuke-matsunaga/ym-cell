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
/// 具体的には
///  ':' <value> ';'
/// の形を仮定してパーズを行う．
/// <value> の部分が一つのトークンでないとエラーになるので
/// ExprHandler は SimpleHandler の継承クラスではない．
///
/// 継承クラスは以下の通り
///   * DelayModelHandler
///   * FloatHandler
///   * FuncHandler
///   * IntHandler
///   * PinDirectionHandler
///   * StrHandler
///   * TechnologyHandler
///   * TimingSenseHandler
///   * TimingTypeHandler
///   * VarTypeHandler
//////////////////////////////////////////////////////////////////////
class SimpleHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  /// @param[in] sym_mode シンボルモード
  SimpleHandler(DotlibParser& parser,
		bool sym_mode);

  /// @brief デストラクタ
  virtual
  ~SimpleHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_attr_value();


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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // シンボルモード
  bool mSymMode;

};

END_NAMESPACE_YM_DOTLIB

#endif // SIMPLEHANDLER_H
