#ifndef DOTLIBTIMINGSENSE_H
#define DOTLIBTIMINGSENSE_H

/// @file DotlibTimingSense.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTimingSense DotlibTimingSense.h "DotlibTimingSense.h"
/// @brief timing sense を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTimingSense :
  public DotlibNode
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibTimingSense(const FileRegion& loc,
		    ClibTimingSense value);

  /// @brief デストラクタ
  virtual
  ~DotlibTimingSense();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingSense を返す．
  ClibTimingSense
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
  ClibTimingSense mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief TimingSense を返す．
inline
ClibTimingSense
DotlibTimingSense::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBTIMINGSENSE_H
