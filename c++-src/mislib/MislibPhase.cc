
/// @file MislibPhase.cc
/// @brief MislibNoinv, MislibInv, MislibUnknown の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibPhase.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibPhase
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
MislibPhase::MislibPhase(const FileRegion& loc) :
  MislibNode(loc)
{
}

// @brief デストラクタ
MislibPhase::~MislibPhase()
{
}


//////////////////////////////////////////////////////////////////////
// クラス MislibNoinv
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibNoninv::MislibNoninv(const FileRegion& loc) :
  MislibPhase(loc)
{
}

// デストラクタ
MislibNoninv::~MislibNoninv()
{
}

// 種類を取り出す．
MislibPhase::Type
MislibNoninv::type() const
{
  return Noninv;
}

// 内容を出力する．
// デバッグ用
void
MislibNoninv::dump(ostream& s) const
{
  s << "<NONINV>" << endl;
  dump_loc(s);
  s << "</NONINV>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibInv
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibInv::MislibInv(const FileRegion& loc) :
  MislibPhase(loc)
{
}

// デストラクタ
MislibInv::~MislibInv()
{
}

// 種類を取り出す．
MislibPhase::Type
MislibInv::type() const
{
  return Inv;
}

// 内容を出力する．
// デバッグ用
void
MislibInv::dump(ostream& s) const
{
  s << "<INV>" << endl;
  dump_loc(s);
  s << "</INV>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibUnknown
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibUnknown::MislibUnknown(const FileRegion& loc) :
  MislibPhase(loc)
{
}

// デストラクタ
MislibUnknown::~MislibUnknown()
{
}

// 種類を取り出す．
MislibPhase::Type
MislibUnknown::type() const
{
  return Unknown;
}

// 内容を出力する．
// デバッグ用
void
MislibUnknown::dump(ostream& s) const
{
  s << "<UNKNOWN>" << endl;
  dump_loc(s);
  s << "</UNKNOWN>" << endl;
}

END_NAMESPACE_YM_MISLIB
