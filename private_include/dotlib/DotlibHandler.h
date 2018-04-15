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
//////////////////////////////////////////////////////////////////////
class DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DotlibHandler(DotlibParser& parser);

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
  /// @return 読み込んだ属性値を返す．
  ///
  /// エラーが起きたら nullptr を返す．
  virtual
  const AstNode*
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
  /// @param[in] vector_mode ベクタモードの時 true にするフラグ
  /// @param[out] value_loc 読み込んだ値全体のファイル上の位置
  /// @param[out] value_list 読み込んだ値のリストを格納する変数
  /// @return 正しく読み込めたら true を返す．
  bool
  parse_complex(bool vector_mode,
		FileRegion& value_loc,
		vector<const AstNode*>& value_list);

  /// @brief AstNode (の派生クラス)を生成する．
  /// @param[in] loc ファイル上の位置情報
  /// @param[in] type 型
  /// @param[in] vector_mode ベクタモードの時 true にするフラグ
  ///
  /// 残りの情報は parser() からとってくる．
  AstNode*
  new_value(const FileRegion& loc,
	    TokenType type,
	    bool vector_mode);

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
