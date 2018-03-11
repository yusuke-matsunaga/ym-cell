#ifndef DOTLIBTIMINGTYPE_H
#define DOTLIBTIMINGTYPE_H

/// @file DotlibTimingType.h
/// @brief DotlibTimingType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTimingType DotlibTimingType.h "DotlibTimingType.h"
/// @brief timing typeを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTimingType :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTimingType(const FileRegion& loc,
		   ClibTimingType value);

  /// @brief デストラクタ
  virtual
  ~DotlibTimingType();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingType を返す．
  ClibTimingType
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
  ClibTimingType mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief TimingType を返す．
inline
ClibTimingType
DotlibTimingType::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBTIMINGTYPE_H
