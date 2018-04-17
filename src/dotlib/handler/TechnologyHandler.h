#ifndef TECHNOLOGYHANDLER_H
#define TECHNOLOGYHANDLER_H

/// @file TechnologyHandler.h
/// @brief TechnologyHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TechnologyHandler TechnologyHandler.h "TechnologyHandler.h"
/// @brief Technology値を取る属性用のハンドラ
//////////////////////////////////////////////////////////////////////
class TechnologyHandler :
  public SimpleHandler
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

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstTechnology*
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
  AstTechnology* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // TECHNOLOGYHANDLER_H
