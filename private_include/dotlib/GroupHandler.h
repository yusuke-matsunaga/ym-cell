#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

/// @file GroupHandler.h
/// @brief GroupHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CGHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupHandler GroupHandler.h "GroupHandler.h"
/// @brief group statement 用のハンドラ
///
/// '(' <value>, <value>, ... ')' '{'
///     属性記述
///     ...
/// '}'
///
/// の形式のパースを行う．
/// このうちのヘッダ部分は CGHandler::parse_header() が行っている．
/// 本体の部分は先頭の '{' を読んだ時点で仮想関数 begin_group() が呼び出されれ，
/// 個々の属性を読んだ時点で仮想関数 parse_attr() が呼び出される．
/// 最後の '}' を読んだ時点で仮想関数 end_group() が呼び出される．
/// 各継承クラスはこれらの仮想関数を実装する必要がある．
///
/// ヘッダの形式でいくつかの継承クラスを持つ．
/// * EmptyGroupHandler
/// * Str1GroupHandler
/// * Str2GroupHandler
/// * Str2IntGroupHandler
//////////////////////////////////////////////////////////////////////
class GroupHandler :
  public CGHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  GroupHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~GroupHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  virtual
  void
  begin_group() = 0;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  virtual
  bool
  read_group_attr(AttrType attr_type,
		  const FileRegion& attr_loc) = 0;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  virtual
  bool
  end_group(const FileRegion& group_loc) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Group Statement を読み込む．
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  bool
  parse_group_statement();

  /// @brief ブール値 のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_bool(const AstBool*& dst,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 整数値 のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_int(const AstInt*& dst,
	    AttrType attr_type,
	    const FileRegion& attr_loc);

  /// @brief float 値のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_float(const AstFloat*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief 文字列値のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_string(const AstString*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 式のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_expr(const AstExpr*& dst,
	     AttrType attr_type,
	     const FileRegion& attr_loc);

  /// @brief 論理関数のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_function(const AstExpr*& dst,
		 AttrType attr_type,
		 const FileRegion& attr_loc);

  /// @brief index attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_index(const AstFloatVector*& dst,
	      AttrType attr_type,
	      const FileRegion& attr_loc);

  /// @brief values attribute のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_values(const AstFloatVector*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief Str1Complex タイプの complex attribute を読み込む．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] group_loc グループ記述全体の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_str1complex(const AstString*& dst,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief Str2Complex タイプの complex attribute を読み込む．
  /// @param[in] dst1, dst2 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] group_loc グループ記述全体の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_str2complex(const AstString*& dst1,
		    const AstString*& dst2,
		    AttrType attr_type,
		    const FileRegion& attr_loc);

  /// @brief Float2Complex タイプの complex attribute を読み込む．
  /// @param[in] dst1, dst2 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] group_loc グループ記述全体の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_float2complex(const AstFloat*& dst1,
		      const AstFloat*& dst2,
		      AttrType attr_type,
		      const FileRegion& attr_loc);

  /// @brief 'domain' Group Statement のパースを行う．
  /// @param[in] dst 結果を格納する変数
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  ///
  /// すでに設定済みの属性に重複して設定しようとするとエラーになる．
  bool
  parse_domain(const AstDomain*& dst,
	       AttrType attr_type,
	       const FileRegion& attr_loc);

  /// @brief 属性がセットされているかチェックする．
  /// @param[in] val 値を持つノード
  /// @param[in] attr_type 属性の型
  /// @param[in] group_loc グループ記述全体の位置
  /// @retval true val が値を持っていた．
  /// @retval false val が nullptr だった．
  ///
  /// val が nullptr の時にエラー出力を行う．
  bool
  check_attr(const AstNode* val,
	     AttrType attr_type,
	     const FileRegion& group_loc);

  /// @brief 同じ属性が重複して定義されている時のエラーを出力する．
  /// @param[in] attr_type 属性の型
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] prev_node 以前に定義されたノード
  void
  duplicate_error(AttrType attr_type,
		  const FileRegion& attr_loc,
		  const AstNode* prev_node);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
