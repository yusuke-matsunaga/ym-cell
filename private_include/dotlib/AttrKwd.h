#ifndef ATTRKWD_H
#define ATTRKWD_H

/// @file AttrKwd.h
/// @brief AttrKwd のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AttrType.h"


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
  AttrKwd(AttrType attr_type,         ///< [in] 属性の種類
	  const FileRegion& attr_loc) ///< [in] 属性のファイル上の位置
    : mType{attr_type},
      mLoc{attr_loc}
  {
  }

  /// @brief デストラクタ
  ~AttrKwd() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を返す．
  AttrType
  type() const { return mType; }

  /// @brief 位置を返す．
  FileRegion
  loc() const { return mLoc; }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 種類
  AttrType mType;

  // 位置
  FileRegion mLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // ATTRKWD_H
