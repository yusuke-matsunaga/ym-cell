#ifndef YM_CLIBTIME_H
#define YM_CLIBTIME_H

/// @file ym/ClibTime.h
/// @brief ClibTime のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


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
  ClibTime() = default;

  /// @brief double からの変換用コンストラクタ
  explicit
  ClibTime(double v);

  /// @brief デストラクタ
  ~ClibTime() = default;


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
  double mValue{0.0};

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

/// @brief ストリーム入力
/// @param[in] s 入力元のストリーム
/// @param[out] val 読み出された値
/// @relates ClibTime
istream&
operator>>(istream& s,
	   ClibTime& val);


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief double からの変換コンストラクタ
inline
ClibTime::ClibTime(double v) :
  mValue{v}
{
}

// @brief 無限大の値を作る．
inline
ClibTime
ClibTime::infty()
{
  return ClibTime(std::numeric_limits<double>::max());
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

// @brief ストリーム入力
// @param[in] s 入力元のストリーム
// @param[out] val 読み出された値
// @relates ClibTime
inline
istream&
operator>>(istream& s,
	   ClibTime& val)
{
  double tmp;
  s >> tmp;
  val = ClibTime{tmp};
  return s;
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBTIME_H
