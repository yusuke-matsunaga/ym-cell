#ifndef YM_CLIBAREA_H
#define YM_CLIBAREA_H

/// @file ym/ClibArea.h
/// @brief ClibArea のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2016, 2017, 2018 Yusuke Matsunaga (松永 裕介)
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @defgroup ClibCellGroup
/// @class ClibArea ClibArea.h "ym/ClibArea.h"
/// @brief 面積を表すクラス
///
/// 内容的には double そのものだが他の単位との演算が
/// 行えないようになっている．
/// ClibArea 同士の演算も加減算のみ定義されている．
//////////////////////////////////////////////////////////////////////
class ClibArea
{
public:
  //////////////////////////////////////////////////////////////////////
  // コンストラクタ/デストラクタ
  //////////////////////////////////////////////////////////////////////

  /// @brief 空のコンストラクタ
  ///
  /// 内容は不定
  ClibArea();

  /// @brief double からの変換コンストラクタ
  explicit
  ClibArea(double v);

  /// @brief デストラクタ
  ~ClibArea();


public:
  //////////////////////////////////////////////////////////////////////
  // 値を作るクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 無限大の値を作る．
  static
  ClibArea
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
  ClibArea&
  operator=(const ClibArea& src);

  /// @brief 加算付き代入演算子
  ClibArea&
  operator+=(const ClibArea& src);

  /// @brief 減算付き代入演算子
  ClibArea&
  operator-=(const ClibArea& src);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};

/// @brief 加算
/// @param[in] left, right オペランド
/// @relates ClibArea
ClibArea
operator+(const ClibArea& left,
	  const ClibArea& right);

/// @brief 減算
/// @param[in] left, right オペランド
/// @relates ClibArea
ClibArea
operator-(const ClibArea& left,
	  const ClibArea& right);

/// @brief 等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator==(const ClibArea& left,
	   const ClibArea& right);

/// @brief 非等価比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator!=(const ClibArea& left,
	   const ClibArea& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator<(const ClibArea& left,
	  const ClibArea& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator>(const ClibArea& left,
	  const ClibArea& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator<=(const ClibArea& left,
	   const ClibArea& right);

/// @brief 大小比較演算子
/// @param[in] left, right オペランド
/// @relates ClibArea
bool
operator>=(const ClibArea& left,
	   const ClibArea& right);

/// @brief ストリーム出力
/// @param[in] s 出力先のストリーム
/// @param[in] val 値
/// @relates ClibArea
ostream&
operator<<(ostream& s,
	   const ClibArea& val);


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 空のコンストラクタ
inline
ClibArea::ClibArea() :
  mValue(0.0)
{
}

// @brief double からの変換コンストラクタ
inline
ClibArea::ClibArea(double v) :
  mValue(v)
{
}

// @brief デストラクタ
inline
ClibArea::~ClibArea()
{
}

// @brief 無限大の値を作る．
inline
ClibArea
ClibArea::infty()
{
  return ClibArea(std::numeric_limits<double>::max());
}

// @brief 値を得る．
inline
double
ClibArea::value() const
{
  return mValue;
}

// @brief 代入演算子
inline
ClibArea&
ClibArea::operator=(const ClibArea& src)
{
  mValue = src.mValue;
  return *this;
}

// @brief 加算付き代入演算子
inline
ClibArea&
ClibArea::operator+=(const ClibArea& src)
{
  mValue += src.mValue;
  return *this;
}

// @brief 減算付き代入演算子
inline
ClibArea&
ClibArea::operator-=(const ClibArea& src)
{
  mValue -= src.mValue;
  return *this;
}

// @brief 加算
inline
ClibArea
operator+(const ClibArea& left,
	  const ClibArea& right)
{
  return ClibArea(left).operator+=(right);
}

// @brief 減算
inline
ClibArea
operator-(const ClibArea& left,
	  const ClibArea& right)
{
  return ClibArea(left).operator-=(right);
}

// @brief 等価比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator==(const ClibArea& left,
	   const ClibArea& right)
{
  return left.value() == right.value();
}

// @brief 非等価比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator!=(const ClibArea& left,
	   const ClibArea& right)
{
  return !operator==(left, right);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator<(const ClibArea& left,
	  const ClibArea& right)
{
  return left.value() < right.value();
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator>(const ClibArea& left,
	  const ClibArea& right)
{
  return operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator<=(const ClibArea& left,
	   const ClibArea& right)
{
  return !operator<(right, left);
}

// @brief 大小比較演算子
// @param[in] left, right オペランド
// @relates ClibArea
inline
bool
operator>=(const ClibArea& left,
	   const ClibArea& right)
{
  return !operator<(left, right);
}

// @brief ストリーム出力
inline
ostream&
operator<<(ostream& s,
	   const ClibArea& val)
{
  return s << val.value();
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBAREA_H
