#ifndef TIMINGTYPEHANDLER_H
#define TIMINGTYPEHANDLER_H

/// @file TimingTypeHandler.h
/// @brief TimingTypeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "StrBaseHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingTypeHandler TimingTypeHandler.h "TimingTypeHandler.h"
/// @brief TimingType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingTypeHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TimingTypeHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TimingTypeHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstTimingType*
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
  const AstTimingType* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TIMINGTYPEHANDLER_H
