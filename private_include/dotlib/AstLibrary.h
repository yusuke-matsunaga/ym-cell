#ifndef ASTLIBRARY_H
#define ASTLIBRARY_H

/// @file AstLibrary.h
/// @brief AstLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNameNode.h"
#include "AstArray.h"
#include "ym/Alloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstLibrary AstLibrary.h "AstLibrary.h"
/// @brief AstNode の木から取り出したライブラリの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstLibrary :
  public AstNameNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  /// @param[in] alloc メモリアロケータ
  AstLibrary(const FileRegion& attr_loc,
	     const StrHandler& header,
	     const LibraryHandler& group,
	     Alloc& alloc);

  /// @brief デストラクタ
  ~AstLibrary();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

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
  const AstFloatStr*
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

  /// @brief "lu_table_template" のリストを返す．
  AstArray<const AstTemplate*>
  lut_template_list() const;

  /// @brief セルのリストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < cell_num() )
  AstArray<const AstCell*>
  cell_list() const;

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
  const AstFloatStr* mCapacitiveLoadUnit;

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

  // lu_table_template のリスト
  AstArray<const AstTemplate*> mLutTemplateList;

  // セルのリスト
  AstArray<const AstCell*> mCellList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

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
const AstFloatStr*
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

// @brief "lu_table_template" のリストを返す．
inline
AstArray<const AstTemplate*>
AstLibrary::lut_template_list() const
{
  return mLutTemplateList;
}

// @brief セルのリストを返す．
inline
AstArray<const AstCell*>
AstLibrary::cell_list() const
{
  return mCellList;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTLIBRARY_H
