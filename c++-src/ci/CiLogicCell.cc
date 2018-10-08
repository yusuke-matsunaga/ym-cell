
/// @file CiLogicCell.cc
/// @brief CiLogicCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLogicCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] library 親のセルライブラリ
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] alloc メモリアロケータ
CiLogicCell::CiLogicCell(CiCellLibrary* library,
			 const ShString& name,
			 ClibArea area,
			 const vector<CiInputPin*>& input_list,
			 const vector<CiOutputPin*>& output_list,
			 const vector<CiInoutPin*>& inout_list,
			 const vector<CiBus*>& bus_list,
			 const vector<CiBundle*>& bundle_list,
			 const vector<CiTiming*>& timing_list,
			 Alloc& alloc) :
  CiCell(library, name, area,
	 input_list,
	 output_list,
	 inout_list,
	 vector<CiInternalPin*>(),
	 bus_list,
	 bundle_list,
	 timing_list,
	 alloc)
{
}

// @brief デストラクタ
CiLogicCell::~CiLogicCell()
{
}

// @brief 組み合わせ論理セルの時に true を返す．
bool
CiLogicCell::is_logic() const
{
  return true;
}

END_NAMESPACE_YM_CLIB
