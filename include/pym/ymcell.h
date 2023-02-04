#ifndef PYM_YMCELL_H
#define PYM_YMCELL_H

/// @file ymcell.h
/// @brief ymcell の初期化関数のエクスポート
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym_config.h"


BEGIN_NAMESPACE_YM

/// @brief ymcell モジュールの初期化関数
extern "C" PyObject* PyInit_ymcell();

END_NAMESPACE_YM

#endif // PY_YMCELL_H
