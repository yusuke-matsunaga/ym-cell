#ifndef ASTATTR_H
#define ASTATTR_H

/// @file AstAttr.h
/// @brief AstAttr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AttrKwd.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstAttr AstAttr.h "AstAttr.h"
/// @brief 属性を表すクラス
///
/// 属性は
/// - 属性名 (AttrType)
/// - 値
/// の組で表されるが，値には様々な種類がある．
//////////////////////////////////////////////////////////////////////
class AstAttr
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 無効な値となる．
  AstAttr() = default;

  /// @brief コンストラクタ
  AstAttr(const AttrKwd& attr,                ///< [in] 属性の型
	  unique_ptr<const AstValue>&& value) ///< [in] 値
    : mAttr{attr},
      mValue{std::move(value)}
  {
  }

  /// @brief デストラクタ
  ~AstAttr() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 有効な値を表す時 true を返す．
  bool
  is_valid() const { return mAttr.name() != "none"; }

  /// @brief 属性を得る．
  const AttrKwd&
  attr() const { return mAttr; }

  /// @brief 属性の値を得る．
  const AstValue&
  value() const { return *mValue; }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,            ///< [in] 出力先のストリーム
       int ilevel = 0) const; ///< [in] インデントレベル


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 属性
  AttrKwd mAttr;

  // 値
  AstValuePtr mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTATTR_H
