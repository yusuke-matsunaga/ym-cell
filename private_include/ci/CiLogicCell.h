#ifndef CILOGICCELL_H
#define CILOGICCELL_H

/// @file CiLogicCell.h
/// @brief CiLogicCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLogicCell CiLogicCell.h "CiLogicCell.h"
/// @brief 論理セルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLogicCell :
  public CiCell
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  /// @param[in] library 親のセルライブラリ
  /// @param[in] name 名前
  /// @param[in] area 面積
  /// @param[in] input_list 入力ピンのリスト
  /// @param[in] output_list 出力ピンのリスト
  /// @param[in] inout_list 入出力ピンのリスト
  /// @param[in] bus_list バスのリスト
  /// @param[in] bundle_list バンドルのリスト
  /// @param[in] timing_list タイミング情報のリスト
  CiLogicCell(CiCellLibrary* library,
	      const ShString& name,
	      ClibArea area,
	      const vector<CiInputPin*>& input_list,
	      const vector<CiOutputPin*>& output_list,
	      const vector<CiInoutPin*>& inout_list,
	      const vector<CiBus*>& bus_list,
	      const vector<CiBundle*>& bundle_list,
	      const vector<CiTiming*>& timing_list);

  /// @brief デストラクタ
  ~CiLogicCell();


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 組み合わせ論理セルの時に true を返す．
  bool
  is_logic() const override;

};

END_NAMESPACE_YM_CLIB

#endif // CILOGICCELL_H
