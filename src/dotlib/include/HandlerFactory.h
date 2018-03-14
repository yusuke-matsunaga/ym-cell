#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

/// @file HandlerFactory.h
/// @brief HandlerFactory のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"


BEGIN_NAMESPACE_YM_DOTLIB

class TimingHandler;
class TableHandler;

//////////////////////////////////////////////////////////////////////
/// @class HandlerFactory HandlerFactory.h "HandlerFactory.h"
/// @brief Handler を生成するファクトリクラス
//////////////////////////////////////////////////////////////////////
class  HandlerFactory
{
public:

  /// @brief コンストラクタ
  HandlerFactory();

  /// @brief デストラクタ
  ~HandlerFactory();


public:
  //////////////////////////////////////////////////////////////////////
  // group handler の生成
  //////////////////////////////////////////////////////////////////////

  /// @brief library group 用のハンドラを作る．
  /// @param[in] parser パーサー
  /// @param[in] ptmgr パース木を管理するオブジェクト
  static
  DotlibHandler*
  new_library(DotlibParser& parser);

  /// @brief input_voltage group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_input_voltage(DotlibParser& parser);

  /// @brief output_voltage group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_output_voltage(DotlibParser& parser);

  /// @brief operating_conditions group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_operating_conditions(DotlibParser& parser);

  /// @brief template group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_template(DotlibParser& parser);

  /// @brief wire_load group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_wire_load(DotlibParser& parser);

  /// @brief wire_load_selection group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_wire_load_selection(DotlibParser& parser);

  /// @brief wire_load_table group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_wire_load_table(DotlibParser& parser);

  /// @brief cell group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_cell(DotlibParser& parser);

  /// @brief leakage_power group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_leakage_power(DotlibParser& parser);

  /// @brief test_cell group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_test_cell(DotlibParser& parser);

  /// @brief ff group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_ff(DotlibParser& parser);

  /// @brief ff_bank group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_ff_bank(DotlibParser& parser);

  /// @brief latch group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_latch(DotlibParser& parser);

  /// @brief latch_bank group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_latch_bank(DotlibParser& parser);

  /// @brief cell 内の internal_power group 用のハンドラを作る．
  static
  DotlibHandler*
  new_cell_internal_power(DotlibParser& parser);

  /// @brief power group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_power(DotlibParser& parser);

  /// @brief statetable group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_statetable(DotlibParser& parser);

  /// @brief bus group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_bus(DotlibParser& parser);

  /// @brief bundle group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_bundle(DotlibParser& parser);

  /// @brief pin group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_pin(DotlibParser& parser);

  /// @brief internal_power group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  DotlibHandler*
  new_internal_power(DotlibParser& parser);

  /// @brief timing group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  TimingHandler*
  new_timing(DotlibParser& parser);

  /// @brief table group 用のハンドラを作る．
  /// @param[in] parent 親のハンドラ
  static
  TableHandler*
  new_table(DotlibParser& parser);

  /// @brief 'index_?' 用のハンドラを作る．
  static
  DotlibHandler*
  new_index(DotlibParser& parser);

  /// @brief ダミーの complex ハンドラを作る．
  static
  DotlibHandler*
  new_complex(DotlibParser& parser);

  /// @brief ダミーの complex ハンドラを作る．
  static
  DotlibHandler*
  new_str1_complex(DotlibParser& parser);

  /// @brief unit 用のハンドラを作る．
  static
  DotlibHandler*
  new_unit(DotlibParser& parser);

  /// @brief piece wise 用のハンドラを作る．
  static
  DotlibHandler*
  new_piece_wise(DotlibParser& parser);

  /// @brief 'values' 用のハンドラを作る．
  static
  DotlibHandler*
  new_values(DotlibParser& parser);

  /// @brief ダミーの simple ハンドラを作る．
  static
  DotlibHandler*
  new_simple(DotlibParser& parser);

  /// @brief string 用のハンドラを作る．
  static
  DotlibHandler*
  new_string(DotlibParser& parser,
	     bool sym_mode);

  /// @brief int 用のハンドラを作る．
  static
  DotlibHandler*
  new_int(DotlibParser& parser);

  /// @brief float 用のハンドラを作る．
  static
  DotlibHandler*
  new_float(DotlibParser& parser);

  /// @brief function group 用のハンドラを作る．
  /// @param[in] parser パーサー
  static
  DotlibHandler*
  new_function(DotlibParser& parser);

  /// @brief 式をパーズするハンドラを作る．
  /// @param[in] parser パーサー
  static
  DotlibHandler*
  new_expr(DotlibParser& parser);

  /// @brief 'technology' 用のハンドラを作る．
  static
  DotlibHandler*
  new_technology(DotlibParser& parser);

  /// @brief 'delay model' 用のハンドラを作る．
  static
  DotlibHandler*
  new_delay_model(DotlibParser& parser);

  /// @brief 'direction' 用のハンドラを作る．
  static
  DotlibHandler*
  new_pin_direction(DotlibParser& parser);

  /// @brief 'timing sense' 用のハンドラを作る．
  static
  DotlibHandler*
  new_timing_sense(DotlibParser& parser);

  /// @brief 'timing type' 用のハンドラを作る．
  static
  DotlibHandler*
  new_timing_type(DotlibParser& parser);

  /// @brief 'var type' 用のハンドラを作る．
  static
  DotlibHandler*
  new_var_type(DotlibParser& parser);

  /// @brief 汎用の group 用のハンドラを作る．
  static
  GroupHandler*
  new_group(DotlibParser& parser);

};

END_NAMESPACE_YM_DOTLIB

#endif // HANDLERFACTORY_H
