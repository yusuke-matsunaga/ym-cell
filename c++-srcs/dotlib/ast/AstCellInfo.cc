
/// @file AstCellInfo.cc
/// @brief AstCellInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstCellInfo.h"
#include "dotlib/AstElemDict.h"
#include "dotlib/AstPinInfo.h"
#include "dotlib/AstTimingInfo.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstValue.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 内容を設定する．
bool
AstCellInfo::set(
  const AstValue* cell_val,
  ClibDelayModel delay_model
)
{
  // セル名
  mName = cell_val->group_header_value().complex_elem_value(0).string_value();

  // セルの属性の辞書を作る．
  auto elem_dict = cell_val->gen_group_elem_dict();

  bool ok{true};

  // 面積
  if ( elem_dict.get_area("area", mArea) != AstElemDict::OK ) {
    { // 仮
      cerr << "Error in area: " << endl;
    }
    ok = false;
  }

  // FF
  mHasFF = false;
  if ( elem_dict.count("ff") > 0 ) {
    auto& vec = elem_dict.at("ff");
    if ( vec.size() > 1 ) {
      // "ff" 属性が2回以上現れる．
#warning "TODO: エラーメッセージ"
      cerr << "ff 属性が2回以上現れる．" << endl;
      ok = false;
    }
    else {
      auto ff_val = vec[0];
      if ( mFFInfo.set(ff_val) ) {
	mHasFF = true;
      }
      else {
	ok = false;
      }
    }
  }

  // ラッチ
  mHasLatch = false;
  if ( elem_dict.count("latch") > 0 ) {
    auto& vec = elem_dict.at("latch");
    if ( vec.size() > 1 ) {
      // "latch" 属性が2回以上現れる．
#warning "TODO: エラーメッセージ"
      cerr << "latch 属性が2回以上現れる．" << endl;
      ok = false;
    }
    else {
      auto latch_val = vec[0];
      if ( mLatchInfo.set(latch_val) ) {
	mHasLatch = true;
      }
      else {
	ok = false;
      }
    }
  }

  // statetable(FSM)
  mHasFSM = false;
  if ( elem_dict.count("statetable") > 0 ) {
    auto& vec = elem_dict.at("statetable");
    if ( vec.size() > 1 ) {
      // "statetable" 属性が2回以上現れる．
#warning "TODO: エラーメッセージ"
      cerr << "statetable 属性が2回以上現れる．" << endl;
      ok = false;
    }
    else {
      auto fsm_val = vec[0];
      if ( mFSMInfo.set(fsm_val) ) {
	mHasFSM = true;
      }
      else {
	ok = false;
      }
    }
  }

  // ピンの属性情報を取り出す．
  if ( elem_dict.count("pin") == 0 ) {
    // pin 情報がないセルはないはず．
#warning "TODO: エラーメッセージ"
    cerr << "No pin definitions" << endl;
    ok = false;
  }
  else {
    auto& vec = elem_dict.at("pin");
    SizeType npin = vec.size();
    mPinInfoList.clear();
    mPinInfoList.resize(npin);
    for ( SizeType i = 0; i < npin; ++ i ) {
      auto pin_val = vec[i];
      if ( !mPinInfoList[i].set(pin_val, delay_model) ) {
	cerr << "Error in pin definition" << endl;
	ok = false;
      }
    }
  }

  mInputId = 0;
  mOutputId = 0;

  // phase-1: 入力ピンの名前と入力ピン番号の辞書を作る．
  // phase-2: 出力ピンの名前と出力ピン番号の辞書を作る．
  //
  // 入力ピン番号
  //   0 - (ni - 1)      : 入力ピン
  //  ni - (ni + nb - 1) : 入出力ピン
  //  ni + nb            : Q
  //  ni + nb + 1        : Qvar
  //
  // 出力ピン番号
  //   0 - (no - 1)      : 出力ピン
  //  no - (no + nb - 1) : 入出力ピン
  for ( const auto& pininfo: mPinInfoList ) {
    if ( pininfo.direction() == ClibDirection::input ) {
      for ( auto name: pininfo.name_list() ) {
	mIpinMap.emplace(name, mInputId);
	++ mInputId;
      }
    }
    else if ( pininfo.direction() == ClibDirection::output ) {
      for ( auto name: pininfo.name_list() ) {
	mOpinMap.emplace(name, mOutputId);
	++ mOutputId;
      }
    }
  }

  // phase-3: 入出力ピンの名前と入力ピン番号/出力ピン番号の辞書を作る．
  for ( const auto& pininfo: mPinInfoList ) {
    if ( pininfo.direction() == ClibDirection::inout ) {
      for ( auto name: pininfo.name_list() ) {
	mIpinMap.emplace(name, mInputId);
	++ mInputId;
	mOpinMap.emplace(name, mOutputId);
	++ mOutputId;
      }
    }
  }

  // FF の内部状態変数を入力ピンの辞書に加える．
  if ( mHasFF ) {
    auto var1 = mFFInfo.var1();
    auto var2 = mFFInfo.var2();
    mIpinMap.emplace(var1, mInputId);
    ++ mInputId;
    mIpinMap.emplace(var2, mInputId);
    ++ mInputId;
  }

  // ラッチの内部状態変数を入力ピンの辞書に加える．
  if ( mHasLatch ) {
    auto var1 = mLatchInfo.var1();
    auto var2 = mLatchInfo.var2();
    mIpinMap.emplace(var1, mInputId);
    ++ mInputId;
    mIpinMap.emplace(var2, mInputId);
    ++ mInputId;
  }

  // FSM の内部状態変数を入力ピンの辞書に加える．
  if ( mHasFSM ) {
    auto var1 = mFSMInfo.var1();
    auto var2 = mFSMInfo.var2();
    mIpinMap.emplace(var1, mInputId);
    ++ mInputId;
    mIpinMap.emplace(var2, mInputId);
    ++ mInputId;
  }

  return ok;
}

// @brief セルを作る．
bool
AstCellInfo::add_cell(
  CiCellLibrary* library
) const
{
  SizeType cell_id{CLIB_NULLID};
  if ( mHasFF ) {
    // FF タイプ
    cell_id = add_ff_cell(library);
  }
  else if ( mHasLatch ) {
    // ラッチタイプ
    cell_id = add_latch_cell(library);
  }
  else if ( mHasFSM ) {
    // FSM タイプ
    cell_id = add_fsm_cell(library);
  }
  else {
    // 論理タイプ
    cell_id = library->add_logic_cell(mName, mArea);
  }
  ASSERT_COND( cell_id != CLIB_NULLID );

  library->init_cell_timing_map(cell_id, mInputId, mOutputId);

  // ピンを作る．
  for ( auto& pininfo: mPinInfoList ) {
    pininfo.add_pin(library, cell_id, mIpinMap);
  }

  return true;
}

// @brief FF セルを作る．
SizeType
AstCellInfo::add_ff_cell(
  CiCellLibrary* library
) const
{
  auto var1 = mFFInfo.var1();
  auto var2 = mFFInfo.var2();
  auto clocked_on = mFFInfo.clocked_on()->to_expr(mIpinMap);
  auto clocked_on_also = Expr::make_invalid();
  if ( mFFInfo.clocked_on_also() != nullptr ) {
    clocked_on_also = mFFInfo.clocked_on_also()->to_expr(mIpinMap);
  }
  auto next_state = mFFInfo.next_state()->to_expr(mIpinMap);
  auto clear = Expr::make_invalid();
  if ( mFFInfo.clear() != nullptr ) {
    clear = mFFInfo.clear()->to_expr(mIpinMap);
  }
  auto preset = Expr::make_invalid();
  if ( mFFInfo.preset() != nullptr ) {
    preset = mFFInfo.preset()->to_expr(mIpinMap);
  }
  auto cpv1 = mFFInfo.clear_preset_var1();
  auto cpv2 = mFFInfo.clear_preset_var2();
  auto cell = library->add_ff_cell(mName, mArea,
				   var1, var2,
				   clocked_on, clocked_on_also,
				   next_state, clear, preset,
				   cpv1, cpv2);
  return cell;
}

// @brief ラッチセルを作る．
SizeType
AstCellInfo::add_latch_cell(
  CiCellLibrary* library
) const
{
  auto var1 = mLatchInfo.var1();
  auto var2 = mLatchInfo.var2();
  auto enable_on = Expr::make_invalid();
  if ( mLatchInfo.enable_on() != nullptr ) {
    enable_on = mLatchInfo.enable_on()->to_expr(mIpinMap);
  }
  auto enable_on_also = Expr::make_invalid();
  if ( mLatchInfo.enable_on_also() != nullptr ) {
    enable_on_also = mLatchInfo.enable_on_also()->to_expr(mIpinMap);
  }
  auto data_in = Expr::make_invalid();
  if ( mLatchInfo.data_in() != nullptr ) {
    data_in = mLatchInfo.data_in()->to_expr(mIpinMap);
  }
  auto clear = Expr::make_invalid();
  if ( mLatchInfo.clear() != nullptr ) {
    clear = mLatchInfo.clear()->to_expr(mIpinMap);
  }
  auto preset = Expr::make_invalid();
  if ( mLatchInfo.preset() != nullptr ) {
    preset = mLatchInfo.preset()->to_expr(mIpinMap);
  }
  auto cpv1 = mLatchInfo.clear_preset_var1();
  auto cpv2 = mLatchInfo.clear_preset_var2();
  auto cell = library->add_latch_cell(mName, mArea,
				      var1, var2,
				      enable_on, enable_on_also,
				      data_in, clear, preset,
				      cpv1, cpv2);
  return cell;
}

// @brief FSM セルを作る．
SizeType
AstCellInfo::add_fsm_cell(
  CiCellLibrary* library
) const
{
#warning "TODO: 未完"
  return CLIB_NULLID;
}

END_NAMESPACE_YM_DOTLIB
