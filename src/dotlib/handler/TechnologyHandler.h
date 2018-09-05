﻿#ifndef TECHNOLOGYHANDLER_H
#define TECHNOLOGYHANDLER_H

/// @file TechnologyHandler.h
/// @brief TechnologyHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "StrBaseHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TechnologyHandler TechnologyHandler.h "TechnologyHandler.h"
/// @brief Technology値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TechnologyHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TechnologyHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TechnologyHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief technology の記述をパースする．
  ///
  /// エラーが起きた場合には nullptr が返される．
  const AstTechnology*
  parse_value();


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
  const AstTechnology* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TECHNOLOGYHANDLER_H
