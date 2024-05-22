
/// @file CiBusType.cc
/// @brief CiBusType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBusType.h"
#include "ci/CiPin.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBusType::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBusType::dump(
  Serializer& s
) const
{
  s.dump(name());
  s.dump(std::uint64_t(bit_from()));
  s.dump(std::uint64_t(bit_to()));
}

// @brief バスタイプを読み込む．
unique_ptr<CiBusType>
CiBusType::restore(
  Deserializer& s
)
{
  ShString name;
  s.in() >> name;
  auto bit_from = s.in().read_64();
  auto bit_to = s.in().read_64();
  auto ptr = unique_ptr<CiBusType>{new CiBusType{name, bit_from, bit_to}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
