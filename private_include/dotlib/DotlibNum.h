#ifndef DOTLIBNUM_H
#define DOTLIBNUM_H

/// @file DotlibNum.h
/// @brief DotlibNum のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibNum DotlibNum.h "DotlibNum.h"
/// @brief 数値を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibNum :
  public DotlibNode
{
  friend class DotlibMgrImpl;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibNum(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~DotlibNum();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  virtual
  double
  float_value() const = 0;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNUM_H
