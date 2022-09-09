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
///
/// 実際には static member function の定義のみからなる．
//////////////////////////////////////////////////////////////////////
class LuaClib :
  public Luapp
{
public:
  //////////////////////////////////////////////////////////////////////
  // コンストラクタ/デストラクタ
  //////////////////////////////////////////////////////////////////////

  /// @brief 空のコンストラクタ
  ///
  /// デフォルトの状態で初期化される．<br>
  /// このオブジェクトとともに Lua インタプリタも破壊される．
  LuaClib() = default;

  /// @brief 詳細なパラメータを指定したコンストラクタ
  ///
  /// このオブジェクトとともに Lua インタプリタも破壊される．
  LuaClib(
    lua_Alloc f, ///< [in] メモリアロケータ
    void* ud     ///< [in] ユーザーデータ
  ) : Luapp{f, ud}
  {
  }

  /// @brief すでに生成済みのインタプリタを用いるコンストラクタ
  ///
  /// このオブジェクトが破壊されても Lua インタプリタは破壊されない．
  LuaClib(
    lua_State* L ///< [in] lua インタプリタ
  ) : Luapp{L}
  {
  }

  /// @brief デストラクタ
  ///
  /// 自前で Lua インタプリタを生成した場合には破壊される．
  ~LuaClib() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCellLibrary 関係の初期化を行う．
  void
  init(
    const char* parent, ///< [in] 親のモジュール名
    const char* name    ///< [in] 自身の名前
  );

  /// @brief 対象が ClibCellLibrary の時 true を返す．
  bool
  is_clib(
    int idx       ///< [in] スタック上のインデックス
  )
  {
    auto obj = to_clib(idx);
    return obj != nullptr;
  }

  /// @brief 対象を ClibCellLibrary として取り出す．
  ///
  /// ClibCellLibrary でない時は nullptr を返す．
  ClibCellLibrary*
  to_clib(
    int idx       ///< [in] スタック上のインデックス
  );


public:
  //////////////////////////////////////////////////////////////////////
  // クラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCellLibrary 関係の初期化を行う．
  static
  void
  init(
    lua_State* L,       ///< [in] lua インタプリタ
    const char* parent, ///< [in] 親のモジュール名
    const char* name    ///< [in] 自身の名前
  )
  {
    LuaClib lua{L};
    lua.init(parent, name);
  }

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
  )
  {
    LuaClib lua{L};
    return lua.to_clib(idx);
  }

};

END_NAMESPACE_YM

#endif // LUACLIB_H
