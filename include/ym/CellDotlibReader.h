#ifndef YM_CELLDOTLIBREADER_H
#define YM_CELLDOTLIBREADER_H

/// @file ym/CellDotlibReader.h
/// @brief CellDotlibReader のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ym_cell.h"


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
/// @class CellDotlibReader CellDotlibReader.h "ym/CellDotlibReader.h"
/// @brief dotlib(liberty) を読み込んで CellLibrary に設定するクラス
/// @sa CellLibrary Cell
//////////////////////////////////////////////////////////////////////
class CellDotlibReader
{
public:

  /// @brief コンストラクタ
  CellDotlibReader();

  /// @brief デストラクタ
  ~CellDotlibReader();


public:

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @param[in] library 設定対象のライブラリ
  /// @return 読み込みが成功したら true を返す．
  bool
  read(const string& filename,
       CellLibrary* library);

  /// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
  /// @param[in] filename ファイル名
  /// @param[in] library 設定対象のライブラリ
  /// @return 読み込みが成功したら true を返す．
  bool
  read(const char* filename,
       CellLibrary* library);

};

END_NAMESPACE_YM_CELL

#endif // YM_CELLDOTLIBREADER_H
