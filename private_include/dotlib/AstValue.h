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
/// @brief 単一の値を表す基底クラス
//////////////////////////////////////////////////////////////////////
class AstValue
{
public:

  /// @brief コンストラクタ
  AstValue(const FileRegion& loc);   ///< [in] 値のファイル上の位置)

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

  /// @brief string vector 型の値を返す．
  ///
  /// string vector 型でない場合の値は不定
  virtual
  vector<ShString>
  string_vector_value() const;

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
