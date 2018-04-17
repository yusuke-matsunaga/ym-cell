#ifndef DOTLIBHANDLER_H
#define DOTLIBHANDLER_H

/// @file DotlibHandler.h
/// @brief DotlibHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibHandler DotlibHandler.h "DotlibHandler.h"
/// @brief liberty ファイルの各構文要素を読み込むためのクラス
///
/// 属性ごとに読み込んだ結果を表す構文木構造が異なるので仮想クラスにする．
/// 結果を取り出す関数は各継承クラス毎に独自のものを用意する．
//////////////////////////////////////////////////////////////////////
class DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DotlibHandler(DotlibParser& parser);

  /// @brief コピーコンストラクタは禁止
  DotlibHandler(const DotlibHandler& src) = delete;

  /// @brief ムーブコンストラクタも禁止
  DotlibHandler(DotlibHandler&& src) = delete;

  /// @brief デストラクタ
  virtual
  ~DotlibHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 派生クラスが実装する仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_name 属性名
  /// @param[in] attr_loc ファイル上の位置
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  virtual
  bool
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 他のクラスが用いる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パーサーを得る．
  DotlibParser&
  parser();

  /// @brief AstMgr を得る．
  AstMgr&
  mgr();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief complex attribute 用のパースを行う．
  /// @return 正しく読み込めたら true を返す．
  bool
  parse_complex();

  /// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
  /// @param[in] req_type 要求するトークンの型
  bool
  expect(TokenType req_type);

  /// @brief 行末まで読み込む．
  bool
  expect_nl();

  /// @brief デバッグモードの時に true を返す．
  bool
  debug();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // パーサー
  DotlibParser& mParser;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBHANDLER_H
