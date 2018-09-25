#ifndef FUNCHANDLER_H
#define FUNCHANDLER_H

/// @file FuncHandler.h
/// @brief FuncHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/SimpleHandler.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FuncHandler FuncHandler.h "FuncHandler.h"
/// @brief function 属性の値をパーズする simple attribute 用のハンドラ
///
/// やっていることは ExprHandler と似ているが，こっちはもとのデータが
/// 文字列なので一旦 FuncScanner に設定し直している．
//////////////////////////////////////////////////////////////////////
class FuncHandler :
  public SimpleHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  FuncHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~FuncHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を得る．
  const AstExpr*
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
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  const AstExpr* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を得る．
inline
const AstExpr*
FuncHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // FUNCHANDLER_H
