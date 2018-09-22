
/// @file DotlibDelayModel.cc
/// @brief DotlibDelayModel の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstDelayModel.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief delay model を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstDelayModel*
AstMgr::new_delay_model(const FileRegion& loc,
			ClibDelayModel value)
{
  ++ mDelayModelNum;
  void* p = mAlloc.get_memory(sizeof(AstDelayModel));
  return new (p) AstDelayModel(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstDelayModel::AstDelayModel(const FileRegion& loc,
			     ClibDelayModel value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstDelayModel::~AstDelayModel()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstDelayModel::dump(ostream& s,
		    int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibDelayModel::GenericCmos:   tmp = "generic cmos"; break;
  case ClibDelayModel::TableLookup:   tmp = "table lookup"; break;
  case ClibDelayModel::PiecewiseCmos: tmp = "piesewise cmos"; break;
  case ClibDelayModel::Cmos2:         tmp = "cmos2"; break;
  case ClibDelayModel::Dcm:           tmp = "dcm"; break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
