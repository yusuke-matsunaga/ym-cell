
/// @file TableInfo.cc
/// @brief TableInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TableInfo.h"
#include "dotlib/LibraryInfo.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TableInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容をセットする．
bool
TableInfo::set(
  const AstValue* val
)
{
  GroupInfo::set(val);

  bool ok{true};

  // テンプレート名
  auto& header = val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n == 1 );
  auto name = header.complex_elem_value(0).string_value();
  mTemplId = library_info().find_lut(name);
  if ( mTemplId == CLIB_NULLID ) {
    ok = false;
  }

  if ( get_complex_float_vector("index_1", mIndex1) == ERROR ) {
    ok = false;
  }

  if ( get_complex_float_vector("index_2", mIndex2) == ERROR ) {
    ok = false;
  }

  if ( get_complex_float_vector("index_3", mIndex3) == ERROR ) {
    ok = false;
  }

  if ( get_complex_float_vector("values", mValues) != OK ) {
    ok = false;
  }

  if ( get_value("domain", mDomain) == ERROR ) {
    ok = false;
  }

  return ok;
}

SizeType
TableInfo::gen_lut() const
{
  if ( mValues.size() > 0 ) {
    return library()->add_lut(mTemplId, mValues, mIndex1, mIndex2, mIndex3);
  }
  return CLIB_NULLID;
}

END_NAMESPACE_YM_DOTLIB
