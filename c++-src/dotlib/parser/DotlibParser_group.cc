
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "FuncParser.h"

#include "dotlib/StrHandler.h"
#include "dotlib/StrIntHandler.h"
#include "dotlib/StrListHandler.h"
#include "dotlib/StrStrHandler.h"
#include "dotlib/StrStrIntHandler.h"

#include "dotlib/GroupHandler.h"
#include "dotlib/CellHandler.h"
#include "dotlib/DomainHandler.h"
#include "dotlib/FFHandler.h"
#include "dotlib/InputVoltageHandler.h"
#include "dotlib/LatchHandler.h"
#include "dotlib/LibraryHandler.h"
#include "dotlib/OutputVoltageHandler.h"
#include "dotlib/PinHandler.h"
#include "dotlib/TableHandler.h"
#include "dotlib/TemplateHandler.h"
#include "dotlib/TimingHandler.h"

#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstCell.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
#include "dotlib/AstDomain.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstFF.h"
#include "dotlib/AstFFBank.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstInputVoltage.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstIntFloat.h"
#include "dotlib/AstIntVector.h"
#include "dotlib/AstLatch.h"
#include "dotlib/AstLatchBank.h"
#include "dotlib/AstLibrary.h"
#include "dotlib/AstLut.h"
#include "dotlib/AstPin.h"
#include "dotlib/AstOutputVoltage.h"
#include "dotlib/AstStr2.h"
#include "dotlib/AstStr3.h"
#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstStrList.h"
#include "dotlib/AstTechnology.h"
#include "dotlib/AstTemplate.h"
#include "dotlib/AstTiming.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/AstTimingType.h"
#include "dotlib/AstVarType.h"

#include "dotlib/TokenType.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'cell' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_cell(vector<const AstCell*>& dst_list,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  bool stat = parse_group_statement(*mStrHeader, *mCellGroup);
  if ( stat ) {
    auto value = mgr().new_cell(*mStrHeader, *mCellGroup);
    dst_list.push_back(value);
  }
  return stat;
}

// @brief 'domain' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_domain(const AstDomain*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrHeader, *mDomainGroup);
    if ( stat ) {
      dst = mgr().new_domain(*mStrHeader, *mDomainGroup);
    }
    return stat;
  }
}

// @brief 'ff' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_ff(const AstFF* dst,
		       AttrType attr_type,
		       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrStrHeader, *mFFGroup);
    if ( stat ) {
      dst = mgr().new_ff(*mStrStrHeader, *mFFGroup);
    }
    return stat;
  }
}

// @brief 'ff_bank' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_ff_bank(const AstFFBank* dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrStrIntHeader, *mFFGroup);
    if ( stat ) {
      dst = mgr().new_ff_bank(*mStrStrIntHeader, *mFFGroup);
    }
    return stat;
  }
}

// @brief 'input_voltage' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_input_voltage(vector<const AstInputVoltage*>& dst_list,
				  AttrType attr_type,
				  const FileRegion& attr_loc)
{
  bool stat = parse_group_statement(*mStrHeader, *mInputVoltageGroup);
  if ( stat ) {
    auto val = mgr().new_input_voltage(*mStrHeader, *mInputVoltageGroup);
    dst_list.push_back(val);
  }
  return stat;
}

// @brief 'latch' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_latch(const AstLatch* dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrStrHeader, *mLatchGroup);
    if ( stat ) {
      dst = mgr().new_latch(*mStrStrHeader, *mLatchGroup);
    }
    return stat;
  }
}

// @brief 'latch_bank' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_latch_bank(const AstLatchBank* dst,
			       AttrType attr_type,
			       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrStrIntHeader, *mLatchGroup);
    if ( stat ) {
      dst = mgr().new_latch_bank(*mStrStrIntHeader, *mLatchGroup);
    }
    return stat;
  }
}

// @brief 'Library' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_library(const AstLibrary*& dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrHeader, *mLibraryGroup);
    if ( stat ) {
      dst = mgr().new_library(*mStrHeader, *mLibraryGroup);
    }
    return stat;
  }
}

// @brief 'OutputVoltage' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_output_voltage(vector<const AstOutputVoltage*>& dst_list,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  bool stat = parse_group_statement(*mStrHeader, *mOutputVoltageGroup);
  if ( stat ) {
    auto val = mgr().new_output_voltage(*mStrHeader, *mOutputVoltageGroup);
    dst_list.push_back(val);
  }
  return stat;
}

// @brief 'pin' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_pin(vector<const AstPin*>& dst_list,
			AttrType attr_type,
			const FileRegion& attr_loc)
{
  bool stat = parse_group_statement(*mStrListHeader, *mPinGroup);
  if ( stat ) {
    auto pin = mgr().new_pin(*mStrListHeader, *mPinGroup);
    dst_list.push_back(pin);
  }
  return stat;
}

// @brief 'table' Group Statement のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_table(const AstLut*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    bool stat = parse_group_statement(*mStrHeader, *mTableGroup);
    if ( stat ) {
      dst = mgr().new_lut(*mStrHeader, *mTableGroup);
    }
    return stat;
  }
}

// @brief 'lut_template' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_template(vector<const AstTemplate*>& dst_list,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  bool stat = parse_group_statement(*mStrHeader, *mTemplateGroup);
  if ( stat ) {
    const AstTemplate* value = mgr().new_template(*mStrHeader, *mTemplateGroup);
    dst_list.push_back(value);
  }
  return stat;
}

// @brief 'timing' Group Statement のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_timing(vector<const AstTiming*>& dst_list,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  StrListHandler header_handler(*this);
  TimingHandler group_handler(*this);
  bool stat = parse_group_statement(*mStrListHeader, *mTimingGroup);
  if ( stat ) {
    const AstTiming* value = mgr().new_timing(*mStrListHeader, *mTimingGroup);
    dst_list.push_back(value);
  }
  return stat;
}

END_NAMESPACE_YM_DOTLIB
