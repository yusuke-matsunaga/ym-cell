#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupHandler GroupHandler.h "GroupHandler.h"
/// @brief group statement 用のハンドラ
///
/// このクラスではなにもパーズしない．
/// 正しく処理させるためには継承クラスで対象の属性を
/// parse_attr() で処理しなければならない．
//////////////////////////////////////////////////////////////////////
class GroupHandler :
  public DotlibHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~GroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる GroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] value_list 値を表すトークンのリスト
  /// @param[out] value_loc 値全体のファイル上の位置
  /// @param[out] end_loc グループ末尾の '}' の位置
  /// @retval true パーズが成功した．
  /// @retval false パーズが失敗した．
  bool
  parse_common(AttrType attr_type,
	       const FileRegion& attr_loc,
	       vector<const AstNode*>& value_list,
	       FileRegion& value_loc,
	       FileRegion& end_loc);


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// このクラスでは常に false を返す．
  virtual
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};


//////////////////////////////////////////////////////////////////////
/// @class EmptyGroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 値をとらないグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class EmptyGroupHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  EmptyGroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~EmptyGroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる EmptyGroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] end_loc グループ末尾の '}' の位置
  /// @retval true パーズが成功した．
  /// @retval false パーズが失敗した．
  bool
  parse_common(AttrType attr_type,
	       const FileRegion& attr_loc,
	       FileRegion& end_loc);

};


//////////////////////////////////////////////////////////////////////
/// @class Str1GroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 1つの文字列型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str1GroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持たないハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str1GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str1GroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str1GroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] value 値を表すトークン
  /// @param[out] value_loc 値のファイル上の位置
  /// @param[out] end_loc グループ末尾の '}' の位置
  /// @retval true パーズが成功した．
  /// @retval false パーズが失敗した．
  bool
  parse_common(AttrType attr_type,
	       const FileRegion& attr_loc,
	       const AstString*& value,
	       FileRegion& value_loc,
	       FileRegion& end_loc);

};


//////////////////////////////////////////////////////////////////////
/// @class Str2GroupHandler GroupHandler.h "GroupHadler.h"
/// @brief 2つの文字列型をとるグループ用のハンドラ
//////////////////////////////////////////////////////////////////////
class Str2GroupHandler :
  public GroupHandler
{
public:

  /// @brief 親を持つハンドラ用のコンストラクタ
  /// @param[in] parser パーサー
  Str2GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  virtual
  ~Str2GroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2GroupHandler の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] value1, value2 値を表すトークン
  /// @param[out] value_loc 値全体のファイル上の位置
  /// @param[out] end_loc グループ末尾の '}' の位置
  /// @retval true パーズが成功した．
  /// @retval false パーズが失敗した．
  bool
  parse_common(AttrType attr_type,
	       const FileRegion& attr_loc,
	       const AstString* value1,
	       const AstString* value2,
	       FileRegion& value_loc,
	       FileRegion& end_loc);

};


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
  virtual
  ~Str2IntGroupHandler();


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いる Str2IntGroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通の処理を行う．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @param[out] value1, value2, value3 値を表すトークン
  /// @param[out] value_loc 値全体のファイル上の位置
  /// @param[out] end_loc グループ末尾の '}' の位置
  /// @retval true パーズが成功した．
  /// @retval false パーズが失敗した．
  bool
  parse_common(AttrType attr_type,
	       const FileRegion& attr_loc,
	       const AstString* value1,
	       const AstString* value2,
	       const AstInt* value3,
	       FileRegion& value_loc,
	       FileRegion& end_loc);

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
