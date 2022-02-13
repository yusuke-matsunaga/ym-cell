#ifndef CIFSMCELL_H
#define CIFSMCELL_H

/// @file CiFsmCell.h
/// @brief CiFsmCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiFsmCell CiFsmCell.h "CiFsmCell.h"
/// @brief 単純なFSMセルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiFsmCell :
  public CiCell
{
public:

  /// @brief コンストラクタ
  CiFsmCell(
    CiCellLibrary* library,                      ///< [in] 親のセルライブラリ
    const ShString& name,                        ///< [in] 名前
    ClibArea area,                               ///< [in] 面積
    const vector<CiInputPin*>& input_list,       ///< [in] 入力ピンのリスト
    const vector<CiOutputPin*>& output_list,     ///< [in] 出力ピンのリスト
    const vector<CiTiming*>& timing_list         ///< [in] タイミング情報のリスト
  ) : CiCell(library, name, area,
	     input_list,
	     output_list,
	     vector<CiInoutPin*>{},
	     timing_list)
  {
  }

  /// @brief デストラクタ
  ~CiFsmCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
  bool
  is_fsm() const override;

};

END_NAMESPACE_YM_CLIB

#endif // CIFSMCELL_H
