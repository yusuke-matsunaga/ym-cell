#ifndef YM_CLIBCAPACITANCE_H
#define YM_CLIBCAPACITANCE_H

/// @file ym/ClibCapacitance.h
/// @brief ClibCapacitance のヘッダファイル
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
/// @class ClibCapacitance ClibCapacitance.h "ym/ClibCapacitance.h"
/// @brief 容量値を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibCapacitance
{
public:
  //////////////////////////////////////////////////////////////////////
  // コンストラクタ/デストラクタ
  //////////////////////////////////////////////////////////////////////

  /// @brief 空のコンストラクタ
  ClibCapacitance();

  /// @brief double からの変換コンストラクタ
  explicit
  ClibCapacitance(double v);

  /// @brief デストラクタ
  ~ClibCapacitance();


public:
  //////////////////////////////////////////////////////////////////////
  // 値を作るクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 無限大の値を作る．
  static
  ClibCapacitance
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
  const ClibCapacitance&
  operator=(const ClibCapacitance& src);

  /// @brief 加算付き代入演算子
  const ClibCapacitance&
  operator+=(const ClibCapacitance& src);

  /// @brief 減算付き代入演算子
  const ClibCapacitance&
  operator-=(const ClibCapacitance& src);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

/// @brief 加算
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
ClibCapacitance
operator+(const ClibCapacitance& left,
	  const ClibCapacitance& right);

/// @brief 減算
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
ClibCapacitance
operator-(const ClibCapacitance& left,
	  const ClibCapacitance& right);

/// @brief 等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator==(const ClibCapacitance& left,
	   const ClibCapacitance& right);

/// @brief 非等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator!=(const ClibCapacitance& left,
	   const ClibCapacitance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator<(const ClibCapacitance& left,
	  const ClibCapacitance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator>(const ClibCapacitance& left,
	  const ClibCapacitance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator<=(const ClibCapacitance& left,
	   const ClibCapacitance& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibCapacitance
bool
operator>=(const ClibCapacitance& left,
	   const ClibCapacitance& right);

/// @brief ストリーム出力
/// @param[in] s 出力先のストリーム
/// @param[in] val 値
/// @relates ClibCapacitance
ostream&
operator<<(ostream& s,
	   const ClibCapacitance& val);

/// @brief バイナリダンプ
/// @param[in] s 出力先のストリーム
/// @param[in] val 値
/// @relates ClibCapacitance
ODO&
operator<<(ODO& s,
	   const ClibCapacitance& val);

/// @brief バイナリリストア
/// @param[in] s 入力元のストリーム
/// @param[out] val 値を格納する変数
/// @relates ClibCapacitance
IDO&
operator>>(IDO& s,
	   ClibCapacitance& val);


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////


// @brief 空のコンストラクタ
inline
ClibCapacitance::ClibCapacitance() :
  mValue(0.0)
{
}

// @brief double からの変換コンストラクタ
inline
ClibCapacitance::ClibCapacitance(double v) :
  mValue(v)
{
}

// @brief デストラクタ
inline
ClibCapacitance::~ClibCapacitance()
{
}

// @brief 無限大の値を作る．
inline
ClibCapacitance
ClibCapacitance::infty()
{
  return ClibCapacitance(DBL_MAX);
}

// @brief 値を得る．
inline
double
ClibCapacitance::value() const
{
  return mValue;
}

// @brief 代入演算子
inline
const ClibCapacitance&
ClibCapacitance::operator=(const ClibCapacitance& src)
{
  mValue = src.mValue;
  return *this;
}

// @brief 加算付き代入演算子
inline
const ClibCapacitance&
ClibCapacitance::operator+=(const ClibCapacitance& src)
{
  mValue += src.mValue;
  return *this;
}

// @brief 減算付き代入演算子
inline
const ClibCapacitance&
ClibCapacitance::operator-=(const ClibCapacitance& src)
{
  mValue -= src.mValue;
  return *this;
}

// @brief 加算
inline
ClibCapacitance
operator+(const ClibCapacitance& left,
	  const ClibCapacitance& right)
{
  return ClibCapacitance(left).operator+=(right);
}

// @brief 減算
inline
ClibCapacitance
operator-(const ClibCapacitance& left,
	  const ClibCapacitance& right)
{
  return ClibCapacitance(left).operator-=(right);
}

// @brief 等価比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator==(const ClibCapacitance& left,
	   const ClibCapacitance& right)
{
  return left.value() == right.value();
}

// @brief 非等価比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator!=(const ClibCapacitance& left,
	   const ClibCapacitance& right)
{
  return !operator==(left, right);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator<(const ClibCapacitance& left,
	  const ClibCapacitance& right)
{
  return left.value() < right.value();
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator>(const ClibCapacitance& left,
	  const ClibCapacitance& right)
{
  return operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator<=(const ClibCapacitance& left,
	   const ClibCapacitance& right)
{
  return !operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibCapacitance
inline
bool
operator>=(const ClibCapacitance& left,
	   const ClibCapacitance& right)
{
  return !operator<(left, right);
}

// @brief ストリーム出力
inline
ostream&
operator<<(ostream& s,
	   const ClibCapacitance& val)
{
  return s << val.value();
}

// @brief バイナリダンプ
// @param[in] s 出力先のストリーム
// @param[in] val 値
// @relates ClibCapacitance
inline
ODO&
operator<<(ODO& s,
	   const ClibCapacitance& val)
{
  return s << val.value();
}

// @brief バイナリリストア
// @param[in] s 入力元のストリーム
// @param[out] val 値を格納する変数
// @relates ClibCapacitance
inline
IDO&
operator>>(IDO& s,
	   ClibCapacitance& val)
{
  double tmp_val;
  s >> tmp_val;
  val = ClibCapacitance(tmp_val);
  return s;
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBCAPACITANCE_H
