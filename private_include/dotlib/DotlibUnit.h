#ifndef DOTLIBUNIT_H
#define DOTLIBUNIT_H

/// @file DotlibUnit.h
/// @brief DotlibUnit のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibUnit DotlibUnit.h "DotlibUnit.h"
/// @brief 単位を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibUnit :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] unit_val 数値
  /// @param[in] unit_str 単位を表す文字列
  DotlibUnit(const FileRegion& loc,
	     double unit_val,
	     const ShString& unit_str);

  /// @brief デストラクタ
  virtual
  ~DotlibUnit();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 単位を表す数値を返す．
  double
  unit_val() const;

  /// @brief 単位を表す文字列を返す．
  ShString
  unit_str() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 単位を表す数値
  double mVal;

  // 単位を表す文字列
  ShString mStr;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 単位を表す数値を返す．
inline
double
DotlibUnit::unit_val() const
{
  return mVal;
}

// @brief 単位を表す文字列を返す．
inline
ShString
DotlibUnit::unit_str() const
{
  return mStr;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBUNIT_H
