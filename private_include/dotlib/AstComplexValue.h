#ifndef ASTCOMPLEXVALUE_H
#define ASTCOMPLEXVALUE_H

/// @file AstComplexValue.h
/// @brief AstComplexValue のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstComplexValue AstComplexValue.h "AstComplexValue.h"
/// @brief complex attribute を表すクラス
//////////////////////////////////////////////////////////////////////
class AstComplexValue :
  public AstValue
{
public:

  /// @brief コンストラクタ(引数1)
  AstComplexValue(unique_ptr<const AstValue>&& value1);

  /// @brief コンストラクタ(引数2)
  AstComplexValue(unique_ptr<const AstValue>&& value1,
		  unique_ptr<const AstValue>&& value2);

  /// @brief コンストラクタ(引数3)
  AstComplexValue(unique_ptr<const AstValue>&& value1,
		  unique_ptr<const AstValue>&& value2,
		  unique_ptr<const AstValue>&& value2);

  /// @brief コンストラクタ(可変引数)
  AstComplexValue(const vector<unique_ptr<const AstValue>>& value_list);

  /// @brief デストラクタ
  ~AstComplexValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief complex attribute の場合の要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  int
  complex_elem_size() const override;

  /// @brief complex attribute の要素を返す．
  ///
  /// 異なる型の場合の値は不定
  const AstValue*
  complex_elem_value(int pos) const override; ///< [in] 位置番号( 0 <= pos < complex_elem_size )


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  vector<unique_ptr<const AstValue>> mElemList;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTCOMPLEXVALUE_H
