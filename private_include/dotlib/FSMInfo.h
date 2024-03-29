#ifndef FSMINFO_H
#define FSMINFO_H

/// @file FSMInfo.h
/// @brief FSMInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/FLInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class FSMInfo FSMInfo.h "FSMInfo.h"
/// @brief
//////////////////////////////////////////////////////////////////////
class FSMInfo :
  public FLInfo
{
public:

  /// @brief コンストラクタ
  FSMInfo(
    LibraryInfo& library_info
  ) : FLInfo{library_info}
  {
  }

  /// @brief デストラクタ
  ~FSMInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 情報をセットする．
  void
  set(
    const AstValue* ast_val
  );


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////


};

END_NAMESPACE_YM_DOTLIB

#endif // FSMINFO_H
