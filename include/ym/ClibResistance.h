#ifndef YM_CLIBRESISTANCE_H
#define YM_CLIBRESISTANCE_H

/// @file ym/ClibResistance.h
/// @brief ClibResistance のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibResistance ClibResistance.h "ym/ClibResistance.h"
/// @brief 抵抗値を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibResistance
{
public:
  //////////////////////////////////////////////////////////////////////
  // コンストラクタ/デストラクタ
  //////////////////////////////////////////////////////////////////////

  /// @brief 空のコンストラクタ
  ClibResistance();

  /// @brief double からの変換コンストラクタ
  explicit
  ClibResistance(double v);

  /// @brief デストラクタ
  ~ClibResistance();


public:
  //////////////////////////////////////////////////////////////////////
  // 値を作るクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 無限大の値を作る．
  static
  ClibResistance
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
  const ClibResistance&
  operator=(const ClibResistance& src);

  /// @brief 加算付き代入演算子
  const ClibResistance&
  operator+=(const ClibResistance& src);

  /// @brief 減算付き代入演算子
  const ClibResistance&
  operator-=(const ClibResistance& src);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

/// @brief 加算
/// @param[in] left, right オペランド
/// @relates ClibResistance
ClibResistance
operator+(const ClibResistance& left,
	  const ClibResistance& right);

/// @brief 減算
/// @param[in] left, right オペランド
/// @relates ClibResistance
ClibResistance
operator-(const ClibResistance& left,
	  const ClibResistance& right);

/// @brief 等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator==(const ClibResistance& left,
	   const ClibResistance& right);

/// @brief 非等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator!=(const ClibResistance& left,
	   const ClibResistance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator<(const ClibResistance& left,
	  const ClibResistance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator>(const ClibResistance& left,
	  const ClibResistance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator<=(const ClibResistance& left,
	   const ClibResistance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibResistance
bool
operator>=(const ClibResistance& left,
	   const ClibResistance& right);

/// @brief ストリーム出力
/// @param[in] s 出力先のストリーム
/// @param[in] val 値
/// @relates ClibResistance
ostream&
operator<<(ostream& s,
	   const ClibResistance& val);


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
inline
ClibResistance::ClibResistance() :
  mValue(0.0)
{
}

// @brief double からの変換コンストラクタ
inline
ClibResistance::ClibResistance(double v) :
  mValue(v)
{
}

// @brief デストラクタ
inline
ClibResistance::~ClibResistance()
{
}

// @brief 無限大の値を作る．
inline
ClibResistance
ClibResistance::infty()
{
  return ClibResistance(std::numeric_limits<double>::max());
}

// @brief 値を得る．
inline
double
ClibResistance::value() const
{
  return mValue;
}

// @brief 代入演算子
inline
const ClibResistance&
ClibResistance::operator=(const ClibResistance& src)
{
  mValue = src.mValue;
  return *this;
}

// @brief 加算付き代入演算子
inline
const ClibResistance&
ClibResistance::operator+=(const ClibResistance& src)
{
  mValue += src.mValue;
  return *this;
}

// @brief 減算付き代入演算子
inline
const ClibResistance&
ClibResistance::operator-=(const ClibResistance& src)
{
  mValue -= src.mValue;
  return *this;
}

// @brief 加算
inline
ClibResistance
operator+(const ClibResistance& left,
	  const ClibResistance& right)
{
  return ClibResistance(left).operator+=(right);
}

// @brief 減算
inline
ClibResistance
operator-(const ClibResistance& left,
	  const ClibResistance& right)
{
  return ClibResistance(left).operator-=(right);
}

// @brief 等価比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator==(const ClibResistance& left,
	   const ClibResistance& right)
{
  return left.value() == right.value();
}

// @brief 非等価比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator!=(const ClibResistance& left,
	   const ClibResistance& right)
{
  return !operator==(left, right);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator<(const ClibResistance& left,
	  const ClibResistance& right)
{
  return left.value() < right.value();
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator>(const ClibResistance& left,
	  const ClibResistance& right)
{
  return operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator<=(const ClibResistance& left,
	   const ClibResistance& right)
{
  return !operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibResistance
inline
bool
operator>=(const ClibResistance& left,
	   const ClibResistance& right)
{
  return !operator<(left, right);
}

// @brief ストリーム出力
inline
ostream&
operator<<(ostream& s,
	   const ClibResistance& val)
{
  return s << val.value();
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBRESISTANCE_H
