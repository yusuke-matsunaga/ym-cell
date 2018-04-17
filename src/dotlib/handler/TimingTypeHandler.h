#ifndef TIMINGTYPEHANDLER_H
#define TIMINGTYPEHANDLER_H

/// @file TimingTypeHandler.h
/// @brief TimingTypeHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingTypeHandler TimingTypeHandler.h "TimingTypeHandler.h"
/// @brief TimingType値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TimingTypeHandler :
  public SimpleHandler
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


protected:
  //////////////////////////////////////////////////////////////////////
  // SimpleHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  AstTimingType* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TIMINGTYPEHANDLER_H
