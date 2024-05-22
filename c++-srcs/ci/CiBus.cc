
/// @file CiBus.cc
/// @brief CiBus の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBus.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBus::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBus::dump(
  Serializer& s
) const
{
  s.out() << name();
  s.dump(bus_type());
  s.dump(pin_list());
}

unique_ptr<CiBus>
CiBus::restore(
  Deserializer& s
)
{
  ShString name;
  s.in() >> name;
  const CiBusType* bus_type;
  s.restore(bus_type);
  vector<const CiPin*> pin_list;
  s.restore(pin_list);
  auto ptr = unique_ptr<CiBus>{new CiBus{name, bus_type, pin_list}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
