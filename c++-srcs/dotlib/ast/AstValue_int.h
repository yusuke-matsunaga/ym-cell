﻿#ifndef ASTVALUE_INT_H
#define ASTVALUE_INT_H

/// @file AstValue_int.h
/// @brief AstValue の派生クラスの定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstSimple AstSimple.h "AstSimple.h"
/// @brief simple attribute の値を表す基底クラス
//////////////////////////////////////////////////////////////////////
class AstSimple :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstSimple(
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstSimple() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をストリーム出力する．
  void
  print(
    ostream& s, ///< [in] 出力先のストリーム
    int ilevel  ///< [in] インデントレベル
  ) const override;

};


//////////////////////////////////////////////////////////////////////
/// @class AstInt AstValue_int.h "AstValue_int.h"
/// @brief 整数値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstInt :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstInt(
    int value,                ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstInt() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数値を返す．
  int
  int_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  int mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstFloat AstValue_int.h "AstValue_int.h"
/// @brief 実数値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloat :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstFloat(
    double value,             ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstFloat() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 数値を返す．
  double
  float_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstString AstValue_int.h "AstValue_int.h"
/// @brief 文字列のノード を表すクラス
//////////////////////////////////////////////////////////////////////
class AstString :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstString(
    ShString value,           ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstString() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 定数シンボルを返す．
  ShString
  string_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ShString mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstBool AstValue_int.h "AstValue_int.h"
/// @brief ブール値のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstBool :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstBool(
    bool value,               ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstBool() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ブール値を返す．
  bool
  bool_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  bool mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstDelayModel AstValue_int.h "AstValue_int.h"
/// @brief delay model のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstDelayModel :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstDelayModel(
    ClibDelayModel value,     ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstDelayModel() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief DelayModel を返す．
  ClibDelayModel
  delay_model_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibDelayModel mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstPieceType AstValue_int.h "AstValue_int.h"
/// @brief piece type のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstPieceType :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstPieceType(
    ClibVarType value,        ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstPieceType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief PieceType を返す．
  ClibVarType
  piece_type_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibVarType mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstDirection AstValue_int.h "AstValue_int.h"
/// @brief 'direction' のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstDirection :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstDirection(
    ClibDirection value,      ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstDirection() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief direction を返す．
  ClibDirection
  direction_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibDirection mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstTechnology AstValue_int.h "AstValue_int.h"
/// @brief technology のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTechnology :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstTechnology(
    ClibTechnology value,     ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstTechnology() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief Technology を返す．
  ClibTechnology
  technology_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTechnology mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstTimingSense AstValue_int.h "AstValue_int.h"
/// @brief timing sense のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingSense :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstTimingSense(
    ClibTimingSense value,    ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstTimingSense() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingSense を返す．
  ClibTimingSense
  timing_sense_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTimingSense mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstTimingType AstValue_int.h "AstValue_int.h"
/// @brief timing type のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingType :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstTimingType(
    ClibTimingType value,     ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstTimingType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingType を返す．
  ClibTimingType
  timing_type_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTimingType mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstVarType AstValue_int.h "AstValue_int.h"
/// @brief var type の simple attribute を表すクラス
//////////////////////////////////////////////////////////////////////
class AstVarType :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstVarType(
    ClibVarType value,        ///< [in] 値
    const FileRegion& val_loc ///< [in] 値のファイル上の位置
  );

  /// @brief デストラクタ
  ~AstVarType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief VarType を返す．
  ClibVarType
  variable_type_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibVarType mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstIntVector AstValue_int.h "AstValue_int.h"
/// @brief 整数値のベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstIntVector :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstIntVector(
    const vector<int>& value, ///< [in] 値
    const FileRegion& loc     ///< [in] ファイル上の位置
  );

  /// @brief デストラクタ
  ~AstIntVector() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタを取り出す．
  vector<int>
  int_vector_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 本体の配列
  vector<int> mBody;

};


//////////////////////////////////////////////////////////////////////
/// @class AstFloatVector AstValue_int.h "AstValue_int.h"
/// @brief ベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloatVector :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  AstFloatVector(
    const vector<double>& value_list, ///< [in] 値のリスト
    const FileRegion& loc             ///< [in] ファイル上の位置
  );

  /// @brief デストラクタ
  ~AstFloatVector() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタの全体を取り出す．
  vector<double>
  float_vector_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ベクタの本体
  vector<double> mBody;

};


//////////////////////////////////////////////////////////////////////
/// @class AstExprValue AstValue_int.h "AstValue_int.h"
/// @brief AstExpr を持つ AstValue の派生クラス
//////////////////////////////////////////////////////////////////////
class AstExprValue :
  public AstSimple
{
public:

  /// @brief コンストラクタ
  ///
  /// value はムーブされる．
  AstExprValue(
    AstExprPtr&& value ///< [in] 値
  );

  /// @brief デストラクタ
  ~AstExprValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief expr 型の値を返す．
  const AstExpr&
  expr_value() const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  AstExprPtr mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class AstComplexValue AstValue_int.h "AstValue_int.h"
/// @brief complex attribute を表すクラス
//////////////////////////////////////////////////////////////////////
class AstComplexValue :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstComplexValue(
    vector<AstValuePtr>& value_list, ///< [in] 値のリスト
    const FileRegion& loc            ///< [in] 位置
  );

  /// @brief デストラクタ
  ~AstComplexValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief complex attribute の場合の要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  SizeType
  complex_elem_size() const override;

  /// @brief complex attribute の要素を返す．
  ///
  /// 異なる型の場合の値は不定
  const AstValue&
  complex_elem_value(
    SizeType pos ///< [in] 位置番号( 0 <= pos < complex_elem_size )
  ) const override;

  /// @brief 内容をストリーム出力する．
  void
  print(
    ostream& s, ///< [in] 出力先のストリーム
    int ilevel  ///< [in] インデントレベル
  ) const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  vector<AstValuePtr> mElemList;

};


//////////////////////////////////////////////////////////////////////
/// @class AstGroupValue AstValue_int.h "AstValue_int.h"
/// @brief group statement を表すクラス
//////////////////////////////////////////////////////////////////////
class AstGroupValue :
 public AstValue
{
public:

  /// @brief コンストラクタ
  AstGroupValue(
    AstValuePtr&& header_value,     ///< [in] ヘッダ
    vector<AstAttrPtr>& child_list, ///< [in] 要素のリスト
    const FileRegion& loc           ///< [in] 位置
  );

  /// @brief デストラクタ
  ~AstGroupValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief group statement のヘッダを返す．
  ///
  /// 異なる型の場合の値は不定
  const AstValue&
  group_header_value() const override;

  /// @brief group statement の要素数を返す．
  ///
  /// 異なる型の場合の値は不定
  SizeType
  group_elem_size() const override;

  /// @brief group statement の要素の属性を返す．
  ///
  /// 異なる型の場合の値は不定
  const AstAttr&
  group_elem_attr(
    SizeType pos ///< [in] 位置番号( 0 <= pos < group_elem_size() )
  ) const override;

  /// @brief 内容をストリーム出力する．
  void
  print(
    ostream& s, ///< [in] 出力先のストリーム
    int ilevel  ///< [in] インデントレベル
  ) const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダ
  AstValuePtr mHeader;

  // 要素のリスト
  vector<AstAttrPtr> mChildList;

};


//////////////////////////////////////////////////////////////////////
/// @class AstNullValue AstValue_int.h "AstValue_int.h"
/// @brief 無効な AstValue を表すクラス
//////////////////////////////////////////////////////////////////////
class AstNullValue :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstNullValue();

  /// @brief デストラクタ
  ~AstNullValue() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 適正な値を持っている時 true を返す．
  bool
  is_valid() const override;

  /// @brief 内容をストリーム出力する．
  void
  print(
    ostream& s, ///< [in] 出力先のストリーム
    int ilevel  ///< [in] インデントレベル
  ) const override;

  /// @brief 値を表す文字列を返す．
  string
  decompile() const override;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTVALUE_INT_H
