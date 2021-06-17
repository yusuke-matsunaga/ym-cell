#ifndef ASTVALUE_H
#define ASTVALUE_H

/// @file AstValue.h
/// @brief AstValue のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstValue AstValue.h "AstValue.h"
/// @brief 値を表す基底クラス
///
/// 以下の３種類がある．
/// - simple attribute の値に対応したもの．
/// - complex attribute の値に対応したもの．
/// - group statement の値に対応したもの．
///
/// ただし，complex attribute でも `technology` のように単一の値
/// を持つものもあり，その場合は simple attribute と同一となる．
/// また，group statement の場合はヘッダ部分は complex attribute と同一
/// の形を持つ．要素として複数の AstAttr を持つ．
//////////////////////////////////////////////////////////////////////
class AstValue
{
public:

  /// @brief コンストラクタ
  AstValue(const FileRegion& loc); ///< [in] 値のファイル上の位置)

  /// @brief デストラクタ
  virtual
  ~AstValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief int 型の値を返す．
  ///
  /// int 型でない場合の値は不定
  virtual
  int
  int_value() const;

  /// @brief float 型の値を返す．
  ///
  /// float 型でない場合の値は不定
  virtual
  double
  float_value() const;

  /// @brief string 型の値を返す．
  ///
  /// string 型でない場合の値は不定
  virtual
  ShString
  string_value() const;

  /// @brief bool 型の値を返す．
  ///
  /// bool 型でない場合の値は不定
  virtual
  bool
  bool_value() const;

  /// @brief delay_model 型の値を返す．
  ///
  /// delay_model 型でない場合の値は不定
  virtual
  ClibDelayModel
  delay_model_value() const;

  /// @brief direction 型の値を返す．
  ///
  /// direction 型でない場合の値は不定
  virtual
  ClibDirection
  direction_value() const;

  /// @brief technology 型の値を返す．
  ///
  /// technology 型でない場合の値は不定
  virtual
  ClibTechnology
  technology_value() const;

  /// @brief timing_sense 型の値を返す．
  ///
  /// timing_sense 型でない場合の値は不定
  virtual
  ClibTimingSense
  timing_sense_value() const;

  /// @brief timing_type 型の値を返す．
  ///
  /// timing_type 型でない場合の値は不定
  virtual
  ClibTimingType
  timing_type_value() const;

  /// @brief vartype 型の値を返す．
  ///
  /// vartype 型でない場合の値は不定
  virtual
  ClibVarType
  vartype_value() const;

  /// @brief expr 型の値を返す．
  ///
  /// expr 型でない場合の値は不定
  virtual
  const AstExpr*
  expr_value() const;

  /// @brief int vector 型の値を返す．
  ///
  /// int vector 型でない場合の値は不定
  virtual
  vector<int>
  int_vector_value() const;

  /// @brief float vector 型の値を返す．
  ///
  /// float vector 型でない場合の値は不定
  virtual
  vector<double>
  float_vector_value() const;

  /// @brief complex attribute の場合の要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  virtual
  int
  complex_elem_size() const;

  /// @brief complex attribute の要素を返す．
  ///
  /// 異なる型の場合の値は不定
  virtual
  const AstValue*
  complex_elem_value(int pos) const; ///< [in] 位置番号( 0 <= pos < complex_elem_size )

  /// @brief group statement のヘッダの要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  int
  group_header_size() const
  {
    // 実は complex と同じ
    return complex_elem_size();
  }

  /// @brief group statement のヘッダの要素を返す．
  ///
  /// 異なる型の場合の値は不定
  const AstValue*
  group_header_value(int pos) const ///< [in] 位置番号( 0 <= pos < group_header_size() )
  {
    // 実は complex と同じ
    return complex_elem_value(pos);
  }

  /// @brief group statement の要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  virtual
  int
  group_elem_size() const;

  /// @brief group statement の要素の属性を返す．
  ///
  /// 異なる型の場合の値は不定
  virtual
  const AstAttr*
  group_elem_attr(int pos) const; ///< [in] 位置番号( 0 <= pos < group_elem_size() )

  /// @brief 値のファイル上の位置を返す．
  FileRegion
  loc() const
  {
    return mLoc;
  }

  /// @brief 内容を出力する．
  virtual
  void
  dump(ostream& s) const = 0; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値のファイル上の位置
  FileRegion mLoc;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTVALUE_H
