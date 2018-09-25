#ifndef FLOAT2HANDLER_H
#define FLOAT2HANDLER_H

/// @file Float2Handler.h
/// @brief Float2Handler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem2Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Float2Handler Float2Handler.h "dotlib/Float2Handler.h"
/// @brief ( float, float ) の形式のヘッダ用ハンドラ
//////////////////////////////////////////////////////////////////////
class Float2Handler :
  public Elem2Handler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  Float2Handler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Float2Handler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 1番目の値を返す．
  const AstFloat*
  value1() const;

  /// @brief 2番目の値を返す．
  const AstFloat*
  value2() const;


private:
  //////////////////////////////////////////////////////////////////////
  // Elem2Handler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief begin_header() 内で呼ばれる初期化関数
  void
  initialize() override;

  /// @brief 1つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  bool
  read_header_value1(TokenType value_type,
		     const FileRegion& value_loc) override;

  /// @brief 2つめのヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  bool
  read_header_value2(TokenType value_type,
		     const FileRegion& value_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の値
  const AstFloat* mValue1;

  // 2番目の値
  const AstFloat* mValue2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 1番目の値を返す．
inline
const AstFloat*
Float2Handler::value1() const
{
  return mValue1;
}

// @brief 2番目の値を返す．
inline
const AstFloat*
Float2Handler::value2() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // FLOAT2HANDLER_H
