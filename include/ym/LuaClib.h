#ifndef LUACLIB_H
#define LUACLIB_H

/// @file LuaClib.h
/// @brief LuaClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include <lua.hpp>


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class LuaClib LuaClib.h "LuaClib.h"
/// @brief Clib 用の Luapp 拡張
///
/// 実際には static member function の定義のみからなる．
//////////////////////////////////////////////////////////////////////
class LuaClib
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCellLibrary 関係の初期化を行う．
  static
  void
  init(
    lua_State* L,                  ///< [in] lua インタプリタ
    vector<struct luaL_Reg>& mylib ///< [out] モジュールに登録する関数のリスト
  );

  /// @brief 対象が ClibCellLibrary の時 true を返す．
  static
  bool
  is_clib(
    lua_State* L, ///< [in] lua インタプリタ
    int idx       ///< [in] スタック上のインデックス
  )
  {
    auto obj = to_clib(L, idx);
    return obj != nullptr;
  }

  /// @brief 対象を ClibCellLibrary として取り出す．
  ///
  /// ClibCellLibrary でない時は nullptr を返す．
  static
  ClibCellLibrary*
  to_clib(
    lua_State* L, ///< [in] lua インタプリタ
    int idx       ///< [in] スタック上のインデックス
  );

};

END_NAMESPACE_YM

#endif // LUACLIB_H
