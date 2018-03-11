#ifndef DOTLIBBUS_H
#define DOTLIBBUS_H

/// @file DotlibBus.h
/// @brief DotlibBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibBase.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibBus DotlibBus.h "DotlibBus.h"
/// @brief DotlibNode の木から取り出したバスの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibBus :
  public DotlibBase
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  DotlibBus(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibBus();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 次の要素を返す．
  const DotlibBus*
  next() const;

  /// @brief 次の要素を設定する．
  void
  set_next(const DotlibBus* next);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 次の要素
  const DotlibBus* mNext;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 次の要素を返す．
inline
const DotlibBus*
DotlibBus::next() const
{
  return mNext;
}

// @brief 次の要素を設定する．
inline
void
DotlibBus::set_next(const DotlibBus* next)
{
  mNext = next;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBBUS_H
