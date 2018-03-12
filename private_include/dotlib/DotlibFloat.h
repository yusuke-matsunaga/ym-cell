#ifndef DOTLIBFLOAT_H
#define DOTLIBFLOAT_H

/// @file DotlibNodeImpl.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNum.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibFloat DotlibFloat.h "DotlibFloat.h"
/// @brief 実数値を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibFloat :
  public DotlibNum
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibFloat(const FileRegion& loc,
	      double value);

  /// @brief デストラクタ
  virtual
  ~DotlibFloat();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  /// @note type() が kFloat の時のみ意味を持つ．
  double
  value() const;

  /// @brief 数値を返す．
  virtual
  double
  float_value() const;

  /// @brief float 値を取り出す．
  ///
  /// 型が違ったらエラーを MsgMgr に出力する．
  virtual
  bool
  expect_float(double& value) const;

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
  double mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 数値を返す．
// @note type() が kFloat の時のみ意味を持つ．
inline
double
DotlibFloat::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBFLOAT_H
