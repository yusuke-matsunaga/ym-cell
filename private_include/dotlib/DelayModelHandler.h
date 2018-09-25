#ifndef DELAYMODELHANDLER_H
#define DELAYMODELHANDLER_H

/// @file DelayModelHandler.h
/// @brief DelayModelHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "StrBaseHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DelayModelHandler DelayModelHandler.h "DelayModelHandler.h"
/// @brief 'delay_model' Simple Attribute 用のハンドラ
//////////////////////////////////////////////////////////////////////
class DelayModelHandler :
  public StrBaseHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DelayModelHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~DelayModelHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ値を得る．
  const AstDelayModel*
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
  const AstDelayModel* mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ値を得る．
inline
const AstDelayModel*
DelayModelHandler::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DELAYMODELHANDLER_H
