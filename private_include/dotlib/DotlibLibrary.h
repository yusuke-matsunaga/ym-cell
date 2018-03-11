#ifndef DOTLIBLIBRARY_H
#define DOTLIBLIBRARY_H

/// @file DotlibLibrary.h
/// @brief DotlibLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"
#include "ym/ClibCellLibrary.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibLibrary DotlibLibrary.h "DotlibLibrary.h"
/// @brief DotlibNode の木から取り出したライブラリの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibLibrary :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibLibrary(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

#if 0
  /// @brief 内容を設定する．
  bool
  set_data(const DotlibNode* lib_node);
#endif

  /// @brief 名前を返す．
  ShString
  name() const;

  /// @brief "technology" を返す．
  ClibTechnology
  technology() const;

  /// @brief "delay_model" を返す．
  ClibDelayModel
  delay_model() const;

  /// @brief "bus_naming_style" を返す．
  const DotlibString*
  bus_naming_style() const;

  /// @brief "comment" を返す．
  const DotlibString*
  comment() const;

  /// @brief "date" を返す．
  const DotlibString*
  date() const;

  /// @brief "revision" を返す．
  const DotlibString*
  revision() const;

  /// @brief "capacitive_load_unit"->top() の値を返す．
  /// @note 未定義なら 0.0 が返る．
  double
  capacitive_load_unit() const;

  /// @brief "capacitive_load_unit"->top()->next() の値を返す．
  string
  capacitive_load_unit_str() const;

  /// @brief "current_unit" を返す．
  const DotlibString*
  current_unit() const;

  /// @brief "leakage_power_unit" を返す．
  const DotlibString*
  leakage_power_unit() const;

  /// @brief "pulling_resistance_unit" を返す．
  const DotlibString*
  pulling_resistance_unit() const;

  /// @brief "time_unit" を返す．
  const DotlibString*
  time_unit() const;

  /// @brief "voltage_unit" を返す．
  const DotlibString*
  voltage_unit() const;

  /// @brief lu_table_template のリストを返す．
  const vector<const DotlibTemplate*>&
  lut_template_list() const;

  /// @brief セル定義のリストを返す．
  const vector<const DotlibCell*>&
  cell_list() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリ名
  ShString mName;

  // "technology"
  ClibTechnology mTechnology;

  // "delay_model"
  ClibDelayModel mDelayModel;

  // "bus_naming_style"
  const DotlibString* mBusNamingStyle;

  // "comment"
  const DotlibString* mComment;

  // "date"
  const DotlibString* mDate;

  // "revision"
  const DotlibString* mRevision;

  // "capacitive_load_unit->top"
  double mCapacitiveLoadUnit;

  // "capacitive_load_unit->top->next"
  ShString mCapacitiveLoadUnitStr;

  // "current_unit"
  const DotlibString* mCurrentUnit;

  // "leakage_power_unit"
  const DotlibString* mLeakagePowerUnit;

  // "pulling_resistance_unit"
  const DotlibString* mPullingResistanceUnit;

  // "time_unit"
  const DotlibString* mTimeUnit;

  // "voltage_unit"
  const DotlibString* mVoltageUnit;

  // lu_table_template のリスト
  vector<const DotlibTemplate*> mLutTemplateList;

  // セル定義のリスト
  vector<const DotlibCell*> mCellList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
ShString
DotlibLibrary::name() const
{
  return mName;
}

// @brief "technology" を返す．
inline
ClibTechnology
DotlibLibrary::technology() const
{
  return mTechnology;
}

// @brief "delay_model" を返す．
inline
ClibDelayModel
DotlibLibrary::delay_model() const
{
  return mDelayModel;
}

// @brief "bus_naming_style" を返す．
inline
const DotlibString*
DotlibLibrary::bus_naming_style() const
{
  return mBusNamingStyle;
}

// @brief "comment" を返す．
inline
const DotlibString*
DotlibLibrary::comment() const
{
  return mComment;
}

// @brief "date" を返す．
inline
const DotlibString*
DotlibLibrary::date() const
{
  return mDate;
}

// @brief "revision" を返す．
inline
const DotlibString*
DotlibLibrary::revision() const
{
  return mRevision;
}

// @brief "capacitive_load_unit"->top() を返す．
inline
double
DotlibLibrary::capacitive_load_unit() const
{
  return mCapacitiveLoadUnit;
}

// @brief "capacitive_load_unit"->top()->next() を返す．
inline
string
DotlibLibrary::capacitive_load_unit_str() const
{
  return mCapacitiveLoadUnitStr;
}

// @brief "current_unit" を返す．
inline
const DotlibString*
DotlibLibrary::current_unit() const
{
  return mCurrentUnit;
}

// @brief "leakage_power_unit" を返す．
inline
const DotlibString*
DotlibLibrary::leakage_power_unit() const
{
  return mLeakagePowerUnit;
}

// @brief "pulling_resistance_unit" を返す．
inline
const DotlibString*
DotlibLibrary::pulling_resistance_unit() const
{
  return mPullingResistanceUnit;
}

// @brief "time_unit" を返す．
inline
const DotlibString*
DotlibLibrary::time_unit() const
{
  return mTimeUnit;
}

// @brief "voltage_unit" を返す．
inline
const DotlibString*
DotlibLibrary::voltage_unit() const
{
  return mVoltageUnit;
}

// @brief lu_table_template のリストを返す．
inline
const vector<const DotlibTemplate*>&
DotlibLibrary::lut_template_list() const
{
  return mLutTemplateList;
}

// @brief セル定義のリストを返す．
inline
const vector<const DotlibCell*>&
DotlibLibrary::cell_list() const
{
  return mCellList;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBLIBRARY_H
