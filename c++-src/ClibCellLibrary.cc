
/// @file ClibCellLibrary.cc
/// @brief ClibCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellLibrary.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス ClibCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
//
// 空の状態で初期化される．
ClibCellLibrary::ClibCellLibrary() :
  mImpl{nullptr}
{
}

// @brief コピーコンストラクタ
// @param[in] src コピー元のオブジェクト
//
// '浅い'コピーを行う．
ClibCellLibrary::ClibCellLibrary(const ClibCellLibrary& src) :
  mImpl{nullptr}
{
  change_impl(src.mImpl);
}

// @brief 代入演算子
// @param[in] src コピー元のオブジェクト
const ClibCellLibrary&
ClibCellLibrary::operator=(const ClibCellLibrary& src)
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
ClibCellLibrary::change_impl(CiCellLibrary* new_impl)
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
// @param[in] filename ファイル名
// @return 読み込みが成功したら true を返す．
bool
ClibCellLibrary::read_mislib(const string& filename)
{
  CiCellLibrary* new_impl = new CiCellLibrary();
  bool stat = new_impl->read_mislib(filename);
  if ( stat ) {
    change_impl(new_impl);
  }
  return stat;
}

// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
// @param[in] filename ファイル名
// @return 読み込みが成功したら true を返す．
bool
ClibCellLibrary::read_mislib(const char* filename)
{
  return read_mislib(string(filename));
}

// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
// @param[in] filename ファイル名
// @return 読み込みが成功したら true を返す．
bool
ClibCellLibrary::read_liberty(const string& filename)
{
  CiCellLibrary* new_impl = new CiCellLibrary();
  bool stat = new_impl->read_liberty(filename);
  if ( stat ) {
    change_impl(new_impl);
  }
  return stat;
}

// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
// @param[in] filename ファイル名
// @return 読み込みが成功したら true を返す．
bool
ClibCellLibrary::read_liberty(const char* filename)
{
  return read_liberty(string(filename));
}

// @brief 名前の取得
string
ClibCellLibrary::name() const
{
  if ( mImpl ) {
    return mImpl->name();
  }
  return string();
}

// @brief テクノロジの取得
// 返り値は
// - kClibTechCmos
// - kClibTechFpga
// のどちらか
ClibTechnology
ClibCellLibrary::technology() const
{
  if ( mImpl ) {
    return mImpl->technology();
  }
  // デフォルトは CMOS
  return ClibTechnology::cmos;
}

// @brief 遅延モデルの取得
// 返り値は
// - kClibDelayGenericCmos
// - kClibDelayTableLookup
// - kClibDelayPiecewiseCmos
// - kClibDelayCmos2
// - kClibDelayDcm
// のいずれか
ClibDelayModel
ClibCellLibrary::delay_model() const
{
  if ( mImpl ) {
    return mImpl->delay_model();
  }
  // デフォルト値
  return ClibDelayModel::GenericCmos;
}

// @brief バス命名規則の取得
string
ClibCellLibrary::bus_naming_style() const
{
  if ( mImpl ) {
    return mImpl->bus_naming_style();
  }
  // デフォルト値
  return string();
}

// @brief 日付情報の取得
string
ClibCellLibrary::date() const
{
  if ( mImpl ) {
    return mImpl->date();
  }
  // デフォルト値
  return string();
}

// @brief リビジョン情報の取得
string
ClibCellLibrary::revision() const
{
  if ( mImpl ) {
    return mImpl->revision();
  }
  // デフォルト値
  return string();
}

// @brief コメント情報の取得
string
ClibCellLibrary::comment() const
{
  if ( mImpl ) {
    return mImpl->comment();
  }
  // デフォルト値
  return string();
}

// @brief 時間単位の取得
string
ClibCellLibrary::time_unit() const
{
  if ( mImpl ) {
    return mImpl->time_unit();
  }
  // デフォルト値
  return string();
}

// @brief 電圧単位の取得
string
ClibCellLibrary::voltage_unit() const
{
  if ( mImpl ) {
    return mImpl->voltage_unit();
  }
  // デフォルト値
  return string();
}

// @brief 電流単位の取得
string
ClibCellLibrary::current_unit() const
{
  if ( mImpl ) {
    return mImpl->current_unit();
  }
  // デフォルト値
  return string();
}

// @brief 抵抗単位の取得
string
ClibCellLibrary::pulling_resistance_unit() const
{
  if ( mImpl ) {
    return mImpl->pulling_resistance_unit();
  }
  // デフォルト値
  return string();
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
  // デフォルト値
  return 0.0;
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
  // デフォルト値
  return string();
}

// @brief 電力単位の取得
string
ClibCellLibrary::leakage_power_unit() const
{
  if ( mImpl ) {
    return mImpl->leakage_power_unit();
  }
  // デフォルト値
  return string();
}

// @brief 遅延テーブルのテンプレートのリストの取得
const ClibLutTemplateList&
ClibCellLibrary::lu_table_template_list() const
{
  if ( mImpl ) {
    return mImpl->lu_table_template_list();
  }

  // ClibLutTemplateList のデフォルト用オブジェクト
  static ClibLutTemplateList sLutTemplateList;

  // デフォルト値
  return sLutTemplateList;
}

// @brief 遅延テーブルのテンプレート数の取得
int
ClibCellLibrary::lu_table_template_num() const
{
  if ( mImpl ) {
    return mImpl->lu_table_template_num();
  }
  // デフォルト値
  return 0;
}

// @brief 遅延テーブルのテンプレートの取得
// @param[in] pos 位置番号 ( 0 <= pos < lu_table_template_num() )
const ClibLutTemplate&
ClibCellLibrary::lu_table_template(int pos) const
{
  if ( mImpl ) {
    return mImpl->lu_table_template(pos);
  }

  // デフォルト値
  return CiCellLibrary::error_lut_template();
}

// @brief 遅延テーブルのテンプレート番号の取得
// @param[in] name テンプレート名
//
// なければ -1 を返す．
int
ClibCellLibrary::lu_table_template_id(const char* name) const
{
  if ( mImpl ) {
    return mImpl->lu_table_template_id(name);
  }
  // デフォルト値
  return -1;
}

// @brief バスタイプの取得
// @param[in] name バスタイプ名
//
// なければ nullptr を返す．
const ClibBusType&
ClibCellLibrary::bus_type(const char* name) const
{
  if ( mImpl ) {
    return mImpl->bus_type(name);
  }

  // デフォルト値
  return CiCellLibrary::error_bus_type();
}

// @brief このライブラリの持つセルのリストの取得
const ClibCellList&
ClibCellLibrary::cell_list() const
{
  if ( mImpl ) {
    return mImpl->cell_list();
  }

  // ClibCellList のデフォルト用オブジェクト
  static ClibCellList sCellList;

  // デフォルト値
  return sCellList;
}

// @brief このライブラリの持つセル数の取得
int
ClibCellLibrary::cell_num() const
{
  if ( mImpl ) {
    return mImpl->cell_list().num();
  }
  // デフォルト値
  return 0;
}

// @brief セル情報の取得
// @param[in] cell_id セル番号 ( 0 <= cell_id < cell_num() )
// @return 該当するセル情報を返す．
const ClibCell&
ClibCellLibrary::cell(int cell_id) const
{
  if ( mImpl ) {
    return mImpl->cell(cell_id);
  }

  // デフォルト値
  return CiCellLibrary::error_cell();
}

// @brief 名前からのセル番号の取得
int
ClibCellLibrary::cell_id(const char* name) const
{
  if ( mImpl ) {
    return mImpl->cell_id(name);
  }
  // デフォルト値
  return -1;
}

// @brief 名前からのセル番号の取得
int
ClibCellLibrary::cell_id(const string& name) const
{
  if ( mImpl ) {
    return mImpl->cell_id(name);
  }
  // デフォルト値
  return -1;
}

// @brief セルグループのリストを返す．
const ClibCellGroupList&
ClibCellLibrary::group_list() const
{
  if ( mImpl ) {
    return mImpl->group_list();
  }

  // ClibCellGroupList のデフォルト用オブジェクト
  static ClibCellGroupList sCellGroupList;

  // デフォルト値
  return sCellGroupList;
}

// @brief NPN同値クラスのリストを返す．
const ClibCellClassList&
ClibCellLibrary::npn_class_list() const
{
  if ( mImpl ) {
    return mImpl->npn_class_list();
  }

  // ClibCellClassList のデフォルト用オブジェクト
  static ClibCellClassList sCellClassList;

  // デフォルト値
  return sCellClassList;
}

// @brief 定数0セルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::const0_func() const
{
  if ( mImpl ) {
    return mImpl->const0_func();
  }

  // デフォルト値
  return CiCellLibrary::error_cell_group();
}

// @brief 定数1セルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::const1_func() const
{
  if ( mImpl ) {
    return mImpl->const1_func();
  }

  // デフォルト値
  return CiCellLibrary::error_cell_group();
}

// @brief バッファセルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::buf_func() const
{
  if ( mImpl ) {
    return mImpl->buf_func();
  }
  // デフォルト値
  return CiCellLibrary::error_cell_group();
}

// @brief インバータセルのグループを返す．
const ClibCellGroup&
ClibCellLibrary::inv_func() const
{
  if ( mImpl ) {
    return mImpl->inv_func();
  }
  // デフォルト値
  return CiCellLibrary::error_cell_group();
}

// @brief 単純な型のFFクラスを返す．
// @param[in] has_clear クリア端子を持つとき true にする．
// @param[in] has_preset プリセット端子を持つとき true にする．
//
// 該当するセルがないときでも空のセルクラスが返される．
const ClibCellClass&
ClibCellLibrary::simple_ff_class(bool has_clear,
				 bool has_preset) const
{
  if ( mImpl ) {
    return mImpl->simple_ff_class(has_clear, has_preset);
  }
  // デフォルト値
  return CiCellLibrary::error_cell_class();
}

// @brief 単純な型のラッチクラスを返す．
// @param[in] has_clear クリア端子を持つとき true にする．
// @param[in] has_preset プリセット端子を持つとき true にする．
//
// 該当するセルがないときでも空のセルクラスが返される．
const ClibCellClass&
ClibCellLibrary::simple_latch_class(bool has_clear,
				    bool has_preset) const
{
  if ( mImpl ) {
    return mImpl->simple_latch_class(has_clear, has_preset);
  }
  // デフォルト値
  return CiCellLibrary::error_cell_class();
}

// @brief 総パタン数を返す．
int
ClibCellLibrary::pg_pat_num() const
{
  if ( mImpl ) {
    return mImpl->pg_pat_num();
  }
  // デフォルト値
  return 0;
}

// @brief パタンを返す．
// @param[in] id パタン番号 ( 0 <= id < pg_pat_num() )
const ClibPatGraph&
ClibCellLibrary::pg_pat(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_pat(id);
  }

  // デフォルト値
  return CiCellLibrary::error_patgraph();
}

// @brief パタンの最大の入力数を得る．
int
ClibCellLibrary::pg_max_input() const
{
  if ( mImpl ) {
    return mImpl->pg_max_input();
  }
  // デフォルト値
  return 0;
}

// @brief 総ノード数を返す．
int
ClibCellLibrary::pg_node_num() const
{
  if ( mImpl ) {
    return mImpl->pg_node_num();
  }
  // デフォルト値
  return 0;
}

// @brief ノードの種類を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
ClibPatType
ClibCellLibrary::pg_node_type(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_node_type(id);
  }
  // デフォルト値
  return ClibPatType::Input;
}

// @brief ノードが入力ノードの時に入力番号を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
//
// 入力ノードでない場合の返り値は不定
int
ClibCellLibrary::pg_input_id(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_input_id(id);
  }
  // デフォルト値
  return 0;
}

// @brief 入力のノード番号を返す．
// @param[in] input_id 入力番号 ( 0 <= input_id < pg_input_num() )
// @return input_id の入力に対応するノードのノード番号
int
ClibCellLibrary::pg_input_node(int input_id) const
{
  if ( mImpl ) {
    return mImpl->pg_input_node(input_id);
  }
  // デフォルト値
  return 0;
}

// @brief 総枝数を返す．
int
ClibCellLibrary::pg_edge_num() const
{
  if ( mImpl ) {
    return mImpl->pg_edge_num();
  }
  // デフォルト値
  return 0;
}

// @brief 枝のファンイン元のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
int
ClibCellLibrary::pg_edge_from(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_from(id);
  }
  // デフォルト値
  return 0;
}

// @brief 枝のファンアウト先のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
int
ClibCellLibrary::pg_edge_to(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_to(id);
  }
  // デフォルト値
  return 0;
}

// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
int
ClibCellLibrary::pg_edge_pos(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_pos(id);
  }
  // デフォルト値
  return 0;
}

// @brief 枝の反転属性を返す．
// @param[in] id 枝番号 ( 0 <= id < edge_num() )
bool
ClibCellLibrary::pg_edge_inv(int id) const
{
  if ( mImpl ) {
    return mImpl->pg_edge_inv(id);
  }
  // デフォルト値
  return false;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
ClibCellLibrary::dump(ostream& s) const
{
  if ( mImpl ) {
    return mImpl->dump(s);
  }
}

// @brief バイナリダンプされた内容を読み込む．
// @param[in] s 入力元のストリーム
void
ClibCellLibrary::restore(istream& s)
{
  CiCellLibrary* new_impl = new CiCellLibrary();
  new_impl->restore(s);
  change_impl(new_impl);
}

END_NAMESPACE_YM_CLIB
