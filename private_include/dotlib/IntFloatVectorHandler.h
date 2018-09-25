#ifndef INTFLOATVECTORHANDLER_H
#define INTFLOATVECTORHANDLER_H

/// @file IntFloatVectorHandler.h
/// @brief IntFloatVectorHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Elem2Handler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class IntFloatVectorHandler IntFloatVectorHandler.h "dotlib/IntFloatVectorHandler.h"
/// @brief ( integer, "float, float, ..." ) の形のヘッダ用のハンドラ
//////////////////////////////////////////////////////////////////////
class IntFloatVectorHandler :
  public Elem2Handler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  IntFloatVectorHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~IntFloatVectorHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 読み込んだ1番目の値を返す．
  const AstInt*
  value1() const;

  /// @brief 読み込んだ2番目の値を返す．
  const AstFloatVector*
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
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 1番目の値
  const AstInt* mValue1;

  // 2番目の値
  const AstFloatVector* mValue2;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 読み込んだ1番目の値を返す．
inline
const AstInt*
IntFloatVectorHandler::value1() const
{
  return mValue1;
}

// @brief 読み込んだ2番目の値を返す．
inline
const AstFloatVector*
IntFloatVectorHandler::value2() const
{
  return mValue2;
}

END_NAMESPACE_YM_DOTLIB

#endif // INTFLOATVECTORHANDLER_H
