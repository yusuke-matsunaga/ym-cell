
/// @file CiBundle.cc
/// @brief CiBundle の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBundle.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBundle::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBundle::dump(
  Serializer& s
) const
{
  s.out() << _name();
  s.dump(pin_list());
}

unique_ptr<CiBundle>
CiBundle::restore(
  Deserializer& s
)
{
  ShString name;
  s.in() >> name;
  vector<const CiPin*> pin_list;
  s.restore(pin_list);
  auto ptr = unique_ptr<CiBundle>{new CiBundle{name, pin_list}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
