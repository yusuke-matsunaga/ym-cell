#ifndef STR2INTGROUPHANDLER_H
#define STR2INTGROUPHANDLER_H

/// @file Str2IntGroupHandler.h
/// @brief Str2IntGroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Str2IntGroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 2つの文字列型と1つの整数型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2IntGroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2IntGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~Str2IntGroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの値1を取り出す．
  const AstString*
  header_value1() const;

  /// @brief ヘッダの値2を取り出す．
  const AstString*
  header_value2() const;

  /// @brief ヘッダの値3を取り出す．
  const AstInt*
  header_value3() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  void
  begin_header() override;

  /// @brief ヘッダの値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  bool
  read_header_value(TokenType value_type,
		    const FileRegion& value_loc,
		    int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  end_header(const FileRegion& header_loc,
	     int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダの値1
  AstString* mHeaderValue1;

  // ヘッダの値2
  AstString* mHeaderValue2;

  // ヘッダの値3
  AstInt* mHeaderValue3;

};

END_NAMESPACE_YM_DOTLIB

#endif // STR2INTGROUPHANDLER_H
