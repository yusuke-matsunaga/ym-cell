#ifndef ATTRKWD_H
#define ATTRKWD_H

/// @file AttrKwd.h
/// @brief AttrKwd のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AttrKwd AttrKwd.h "AttrKwd.h"
/// @brief 属性のキーワードを表すクラス
//////////////////////////////////////////////////////////////////////
class AttrKwd
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  AttrKwd() = default;

  /// @brief 内容を指定したコンストラクタ
  AttrKwd(
    const char* attr_name,     ///< [in] 属性名
    const FileRegion& attr_loc ///< [in] 属性のファイル上の位置
  ) : mName{attr_name},
      mLoc{attr_loc}
  {
  }

  /// @brief デストラクタ
  ~AttrKwd() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性名を返す．
  string
  name() const { return mName; }

  /// @brief 位置を返す．
  FileRegion
  loc() const { return mLoc; }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性名
  string mName;

  // 位置
  FileRegion mLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // ATTRKWD_H
