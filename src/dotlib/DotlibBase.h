#ifndef DOTLIBBASE_H
#define DOTLIBBASE_H

/// @file DotlibBase.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibBase DotlibBase.h "DotlibBase.h"
/// @brief 直接値を表すクラスの基底クラス
//////////////////////////////////////////////////////////////////////
class DotlibBase
{
protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibBase(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibBase();


public:

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ファイル上の位置
  FileRegion mLoc;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
inline
DotlibBase::DotlibBase(const FileRegion& loc) :
  mLoc(loc)
{
}

// @brief デストラクタ
inline
DotlibBase::~DotlibBase()
{
}

// @brief ファイル上の位置を返す．
inline
FileRegion
DotlibBase::loc() const
{
  return mLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBBASE_H
