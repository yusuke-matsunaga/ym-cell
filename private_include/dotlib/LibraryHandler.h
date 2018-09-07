#ifndef LIBRARIRYHANDLER_H
#define LIBRARIRYHANDLER_H

/// @file LibraryHandler.h
/// @brief LibraryHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class LibraryHandler LibraryHandler.h "LibraryHandler.h"
/// @brief 'library' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class LibraryHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  LibraryHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~LibraryHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'library' Group Statement の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstLibrary*& dst);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 読み込んだ値
  AstLibrary* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // LIBRARIRYHANDLER_H
