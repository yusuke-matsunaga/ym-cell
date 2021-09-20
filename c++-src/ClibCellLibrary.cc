
/// @file ClibCellLibrary.cc
/// @brief ClibCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellLibrary.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief コピーコンストラクタ
//
// '浅い'コピーを行う．
ClibCellLibrary::ClibCellLibrary(
  const ClibCellLibrary& src
)
{
  change_impl(src.mImpl);
}

// @brief 代入演算子
ClibCellLibrary&
ClibCellLibrary::operator=(
  const ClibCellLibrary& src
)
{
  change_impl(src.mImpl);
  return *this;
}

// @brief デストラクタ
ClibCellLibrary::~ClibCellLibrary()
{
  change_impl(nullptr);
}

// @brief mImpl を切り替える．
void
ClibCellLibrary::change_impl(
  CiCellLibrary* new_impl
)
{
  if ( mImpl == new_impl ) {
    // なにもしない．
    return;
  }

  if ( mImpl != nullptr ) {
    // 古いオブジェクトの参照回数を一つ減らす．
    mImpl->dec_ref();
  }
  if ( new_impl != nullptr ) {
    // 新しいオブジェクトの参照回数を一つ増やす．
    new_impl->inc_ref();
  }
  mImpl = new_impl;
}

// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
ClibCellLibrary
ClibCellLibrary::read_mislib(
  const string& filename
)
{
  ClibCellLibrary lib;
  auto new_impl = CiCellLibrary::read_mislib(filename);
  if ( new_impl != nullptr ) {
    lib.change_impl(new_impl);
  }
  return lib;
}

// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
ClibCellLibrary
ClibCellLibrary::read_liberty(
  const string& filename
)
{
  ClibCellLibrary lib;
  auto new_impl = CiCellLibrary::read_liberty(filename);
  if ( new_impl != nullptr ) {
    lib.change_impl(new_impl);
  }
  return lib;
}

// @brief 名前の取得
string
ClibCellLibrary::name() const
{
  if ( mImpl ) {
    return mImpl->name();
  }
  else {
    return string();
  }
}

// @brief テクノロジの取得
ClibTechnology
ClibCellLibrary::technology() const
{
  if ( mImpl ) {
    return mImpl->technology();
  }
  else {
    // デフォルトは CMOS
    return ClibTechnology::cmos;
  }
}

// @brief 遅延モデルの取得
ClibDelayModel
ClibCellLibrary::delay_model() const
{
  if ( mImpl ) {
    return mImpl->delay_model();
  }
  else {
    // デフォルト値
    return ClibDelayModel::generic_cmos;
  }
}

// @brief バス命名規則の取得
string
ClibCellLibrary::bus_naming_style() const
{
  if ( mImpl ) {
    return mImpl->bus_naming_style();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 日付情報の取得
string
ClibCellLibrary::date() const
{
  if ( mImpl ) {
    return mImpl->date();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief リビジョン情報の取得
string
ClibCellLibrary::revision() const
{
  if ( mImpl ) {
    return mImpl->revision();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief コメント情報の取得
string
ClibCellLibrary::comment() const
{
  if ( mImpl ) {
    return mImpl->comment();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 時間単位の取得
string
ClibCellLibrary::time_unit() const
{
  if ( mImpl ) {
    return mImpl->time_unit();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 電圧単位の取得
string
ClibCellLibrary::voltage_unit() const
{
  if ( mImpl ) {
    return mImpl->voltage_unit();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 電流単位の取得
string
ClibCellLibrary::current_unit() const
{
  if ( mImpl ) {
    return mImpl->current_unit();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 抵抗単位の取得
string
ClibCellLibrary::pulling_resistance_unit() const
{
  if ( mImpl ) {
    return mImpl->pulling_resistance_unit();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 容量単位の取得
//
// なぜかここだけインターフェイスが異なる．
double
ClibCellLibrary::capacitive_load_unit() const
{
  if ( mImpl ) {
    return mImpl->capacitive_load_unit();
  }
  else {
    // デフォルト値
    return 0.0;
  }
}

// @brief 容量単位文字列の取得
//
// なぜかここだけインターフェイスが異なる．
string
ClibCellLibrary::capacitive_load_unit_str() const
{
  if ( mImpl ) {
    return mImpl->capacitive_load_unit_str();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 電力単位の取得
string
ClibCellLibrary::leakage_power_unit() const
{
  if ( mImpl ) {
    return mImpl->leakage_power_unit();
  }
  else {
    // デフォルト値
    return string();
  }
}

// @brief 遅延テーブルのテンプレート数の取得
SizeType
ClibCellLibrary::lu_table_template_num() const
{
  if ( mImpl ) {
    return mImpl->lu_table_template_num();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 遅延テーブルのテンプレートの取得
const ClibLutTemplate&
ClibCellLibrary::lu_table_template(
  SizeType pos
) const
{
  if ( mImpl ) {
    return mImpl->lu_table_template(pos);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_lut_template();
  }
}

// @brief 遅延テーブルのテンプレート番号の取得
SizeType
ClibCellLibrary::lu_table_template_id(
  const char* name
) const
{
  if ( mImpl ) {
    return mImpl->lu_table_template_id(name);
  }
  else {
    // デフォルト値
    return -1;
  }
}

// @brief バスタイプの取得
// @param[in] name バスタイプ名
//
// なければ nullptr を返す．
const ClibBusType&
ClibCellLibrary::bus_type(
  const char* name
) const
{
  if ( mImpl ) {
    return mImpl->bus_type(name);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_bus_type();
  }
}

// @brief このライブラリの持つセル数の取得
SizeType
ClibCellLibrary::cell_num() const
{
  if ( mImpl ) {
    return mImpl->cell_num();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief セル情報の取得
const ClibCell&
ClibCellLibrary::cell(
  SizeType cell_id
) const
{
  if ( mImpl ) {
    return mImpl->cell(cell_id);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell();
  }
}

// @brief 名前からのセル番号の取得
SizeType
ClibCellLibrary::cell_id(
  const char* name
) const
{
  if ( mImpl ) {
    return mImpl->cell_id(name);
  }
  else {
    // デフォルト値
    return CLIB_NULLID;
  }
}

// @brief セルグループ数の取得
SizeType
ClibCellLibrary::cell_group_num() const
{
  if ( mImpl ) {
    return mImpl->cell_group_num();
  }
  else {
    return 0;
  }
}

// @brief セルグループの取得
const ClibCellGroup&
ClibCellLibrary::cell_group(
  SizeType id ///< [in] グループ番号 ( 0 <= id < group_num() )
) const
{
  if ( mImpl ) {
    return mImpl->cell_group(id);
  }
  else {
    return CiCellLibrary::error_cell_group();
  }
}

// @brief NPN同値クラス数の取得
SizeType
ClibCellLibrary::npn_class_num() const
{
  if ( mImpl ) {
    return mImpl->npn_class_num();
  }
  else {
    return 0;
  }
}

// @brief NPN同値クラスの取得
const ClibCellClass&
ClibCellLibrary::npn_class(
  SizeType id ///< [in] 同値クラス番号 ( 0 <= id < npn_class_num() )
) const
{
  if ( mImpl ) {
    return mImpl->npn_class(id);
  }
  else {
    return CiCellLibrary::error_cell_class();
  }
}

// @brief 定数0セルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::const0_func() const
{
  if ( mImpl ) {
    return mImpl->const0_func();
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_group();
  }
}

// @brief 定数1セルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::const1_func() const
{
  if ( mImpl ) {
    return mImpl->const1_func();
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_group();
  }
}

// @brief バッファセルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::buf_func() const
{
  if ( mImpl ) {
    return mImpl->buf_func();
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_group();
  }
}

// @brief インバータセルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::inv_func() const
{
  if ( mImpl ) {
    return mImpl->inv_func();
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_group();
  }
}

// @brief 単純な型のFFクラスを返す．
const ClibCellClass&
ClibCellLibrary::simple_ff_class(
  bool has_clear,
  bool has_preset
) const
{
  if ( mImpl ) {
    return mImpl->simple_ff_class(has_clear, has_preset);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_class();
  }
}

// @brief 単純な型のラッチクラスを返す．
const ClibCellClass&
ClibCellLibrary::simple_latch_class(
  bool has_clear,
  bool has_preset
) const
{
  if ( mImpl ) {
    return mImpl->simple_latch_class(has_clear, has_preset);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_cell_class();
  }
}

// @brief 総パタン数を返す．
SizeType
ClibCellLibrary::pg_pat_num() const
{
  if ( mImpl ) {
    return mImpl->pg_pat_num();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief パタンを返す．
// @param[in] id パタン番号 ( 0 <= id < pg_pat_num() )
const ClibPatGraph&
ClibCellLibrary::pg_pat(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_pat(id);
  }
  else {
    // デフォルト値
    return CiCellLibrary::error_patgraph();
  }
}

// @brief パタンの最大の入力数を得る．
SizeType
ClibCellLibrary::pg_max_input() const
{
  if ( mImpl ) {
    return mImpl->pg_max_input();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 総ノード数を返す．
SizeType
ClibCellLibrary::pg_node_num() const
{
  if ( mImpl ) {
    return mImpl->pg_node_num();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief ノードの種類を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
ClibPatType
ClibCellLibrary::pg_node_type(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_node_type(id);
  }
  else {
    // デフォルト値
    return ClibPatType::Input;
  }
}

// @brief ノードが入力ノードの時に入力番号を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
//
// 入力ノードでない場合の返り値は不定
SizeType
ClibCellLibrary::pg_input_id(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_input_id(id);
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 入力のノード番号を返す．
// @param[in] input_id 入力番号 ( 0 <= input_id < pg_input_num() )
// @return input_id の入力に対応するノードのノード番号
SizeType
ClibCellLibrary::pg_input_node(
  SizeType input_id
) const
{
  if ( mImpl ) {
    return mImpl->pg_input_node(input_id);
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 総枝数を返す．
SizeType
ClibCellLibrary::pg_edge_num() const
{
  if ( mImpl ) {
    return mImpl->pg_edge_num();
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 枝のファンイン元のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
SizeType
ClibCellLibrary::pg_edge_from(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_from(id);
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 枝のファンアウト先のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
SizeType
ClibCellLibrary::pg_edge_to(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_to(id);
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
SizeType
ClibCellLibrary::pg_edge_pos(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_pos(id);
  }
  else {
    // デフォルト値
    return 0;
  }
}

// @brief 枝の反転属性を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
bool
ClibCellLibrary::pg_edge_inv(
  SizeType id
) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_inv(id);
  }
  else {
    // デフォルト値
    return false;
  }
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
ClibCellLibrary::dump(
  ostream& s
) const
{
  if ( mImpl ) {
    return mImpl->dump(s);
  }
}

// @brief バイナリダンプされた内容を読み込む．
// @param[in] s 入力元のストリーム
void
ClibCellLibrary::restore(
  istream& s
)
{
  auto new_impl{new CiCellLibrary()};
  new_impl->restore(s);
  change_impl(new_impl);
}

END_NAMESPACE_YM_CLIB
