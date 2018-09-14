#ifndef SIMPLEHANDLER_H
#define SIMPLEHANDLER_H

/// @file SimpleHandler.h
/// @brief SimpleHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class SimpleHandler SimpleHandler.h "SimpleHandler.h"
/// @brief simple attribute 用のハンドラ
///
/// 具体的には
///  ':' <value> ';'
/// の形を仮定してパーズを行う．
/// 実際の処理は純粋仮想関数 read_value() が行うので継承クラスで実装する
/// 必要がある．
///
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
  SimpleHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~SimpleHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief シンボルモードの値を返す．
  ///
  /// デフォルト実装では false を返す．
  virtual
  bool
  symbol_mode();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Simple Attribute を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_simple_attribute();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // SIMPLEHANDLER_H
