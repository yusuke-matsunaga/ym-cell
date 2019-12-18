#ifndef MISLIBSTR_H
#define MISLIBSTR_H

/// @file MislibStr.h
/// @brief MislibStr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNode.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
/// @class MislibStr MislibStr.h "MislibStr.h"
/// @brief 文字列を表すクラス
//////////////////////////////////////////////////////////////////////
class MislibStr :
  public MislibNode
{
  friend class MislibParser;

private:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] str 共有された文字列のID
  MislibStr(const FileRegion& loc,
	    ShString str);

  /// @brief デストラクタ
  ~MislibStr();


public:

  /// @brief 文字列を取り出す
  ShString
  str() const;

  /// @brief 内容を出力する．
  /// デバッグ用
  void
  dump(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 文字列
  ShString mStr;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// 文字列を取り出す
inline
ShString
MislibStr::str() const
{
  return mStr;
}

END_NAMESPACE_YM_MISLIB

#endif // MISLIBSTR_H
