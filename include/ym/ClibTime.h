#ifndef YM_CLIBTIME_H
#define YM_CLIBTIME_H

/// @file ym/ClibTime.h
/// @brief ClibTime のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/IDO.h"
#include "ym/ODO.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibTime ClibTime.h "ym/ClibTime.h"
/// @brief 時間を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibTime
{
public:
  //////////////////////////////////////////////////////////////////////
  // コンストラクタ/デストラクタ
  //////////////////////////////////////////////////////////////////////

  /// @brief 空のコンストラクタ
  ClibTime();

  /// @brief double からの変換用コンストラクタ
  explicit
  ClibTime(double v);

  /// @brief デストラクタ
  ~ClibTime();


public:
  //////////////////////////////////////////////////////////////////////
  // 値を作るクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 無限大の値を作る．
  static
  ClibTime
  infty();


public:
  //////////////////////////////////////////////////////////////////////
  // 値を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を得る．
  double
  value() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 代入演算子
  //////////////////////////////////////////////////////////////////////

  /// @brief 代入演算子
  const ClibTime&
  operator=(const ClibTime& src);

  /// @brief 加算付き代入演算子
  const ClibTime&
  operator+=(const ClibTime& src);

  /// @brief 減算付き代入演算子
  const ClibTime&
  operator-=(const ClibTime& src);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

/// @brief 加算
/// @param[in] left, right オペランド
/// @relates ClibTime
ClibTime
operator+(const ClibTime& left,
	  const ClibTime& right);

/// @brief 減算
/// @param[in] left, right オペランド
/// @relates ClibTime
ClibTime
operator-(const ClibTime& left,
	  const ClibTime& right);

/// @brief 等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator==(const ClibTime& left,
	   const ClibTime& right);

/// @brief 非等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator!=(const ClibTime& left,
	   const ClibTime& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator<(const ClibTime& left,
	  const ClibTime& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator>(const ClibTime& left,
	  const ClibTime& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator<=(const ClibTime& left,
	   const ClibTime& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibTime
bool
operator>=(const ClibTime& left,
	   const ClibTime& right);

/// @brief ストリーム出力
ostream&
operator<<(ostream& s,
	   const ClibTime& val);

/// @brief バイナリダンプ
/// @param[in] s 出力先のストリーム
/// @param[in] val 値
/// @relates ClibTime
ODO&
operator<<(ODO& s,
	   const ClibTime& val);

/// @brief バイナリリストア
/// @param[in] s 入力元のストリーム
/// @param[out] val 値を格納する変数
/// @relates ClibTime
IDO&
operator>>(IDO& s,
	   ClibTime& val);


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
inline
ClibTime::ClibTime() :
  mValue(0.0)
{
}

// @brief double からの変換コンストラクタ
inline
ClibTime::ClibTime(double v) :
  mValue(v)
{
}

// @brief デストラクタ
inline
ClibTime::~ClibTime()
{
}

// @brief 無限大の値を作る．
inline
ClibTime
ClibTime::infty()
{
  return ClibTime(DBL_MAX);
}

// @brief 値を得る．
inline
double
ClibTime::value() const
{
  return mValue;
}

// @brief 代入演算子
inline
const ClibTime&
ClibTime::operator=(const ClibTime& src)
{
  mValue = src.mValue;
  return *this;
}

// @brief 加算付き代入演算子
inline
const ClibTime&
ClibTime::operator+=(const ClibTime& src)
{
  mValue += src.mValue;
  return *this;
}

// @brief 減算付き代入演算子
inline
const ClibTime&
ClibTime::operator-=(const ClibTime& src)
{
  mValue -= src.mValue;
  return *this;
}

// @brief 加算
inline
ClibTime
operator+(const ClibTime& left,
	  const ClibTime& right)
{
  return ClibTime(left).operator+=(right);
}

// @brief 減算
inline
ClibTime
operator-(const ClibTime& left,
	  const ClibTime& right)
{
  return ClibTime(left).operator-=(right);
}

// @brief 等価比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator==(const ClibTime& left,
	   const ClibTime& right)
{
  return left.value() == right.value();
}

// @brief 非等価比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator!=(const ClibTime& left,
	   const ClibTime& right)
{
  return !operator==(left, right);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator<(const ClibTime& left,
	  const ClibTime& right)
{
  return left.value() < right.value();
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator>(const ClibTime& left,
	  const ClibTime& right)
{
  return operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator<=(const ClibTime& left,
	   const ClibTime& right)
{
  return !operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibTime
inline
bool
operator>=(const ClibTime& left,
	   const ClibTime& right)
{
  return !operator<(left, right);
}

// @brief ストリーム出力
inline
ostream&
operator<<(ostream& s,
	   const ClibTime& val)
{
  return s << val.value();
}

// @brief バイナリダンプ
// @param[in] s 出力先のストリーム
// @param[in] val 値
// @relates ClibTime
inline
ODO&
operator<<(ODO& s,
	   const ClibTime& val)
{
  return s << val.value();
}

// @brief バイナリリストア
// @param[in] s 入力元のストリーム
// @param[out] val 値を格納する変数
// @relates ClibTime
inline
IDO&
operator>>(IDO& s,
	   ClibTime& val)
{
  double tmp_val;
  s >> tmp_val;
  val = ClibTime(tmp_val);
  return s;
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBTIME_H
