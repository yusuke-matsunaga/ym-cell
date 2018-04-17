#ifndef PWCOMPLEXHANDLER_H
#define PWCOMPLEXHANDLER_H

/// @file ComplexHandler.h
/// @brief ComplexHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PwComplexHandler ComplexHandler.h "ComplexHandler.h"
/// @brief 折れ線近似モデル用ののcomplex attribute ハンドラ
//////////////////////////////////////////////////////////////////////
class PwComplexHandler :
  public ComplexHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PwComplexHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~PwComplexHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstPieceWise*
  value() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // ComplexHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header();

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) override;

  /// @brief 読み込みが終了した時の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @param[in] header_loc '(' から ')' までのファイル上の位置
  /// @param[in] count 読み込んだ要素数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  end_header(AttrType attr_type,
	     const FileRegion& attr_loc,
	     const FileRegion& header_loc,
	     int count) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 第1パラメータ
  AstInt* mVal1;

  // 第2パラメータ
  AstFloat* mVal2;

  // 読み込んだ値
  AstPieceWise* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // PWCOMPLEXHANDLER_H
