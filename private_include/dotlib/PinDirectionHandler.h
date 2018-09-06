#ifndef PINDIRECTIONHANDLER_H
#define PINDIRECTIONHANDLER_H

/// @file PinDirectionHandler.h
/// @brief PinDirectionHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrBaseHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PinDirectionHandler PinDirectionHandler.h "PinDirectionHandler.h"
/// @brief 'pin_direction' Simple Attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class PinDirectionHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PinDirectionHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~PinDirectionHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief pin_direction の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstPinDirection*& dst);


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
  const AstPinDirection* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // PINDIRECTIONHANDLER_H
