#ifndef ASTLIBRARY_H
#define ASTLIBRARY_H

/// @file AstLibrary.h
/// @brief AstLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLibrary AstLibrary.h "AstLibrary.h"
/// @brief AstNode の木から取り出したライブラリの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLibrary :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name
  /// @param[in] technology
  /// @param[in] delay_model
  /// @param[in] bus_naming_style
  /// @param[in] comment
  /// @param[in] date
  /// @param[in] revision
  /// @param[in] capacitive_load_unit
  /// @param[in] current_unit
  /// @param[in] leakage_power_unit
  /// @param[in] pulling_resistance_unit
  /// @param[in] time_unit
  /// @param[in] voltage_unit
  /// @param[in] lut_template_list
  /// @param[in] cell_list
  /// @param[in] alloc
  AstLibrary(const FileRegion& loc,
	     const AstString* name,
	     const AstTechnology* technology,
	     const AstDelayModel* delay_model,
	     const AstString* bus_naming_style,
	     const AstString* comment,
	     const AstString* date,
	     const AstString* revision,
	     const AstUnit* capacitive_load_unit,
	     const AstString* current_unit,
	     const AstString* leakage_power_unit,
	     const AstString* pulling_resistance_unit,
	     const AstString* time_unit,
	     const AstString* voltage_unit,
	     const vector<const AstTemplate*>& lut_template_list,
	     const vector<const AstCell*>& cell_list,
	     Alloc& alloc);

  /// @brief デストラクタ
  ~AstLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief "technology" を返す．
  const AstTechnology*
  technology() const;

  /// @brief "delay_model" を返す．
  const AstDelayModel*
  delay_model() const;

  /// @brief "bus_naming_style" を返す．
  const AstString*
  bus_naming_style() const;

  /// @brief "comment" を返す．
  const AstString*
  comment() const;

  /// @brief "date" を返す．
  const AstString*
  date() const;

  /// @brief "revision" を返す．
  const AstString*
  revision() const;

  /// @brief "capacitive_load_unit" を返す．
  const AstUnit*
  capacitive_load_unit() const;

  /// @brief "current_unit" を返す．
  const AstString*
  current_unit() const;

  /// @brief "leakage_power_unit" を返す．
  const AstString*
  leakage_power_unit() const;

  /// @brief "pulling_resistance_unit" を返す．
  const AstString*
  pulling_resistance_unit() const;

  /// @brief "time_unit" を返す．
  const AstString*
  time_unit() const;

  /// @brief "voltage_unit" を返す．
  const AstString*
  voltage_unit() const;

  /// @brief "lu_table_template" のリストの要素数を返す．
  int
  lut_template_num() const;

  /// @brief "lu_table_template" のリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < lut_template_num() )
  const AstTemplate*
  lut_template_elem(int pos) const;

  /// @brief セルのリストの要素数を返す．
  int
  cell_num() const;

  /// @brief セルのリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < cell_num() )
  const AstCell*
  cell_elem(int pos) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリ名
  const AstString* mName;

  // "technology"
  const AstTechnology* mTechnology;

  // "delay_model"
  const AstDelayModel* mDelayModel;

  // "bus_naming_style"
  const AstString* mBusNamingStyle;

  // "comment"
  const AstString* mComment;

  // "date"
  const AstString* mDate;

  // "revision"
  const AstString* mRevision;

  // "capacitive_load_unit"
  const AstUnit* mCapacitiveLoadUnit;

  // "current_unit"
  const AstString* mCurrentUnit;

  // "leakage_power_unit"
  const AstString* mLeakagePowerUnit;

  // "pulling_resistance_unit"
  const AstString* mPullingResistanceUnit;

  // "time_unit"
  const AstString* mTimeUnit;

  // "voltage_unit"
  const AstString* mVoltageUnit;

  // lu_table_template のリストの要素数
  int mLutTemplateNum;

  // lu_table_template のリスト
  const AstTemplate** mLutTemplateList;

  // セルのリストの要素数
  int mCellNum;

  // セルのリスト
  const AstCell** mCellList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstLibrary::name() const
{
  return mName;
}

// @brief "technology" を返す．
inline
const AstTechnology*
AstLibrary::technology() const
{
  return mTechnology;
}

// @brief "delay_model" を返す．
inline
const AstDelayModel*
AstLibrary::delay_model() const
{
  return mDelayModel;
}

// @brief "bus_naming_style" を返す．
inline
const AstString*
AstLibrary::bus_naming_style() const
{
  return mBusNamingStyle;
}

// @brief "comment" を返す．
inline
const AstString*
AstLibrary::comment() const
{
  return mComment;
}

// @brief "date" を返す．
inline
const AstString*
AstLibrary::date() const
{
  return mDate;
}

// @brief "revision" を返す．
inline
const AstString*
AstLibrary::revision() const
{
  return mRevision;
}

// @brief "capacitive_load_unit"->top() を返す．
inline
const AstUnit*
AstLibrary::capacitive_load_unit() const
{
  return mCapacitiveLoadUnit;
}

// @brief "current_unit" を返す．
inline
const AstString*
AstLibrary::current_unit() const
{
  return mCurrentUnit;
}

// @brief "leakage_power_unit" を返す．
inline
const AstString*
AstLibrary::leakage_power_unit() const
{
  return mLeakagePowerUnit;
}

// @brief "pulling_resistance_unit" を返す．
inline
const AstString*
AstLibrary::pulling_resistance_unit() const
{
  return mPullingResistanceUnit;
}

// @brief "time_unit" を返す．
inline
const AstString*
AstLibrary::time_unit() const
{
  return mTimeUnit;
}

// @brief "voltage_unit" を返す．
inline
const AstString*
AstLibrary::voltage_unit() const
{
  return mVoltageUnit;
}

// @brief "lu_table_template" のリストの要素数を返す．
inline
int
AstLibrary::lut_template_num() const
{
  return mLutTemplateNum;
}

// @brief "lu_table_template" のリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < lut_template_num() )
inline
const AstTemplate*
AstLibrary::lut_template_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < lut_template_num() );

  return mLutTemplateList[pos];
}

// @brief セルのリストの要素数を返す．
inline
int
AstLibrary::cell_num() const
{
  return mCellNum;
}

// @brief セルのリストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < cell_num() )
inline
const AstCell*
AstLibrary::cell_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < cell_num() );

  return mCellList[pos];
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTLIBRARY_H
