#ifndef LUACLIB_H
#define LUACLIB_H

/// @file LuaClib.h
/// @brief LuaClib のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/Luapp.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class LuaClib LuaClib.h "LuaClib.h"
/// @brief Clib 用の Luapp 拡張
//////////////////////////////////////////////////////////////////////
class LuaClib :
  public Luapp
{
public:

  /// @brief 空のコンストラクタ
  LuaClib() = default;

  /// @brief 通常のコンストラクタ
  LuaClib(
    lua_Alloc f, ///< [in] アロケーター
    void* ud      ///< [in] ユーザーデータ
  ) : Luapp{f, ud}
  {
  }

  /// @brief すでに生成済みのインタプリタを用いるコンストラクタ
  LuaClib(
    lua_State* L ///< [in] lua インタープリタ
  ) : Luapp{L}
  {
  }

  /// @brief デストラクタ
  ~LuaClib() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 対象が ClibCellLibrary の時 true を返す．
  bool
  is_clib(
    int idx ///< [in] スタック上のインデックス
  );

  /// @brief 対象を ClibCellLibrary として取り出す．
  ///
  /// ClibCellLibrary でない時は nullptr を返す．
  ClibCellLibrary*
  to_clib(
    int idx ///< [in] スタック上のインデックス
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスで用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCellLibrary 関係の初期化を行う．
  void
  init_Clib(
    vector<struct luaL_Reg>& mylib ///< [out] モジュールに登録する関数のリスト
  );

};

END_NAMESPACE_YM

#endif // LUACLIB_H
