#ifndef CGHANDLER_H
#define CGHANDLER_H

/// @file CGHandler.h
/// @brief CGHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class CGHandler CGHandler.h "CGHandler.h"
/// @brief complex attribute/group attribute 用のハンドラ
///
/// 継承クラスで begin_header(), read_value(), end_header()
/// を実装する必要がある．
/// ここでは header と読んでいるが complex attribute の場合はそれが
/// 本体となる．
//////////////////////////////////////////////////////////////////////
class CGHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  CGHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~CGHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダ部分の読み込みを行う．
  bool
  parse_header();


protected:
  //////////////////////////////////////////////////////////////////////
  // CGHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ヘッダの開始処理
  ///
  /// '(' を読み込んだ時に呼ばれる．
  virtual
  void
  begin_header() = 0;

  /// @brief 値を読み込む処理
  /// @param[in] value_type 型
  /// @param[in] value_loc トークンの位置
  /// @param[in] count read_value() の呼ばれた回数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  read_value(TokenType value_type,
	     const FileRegion& value_loc,
	     int count) = 0;

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
	     int count) = 0;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // CGHANDLER_H
