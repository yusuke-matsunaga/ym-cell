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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPHANDLER_H
