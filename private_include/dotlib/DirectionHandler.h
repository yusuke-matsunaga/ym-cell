#ifndef DIRECTIONHANDLER_H
#define DIRECTIONHANDLER_H

/// @file DirectionHandler.h
/// @brief DirectionHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrBaseHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DirectionHandler DirectionHandler.h "dotlib/DirectionHandler.h"
/// @brief 'direction' Simple Attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class DirectionHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DirectionHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~DirectionHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を得る．
  const AstDirection*
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
  const AstDirection* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を得る．
inline
const AstDirection*
DirectionHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DIRECTIONHANDLER_H
