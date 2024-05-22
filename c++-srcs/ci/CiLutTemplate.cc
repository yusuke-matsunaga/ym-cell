
/// @file CiLutTemplate.cc
/// @brief CiLutTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLutTemplate.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"
#include "CiLutTemplate_sub.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiLutTemplate::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 1つの変数の情報をバイナリダンプする．
void
CiLutTemplate::dump_var(
  Serializer& s,
  ClibVarType var_type,
  const vector<double>& index_array
)
{
  s.out() << var_type;
  s.dump(index_array);
}


// @brief 内容を復元する．
unique_ptr<CiLutTemplate>
CiLutTemplate::restore(
  Deserializer& s
)
{
  auto d = s.in().read_8();
  switch ( d ) {
  case 1:
    {
      ClibVarType var_type;
      s.in() >> var_type;
      vector<double> index_array;
      s.restore(index_array);
      return unique_ptr<CiLutTemplate>{new CiLutTemplate1D{var_type, index_array}};
    }
  case 2:
    {
      ClibVarType var_type1;
      s.in() >> var_type1;
      vector<double> index_array1;
      s.restore(index_array1);
      ClibVarType var_type2;
      s.in() >> var_type2;
      vector<double> index_array2;
      s.restore(index_array2);
      return unique_ptr<CiLutTemplate>{new CiLutTemplate2D{var_type1, index_array1,
							   var_type2, index_array2}};
    }
  case 3:
    {
      ClibVarType var_type1;
      s.in() >> var_type1;
      vector<double> index_array1;
      s.restore(index_array1);
      ClibVarType var_type2;
      s.in() >> var_type2;
      vector<double> index_array2;
      s.restore(index_array2);
      ClibVarType var_type3;
      s.in() >> var_type3;
      vector<double> index_array3;
      s.restore(index_array3);
      return unique_ptr<CiLutTemplate>{new CiLutTemplate3D{var_type1, index_array1,
							   var_type2, index_array2,
							   var_type3, index_array3}};
    }
  default:
    ASSERT_NOT_REACHED;
  }
  // ダミー
  return {};
}

//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate1D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate1D::dimension() const
{
  return 1;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate1D::variable_type(
  SizeType var
) const
{
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType;
}

// @brief インデックス数の取得
SizeType
CiLutTemplate1D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray.size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate1D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 1 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray;
}

// @brief 内容をバイナリダンプする．
void
CiLutTemplate1D::dump(
  Serializer& s
) const
{
  s.out().write_8(1);
  dump_var(s, mVarType, mIndexArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate2D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate2D::dimension() const
{
  return 2;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate2D::variable_type(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate2D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate2D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 2 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var];
}

// @brief 内容をバイナリダンプする．
void
CiLutTemplate2D::dump(
  Serializer& s
) const
{
  s.out().write_8(2);
  for ( SizeType i: Range(2) ) {
    dump_var(s, mVarType[i], mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate3D
//////////////////////////////////////////////////////////////////////

// @brief 次元数の取得
SizeType
CiLutTemplate3D::dimension() const
{
  return 3;
}

// @brief 変数型の取得
ClibVarType
CiLutTemplate3D::variable_type(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mVarType[var];
}

// @brief インデックス数の取得
SizeType
CiLutTemplate3D::index_num(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var].size();
}

// @brief インデックス配列の取得
const vector<double>&
CiLutTemplate3D::index_array(
  SizeType var
) const
{
  if ( var < 0 || 3 <= var ) {
    throw std::out_of_range{"var is out of range"};
  }
  return mIndexArray[var];
}

// @brief 内容をバイナリダンプする．
void
CiLutTemplate3D::dump(
  Serializer& s
) const
{
  s.out().write_8(3);
  for ( SizeType i: Range(2) ) {
    dump_var(s, mVarType[i], mIndexArray[i]);
  }
}

END_NAMESPACE_YM_CLIB
