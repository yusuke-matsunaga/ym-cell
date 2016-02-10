﻿#ifndef YM_CELLMISLIBREADER_H
#define YM_CELLMISLIBREADER_H

/// @file ym/CellMislibReader.h
/// @brief CellMislibReader のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ym_cell.h"


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
/// @class CellMislibReader CellMislibReader.h "ym/CellMislibReader.h"
/// @brief mislib 形式のファイルを読み込んで CellLibrary に設定するクラス
/// @sa CellLibrary Cell
//////////////////////////////////////////////////////////////////////
class CellMislibReader
{
public:

  /// @brief コンストラクタ
  CellMislibReader();

  /// @brief デストラクタ
  ~CellMislibReader();


public:

  /// @brief mislib 形式のファイルを読み込んでライブラリを生成する．
  /// @param[in] filename ファイル名
  /// @return 読み込んで作成したセルライブラリを返す．
  /// @note エラーが起きたら nullptr を返す．
  const CellLibrary*
  operator()(const string& filename);

  /// @brief mislib 形式のファイルを読み込んでライブラリを生成する．
  /// @param[in] filename ファイル名
  /// @return 読み込んで作成したセルライブラリを返す．
  /// @note エラーが起きたら nullptr を返す．
  const CellLibrary*
  operator()(const char* filename);

};

END_NAMESPACE_YM_CELL

#endif // YM_CELLMISLIBREADER_H
