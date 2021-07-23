#ifndef CILOGICCELL_H
#define CILOGICCELL_H

/// @file CiLogicCell.h
/// @brief CiLogicCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
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
  CiLogicCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
    const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
    const vector<CiBus*>& bus_list,          ///< [in] バスのリスト
    const vector<CiBundle*>& bundle_list,    ///< [in] バンドルのリスト
    const vector<CiTiming*>& timing_list     ///< [in] タイミング情報のリスト
  ) : CiCell(library, name, area,
	     input_list,
	     output_list,
	     inout_list,
	     vector<CiInternalPin*>(),
	     bus_list,
	     bundle_list,
	     timing_list)
  {
  }

  /// @brief デストラクタ
  ~CiLogicCell() = default;


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
