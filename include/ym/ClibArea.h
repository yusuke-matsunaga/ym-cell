#ifndef YM_CLIBAREA_H
#define YM_CLIBAREA_H

/// @file ym/ClibArea.h
/// @brief ClibArea のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2016, 2017, 2018, 2019, 2021 Yusuke Matsunaga (松永 裕介)
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
  /// 内容は 0.0 に初期化される．
  ClibArea() = default;

  /// @brief double からの変換コンストラクタ
  explicit
  ClibArea(double v) : ///< [in] 設定する値
    mValue{v}
  {
  }

  /// @brief デストラクタ
  ~ClibArea() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 値を作るクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 無限大の値を作る．
  static
  ClibArea
  infty()
  {
    return ClibArea(std::numeric_limits<double>::max());
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 値を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 値を得る．
  double
  value() const
  {
    return mValue;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 代入演算子
  //////////////////////////////////////////////////////////////////////

  /// @brief 代入演算子
  ClibArea&
  operator=(const ClibArea& src) ///< [in] コピー元のオブジェクト
  {
    mValue = src.mValue;
    return *this;
  }

  /// @brief 加算付き代入演算子
  ClibArea&
  operator+=(const ClibArea& src) ///< [in] オペランド
  {
    mValue += src.mValue;
    return *this;
  }

  /// @brief 減算付き代入演算子
  ClibArea&
  operator-=(const ClibArea& src) ///< [in] オペランド
  {
    mValue -= src.mValue;
    return *this;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue{0.0};

};

/// @brief 加算
/// @relates ClibArea
inline
ClibArea
operator+(const ClibArea& left,  ///< [in] 左のオペランド
	  const ClibArea& right) ///< [in] 右のオペランド
{
  return ClibArea(left).operator+=(right);
}

/// @brief 減算
/// @relates ClibArea
inline
ClibArea
operator-(const ClibArea& left,  ///< [in] 左のオペランド
	  const ClibArea& right) ///< [in] 右のオペランド
{
  return ClibArea(left).operator-=(right);
}

/// @brief 等価比較演算子
/// @relates ClibArea
inline
bool
operator==(const ClibArea& left,  ///< [in] 左のオペランド
	   const ClibArea& right) ///< [in] 右のオペランド
{
  return left.value() == right.value();
}

/// @brief 非等価比較演算子
/// @relates ClibArea
inline
bool
operator!=(const ClibArea& left,  ///< [in] 左のオペランド
	   const ClibArea& right) ///< [in] 右のオペランド
{
  return !operator==(left, right);
}

/// @brief 大小比較演算子
/// @relates ClibArea
inline
bool
operator<(const ClibArea& left,  ///< [in] 左のオペランド
	  const ClibArea& right) ///< [in] 右のオペランド
{
  return left.value() < right.value();
}

/// @brief 大小比較演算子
/// @relates ClibArea
inline
bool
operator>(const ClibArea& left,  ///< [in] 左のオペランド
	  const ClibArea& right) ///< [in] 右のオペランド
{
  return operator<(right, left);
}

/// @brief 大小比較演算子
/// @relates ClibArea
inline
bool
operator<=(const ClibArea& left,  ///< [in] 左のオペランド
	   const ClibArea& right) ///< [in] 右のオペランド
{
  return !operator<(right, left);
}

/// @brief 大小比較演算子
/// @relates ClibArea
inline
bool
operator>=(const ClibArea& left,  ///< [in] 左のオペランド
	   const ClibArea& right) ///< [in] 右のオペランド
{
  return !operator<(left, right);
}

/// @brief ストリーム出力
/// @relates ClibArea
inline
ostream&
operator<<(ostream& s,          ///< [in] 出力先のストリーム
	   const ClibArea& val) ///< [in] 値
{
  return s << val.value();
}

/// @brief ストリーム入力
/// @relates ClibArea
inline
istream&
operator>>(istream& s,    ///< [in] 入力元のストリーム
	   ClibArea& val) ///< [out] 読み出された値を格納する変数
{
  double tmp;
  s >> tmp;
  val = ClibArea{tmp};
  return s;
}

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBAREA_H
