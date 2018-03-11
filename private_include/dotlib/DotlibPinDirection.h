#ifndef DOTLIBPINDIRECTION_H
#define DOTLIBPINDIRECTION_H

/// @file DotlibPinDirection.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibCellPinDirection DotlibPinDirection.h "DotlibPinDirection.h"
/// @brief cell pin directionを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibPinDirection :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibPinDirection(const FileRegion& loc,
		     ClibCellPinDirection value);

  /// @brief デストラクタ
  virtual
  ~DotlibPinDirection();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief CellPinDirection を返す．
  ClibCellPinDirection
  value() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibCellPinDirection mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief CellPinDirection を返す．
inline
ClibCellPinDirection
DotlibPinDirection::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPINDIRECTION_H
