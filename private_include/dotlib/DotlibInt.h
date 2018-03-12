#ifndef DOTLIBINT_H
#define DOTLIBINT_H

/// @file DotlibInt.h
/// @brief DotlibInt のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNum.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibInt DotlibInt.h "DotlibInt.h"
/// @brief 整数値を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibInt :
  public DotlibNum
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  DotlibInt(const FileRegion& loc,
	    int value);

  /// @brief デストラクタ
  virtual
  ~DotlibInt();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値を返す．
  int
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
  int mValue;

};


//////////////////////////////////////////////////////////////////////
// インライン関数
//////////////////////////////////////////////////////////////////////

// @brief 整数値を返す．
inline
int
DotlibInt::value() const
{
  return mValue;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBINT_H
