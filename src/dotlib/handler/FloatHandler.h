#ifndef FLOATHANDLER_H
#define FLOATHANDLER_H

/// @file FloatHandler.h
/// @brief FloatHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FloatHandler FloatHandler.h "FloatHandler.h"
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

  /// @brief float 値の記述をパースする．
  /// @return 読み込んだ値を返す．
  ///
  /// エラーの場合には nullptr を返す．
  const AstFloat*
  parse_value();


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
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstFloat* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // FLOATHANDLER_H
