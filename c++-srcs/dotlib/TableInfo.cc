
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
  // 名前を得る．
  auto& header = val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n == 1 );
  mName = header.complex_elem_value(0).string_value();

  // 属性の辞書を作る．
  mElemDict.set(val);

  bool ok{true};

  if ( mElemDict.get_complex_float_vector("index_1", mIndex1) == ElemDict::ERROR ) {
    ok = false;
  }

  if ( mElemDict.get_complex_float_vector("index_2", mIndex2) == ElemDict::ERROR ) {
    ok = false;
  }

  if ( mElemDict.get_complex_float_vector("index_3", mIndex3) == ElemDict::ERROR ) {
    ok = false;
  }

  if ( mElemDict.get_complex_float_vector("values", mValues) != ElemDict::OK ) {
    ok = false;
  }

  if ( mElemDict.get_value("domain", mDomain) == ElemDict::ERROR ) {
    ok = false;
  }

  return ok;
}

SizeType
TableInfo::gen_lut() const
{
  if ( mValues.size() > 0 ) {
    SizeType templ_id = mLibraryInfo.find_lut(mName);
    if ( templ_id == CLIB_NULLID ) {
      return CLIB_NULLID;
    }
    return library()->add_lut(templ_id, mValues, mIndex1, mIndex2, mIndex3);
  }
  return CLIB_NULLID;
}

// @brief ライブラリを取り出す．
CiCellLibrary*
TableInfo::library() const
{
  return mLibraryInfo.library();
}

END_NAMESPACE_YM_DOTLIB
