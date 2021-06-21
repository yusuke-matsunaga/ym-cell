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
#include "ym/ShString.h"


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

  /// @brief int 値を作る．
  static
  AstValuePtr
  new_int(int value,              ///< [in] 値
	  const FileRegion& loc); ///< [in] 値の位置

  /// @brief float 値を作る．
  static
  AstValuePtr
  new_float(double value,           ///< [in] 値
	    const FileRegion& loc); ///< [in] 値の位置

  /// @brief string 値を作る．
  static
  AstValuePtr
  new_string(const ShString& value,  ///< [in] 値
	     const FileRegion& loc); ///< [in] 値の位置

  /// @brief bool 値を作る．
  static
  AstValuePtr
  new_bool(bool value,             ///< [in] 値
	   const FileRegion& loc); ///< [in] 値の位置

  /// @brief delay_model 値を作る．
  static
  AstValuePtr
  new_delay_model(ClibDelayModel value,   ///< [in] 値
		  const FileRegion& loc); ///< [in] 値の位置

  /// @brief direction 値を作る．
  static
  AstValuePtr
  new_direction(ClibDirection value,    ///< [in] 値
		const FileRegion& loc); ///< [in] 値の位置

  /// @brief technology 値を作る．
  static
  AstValuePtr
  new_technology(ClibTechnology value,   ///< [in] 値
		 const FileRegion& loc); ///< [in] 値の位置

  /// @brief timing_sense 値を作る．
  static
  AstValuePtr
  new_timing_sense(ClibTimingSense value,  ///< [in] 値
		   const FileRegion& loc); ///< [in] 値の位置

  /// @brief timing_type 値を作る．
  static
  AstValuePtr
  new_timing_type(ClibTimingType value,   ///< [in] 値
		  const FileRegion& loc); ///< [in] 値の位置

  /// @brief vartype 値を作る．
  static
  AstValuePtr
  new_vartype(ClibVarType value,      ///< [in] 値
	      const FileRegion& loc); ///< [in] 値の位置

  /// @brief expr 値を作る．
  static
  AstValuePtr
  new_expr(unique_ptr<const AstExpr>&& value); ///< [in] 値

  /// @brief int vector 値を作る．
  static
  AstValuePtr
  new_int_vector(const vector<int>& value, ///< [in] 値
		 const FileRegion& loc);   ///< [in] 値の位置

  /// @brief float vector 値を作る．
  static
  AstValuePtr
  new_float_vector(const vector<double>& value, ///< [in] 値
		   const FileRegion& loc);      ///< [in] 値の位置

  /// @brief complex 値を作る．
  static
  AstValuePtr
  new_complex(vector<AstValuePtr>& value, ///< [in] 値のリスト
	      const FileRegion& loc);     ///< [in] 値の位置

  /// @brief group 値を作る．
  static
  AstValuePtr
  new_group(AstValuePtr&& header,           ///< [in] ヘッダ
	    vector<AstAttrPtr>& child_list, ///< [in] 要素のリスト
	    const FileRegion& loc);         ///< [in] 値の位置

  /// @brief 無効な参照値を返す．
  static
  const AstValue&
  null_ref();

  /// @brief デストラクタ
  virtual
  ~AstValue() = default;


protected:

  /// @brief コンストラクタ
  AstValue(const FileRegion& loc); ///< [in] 値のファイル上の位置)


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 適正な値を持っている時 true を返す．
  virtual
  bool
  is_valid() const;

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
  const AstExpr&
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
  const AstValue&
  complex_elem_value(int pos) const; ///< [in] 位置番号( 0 <= pos < complex_elem_size )

  /// @brief group statement のヘッダを返す．
  ///
  /// 異なる型の場合の値は不定
  virtual
  const AstValue&
  group_header_value() const;

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
  const AstAttr&
  group_elem_attr(int pos) const; ///< [in] 位置番号( 0 <= pos < group_elem_size() )

  /// @brief 値のファイル上の位置を返す．
  FileRegion
  loc() const { return mLoc; }

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
