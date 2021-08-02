
/// @file LibComp.cc
/// @brief LibComp の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/LibComp.h"
#include "lc/LcClass.h"
#include "lc/LcGroup.h"
#include "lc/LcPatNode.h"
#include "lc/LcPatHandle.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiCell.h"
#include "ym/Expr.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

BEGIN_NONAMESPACE

// 論理式の変数を map にしたがって変換する．
Expr
xform_expr(
  const Expr& expr,
  const NpnMapM& map
)
{
  auto ni = map.input_num();
  auto no = map.output_num();
  ASSERT_COND( no == 1 );
  unordered_map<VarId, Expr> vlm;
  for ( auto i = 0; i < ni; ++ i ) {
    VarId src_var(i);
    NpnVmap imap = map.imap(src_var);
    VarId dst_var = imap.var();
    Expr expr = Expr::make_literal(dst_var, imap.inv());
    vlm[src_var] = expr;
  }
  Expr cexpr = expr.compose(vlm);
  if ( map.omap(VarId(0)).inv() ) {
    cexpr = ~cexpr;
  }
  return cexpr;
}

// has_q, has_xq, has_clear, has_preset をエンコードする．
inline
SizeType
encode(
  bool has_q,
  bool has_xq,
  bool has_clear,
  bool has_preset
)
{
  SizeType ans = 0;
  if ( has_q ) {
    if ( has_xq ) {
      ans = 2;
    }
    else {
      ans = 0;
    }
  }
  else {
    ASSERT_COND( has_xq );
    ans = 1;
  }
  ans <<= 2;
  if ( has_clear ) {
    ans |= 1U;
  }
  if ( has_preset ) {
    ans |= 2U;
  }
  return ans;
}

// 整数から has_q, has_xq, has_clear, has_preset をデコードする．
inline
void
decode(
  SizeType val,
  bool& has_q,
  bool& has_xq,
  bool& has_clear,
  bool& has_preset)
{
  SizeType val1 = val >> 2;
  switch ( val1 ) {
  case 0:
    has_q = true;
    has_xq = false;
    break;
  case 1:
    has_q = false;
    has_xq = true;
    break;
  case 2:
    has_q = true;
    has_xq = true;
    break;
  }
  has_clear = static_cast<bool>((val >> 0) & 1);
  has_preset = static_cast<bool>((val >> 1) & 1);
}

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス LibComp
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LibComp::LibComp()
{
}

// @brief デストラクタ
LibComp::~LibComp()
{
}

// @brief パタングラフの情報を取り出す．
const LcPatMgr&
LibComp::pat_mgr() const
{
  return mPatMgr;
}

// @brief セルのグループ化，クラス化を行う．
// @param[in] cell_list セルのリスト
void
LibComp::compile(
  const vector<unique_ptr<CiCell>>& cell_list
)
{
  mGroupList.clear();
  mGroupMap.clear();

  mClassList.clear();
  mClassMap.clear();

  // パタンマネージャを初期化
  mPatMgr.init();

  // 論理型の基本タイプを登録
  _logic_init();

  // FFの基本タイプを登録
  _ff_init();

  // ラッチの基本タイプを登録
  _latch_init();

  // セルを登録する．
  for ( auto& p: cell_list ) {
    auto cell = p.get();
    auto& group = _find_group(cell);
    group.add_cell(cell);
  }
}

// @brief セルグループの数を返す．
SizeType
LibComp::group_num() const
{
  return mGroupList.size();
}

// @brief セルグループを返す．
// @param[in] id グループ番号 ( 0 <= id < group_num() )
const LcGroup&
LibComp::group(
  SizeType id
) const
{
  ASSERT_COND( id >= 0 && id < group_num() );
  return *mGroupList[id];
}

// @brief NPN同値クラスの数を返す．
SizeType
LibComp::npn_class_num() const
{
  return mClassList.size();
}

// @brief NPN同値クラスを返す．
// @param[in] id クラス番号 ( 0 <= id < npn_class_num() )
const LcClass&
LibComp::npn_class(
  SizeType id
) const
{
  ASSERT_COND( id >= 0 && id < npn_class_num() );
  return *mClassList[id];
}

// @brief 定義済みの論理グループ番号を返す．
// @param[in] id 番号
// - 0: 定数0
// - 1: 定数1
// - 2: バッファ
// - 3: インバーター
SizeType
LibComp::logic_group(
  SizeType id
) const
{
  ASSERT_COND( id >= 0 && id < 4 );
  return mLogicGroup[id];
}

// @brief 定義済みのFFクラス番号を返す．
// @param[in] has_q Q端子の有無
// @param[in] has_xq 反転Q端子の有無
// @param[in] has_clear クリア端子の有無
// @param[in] has_preset プリセット端子の有無
//
// has_q == false && has_xq == false は不適
SizeType
LibComp::ff_class(
  bool has_q,
  bool has_xq,
  bool has_clear,
  bool has_preset
) const
{
  auto i = encode(has_q, has_xq, has_clear, has_preset);
  return mFFClass[i];
}

// @brief 定義済みのラッチクラス番号を返す．
// @param[in] has_q Q端子の有無
// @param[in] has_xq 反転Q端子の有無
// @param[in] has_clear クリア端子の有無
// @param[in] has_preset プリセット端子の有無
//
// has_q == false && has_xq == false は不適
SizeType
LibComp::latch_class(
  bool has_q,
  bool has_xq,
  bool has_clear,
  bool has_preset
)
{
  auto i = encode(has_q, has_xq, has_clear, has_preset);
  return mLatchClass[i];
}

// @brief 論理セルの基本タイプを登録する．
void
LibComp::_logic_init()
{
  { // 定数0グループの登録
    LcGroup& func0 = _find_group(Expr::make_zero());
    mLogicGroup[0] = func0.id();
  }
  { // 定数1グループの登録
    LcGroup& func1 = _find_group(Expr::make_one());
    mLogicGroup[1] = func1.id();
  }
  { // バッファグループの登録
    Expr expr = Expr::make_posi_literal(VarId(0));
    LcGroup& func2 = _find_group(expr);
    mLogicGroup[2] = func2.id();
  }
  { // インバーターグループの登録
    Expr expr = Expr::make_nega_literal(VarId(0));
    LcGroup& func3 = _find_group(expr);
    mLogicGroup[3] = func3.id();
  }

  // AND2 〜 AND8 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4, 5, 6, 7, 8} ) {
    Expr and_expr = Expr::make_posi_literal(VarId(0));
    for ( auto i = 1; i < ni; ++ i ) {
      and_expr &= Expr::make_posi_literal(VarId(i));
    }
    _find_group(and_expr);
  }

  // XOR2 〜 XOR4 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4} ) {
    Expr xor_expr = Expr::make_posi_literal(VarId(0));
    for ( int i = 1; i < ni; ++ i ) {
      xor_expr ^= Expr::make_posi_literal(VarId(i));
    }
    _find_group(xor_expr);
  }

  // MUX2 のシグネチャを登録しておく．
  {
    Expr lit0 = Expr::make_posi_literal(VarId(0));
    Expr lit1 = Expr::make_posi_literal(VarId(1));
    Expr lit2 = Expr::make_posi_literal(VarId(2));
    Expr mux2_expr = lit0 & ~lit2 | lit1 & lit2;
    _find_group(mux2_expr);
  }

  // MUX4 のシグネチャを登録しておく．
  {
    Expr lit0 = Expr::make_posi_literal(VarId(0));
    Expr lit1 = Expr::make_posi_literal(VarId(1));
    Expr lit2 = Expr::make_posi_literal(VarId(2));
    Expr lit3 = Expr::make_posi_literal(VarId(3));
    Expr lit4 = Expr::make_posi_literal(VarId(4));
    Expr lit5 = Expr::make_posi_literal(VarId(5));
    Expr mux4_expr =
      lit0 & ~lit4 & ~lit5 |
      lit1 &  lit4 & ~lit5 |
      lit2 & ~lit4 &  lit5 |
      lit3 &  lit4 &  lit5;
    _find_group(mux4_expr);
  }

  // MUX8 のシグネチャを登録しておく．
  if ( 0 ) {
    Expr lit0 = Expr::make_posi_literal(VarId(0));
    Expr lit1 = Expr::make_posi_literal(VarId(1));
    Expr lit2 = Expr::make_posi_literal(VarId(2));
    Expr lit3 = Expr::make_posi_literal(VarId(3));
    Expr lit4 = Expr::make_posi_literal(VarId(4));
    Expr lit5 = Expr::make_posi_literal(VarId(5));
    Expr lit6 = Expr::make_posi_literal(VarId(6));
    Expr lit7 = Expr::make_posi_literal(VarId(7));
    Expr lit8 = Expr::make_posi_literal(VarId(8));
    Expr lit9 = Expr::make_posi_literal(VarId(9));
    Expr lit10 = Expr::make_posi_literal(VarId(10));
    Expr mux8_expr =
      lit0 & ~lit8 & ~lit9 & ~lit10 |
      lit1 &  lit8 & ~lit9 & ~lit10 |
      lit2 & ~lit8 &  lit9 & ~lit10 |
      lit3 &  lit8 &  lit9 & ~lit10 |
      lit4 & ~lit8 & ~lit9 &  lit10 |
      lit5 &  lit8 & ~lit9 &  lit10 |
      lit6 & ~lit8 &  lit9 &  lit10 |
      lit7 &  lit8 &  lit9 &  lit10;
    _find_group(mux8_expr);
  }
}

// @brief FFセルの基本タイプを登録する．
void
LibComp::_ff_init()
{
  for ( auto i = 0; i < 12; ++ i ) {
    bool has_q;
    bool has_xq;
    bool has_clear;
    bool has_preset;
    decode(i, has_q, has_xq, has_clear, has_preset);

    LcSignature sig(LcType::FF, has_q, has_xq, has_clear, has_preset);
    LcGroup& group = _find_group(sig);
    LcClass& cclass = group.parent();
    mFFClass[i] = cclass.id();
  }
}

// @brief ラッチセルの基本タイプを登録する．
void
LibComp::_latch_init()
{
  for ( auto i = 0; i < 12; ++ i ) {
    bool has_q;
    bool has_xq;
    bool has_clear;
    bool has_preset;
    decode(i, has_q, has_xq, has_clear, has_preset);

    LcSignature sig(LcType::Latch, has_q, has_xq, has_clear, has_preset);
    LcGroup& group = _find_group(sig);
    LcClass& cclass = group.parent();
    mLatchClass[i] = cclass.id();
  }
}

// @brief セルに対応する LcGroup を求める．
LcGroup&
LibComp::_find_group(
  CiCell* cell
)
{
  if ( !cell->has_logic() || cell->output_num2() == 0 ) {
    // ひとつでも論理式を持たない出力があるセルは独立したグループとなる．
    auto fgroup = _new_group();

    auto ni = cell->input_num2();
    auto no = cell->output_num2();
    auto fclass = _new_class(LcSignature());
    NpnMapM xmap;
    xmap.set_identity(ni, no);
    fclass->add_group(fgroup, xmap);
    return *fgroup;
  }
  else if ( cell->is_logic() &&
	    cell->output_num2() == 1 &&
	    !cell->has_tristate(0) ) {
    // 1出力の単純なセルの場合，論理式からグループを求める．
    return _find_group(cell->logic_expr(0));
  }
  else {
    // セルのシグネチャ関数を作る．
    LcSignature sig(cell);

    // sig に対するセルグループを求める．
    return _find_group(sig);
  }
}

// @brief シグネチャに対応する LcGroup を求める．
// @param[in] sig シグネチャ
//
// なければ新規に作る．
LcGroup&
LibComp::_find_group(
  const LcSignature& sig
)
{
  string sig_str = sig.str();
  if ( mGroupMap.count(sig_str) > 0 ) {
    auto fgid = mGroupMap.at(sig_str);
    // 既に登録されていた．
    return *mGroupList[fgid];
  }

  // なかったので新たに作る．
  auto fgroup = _new_group();
  mGroupMap.emplace(sig_str, fgroup->id());

  // 代表関数を求める．
  // 今は単一出力の論理型でトライステート状態を
  // 持たない場合のみNPN同値類を考える．
  // それ以外の場合は Group = NpnClass となる．
  LcSignature rep_sig{sig};
  NpnMapM xmap(sig.input_num(), sig.output_num());
  if ( sig.output_num() == 1 &&
       sig.type() == LcType::Logic &&
       !sig.is_tristate(0) ) {
    TvFunc f1 = sig.output_func(0);
    NpnMap xmap1 = f1.npn_cannonical_map();
    rep_sig = LcSignature(sig, xmap1);
    xmap = NpnMapM(xmap1);
  }
  string rep_sig_str = rep_sig.str();
  LcClass* fclass = nullptr;
  if ( mClassMap.count(rep_sig_str) > 0 ) {
    auto fcid = mClassMap.at(rep_sig_str);
    // 登録されていた．
    fclass = mClassList[fcid].get();
  }
  else {
    // まだ登録されていない．
    fclass = _new_class(rep_sig);
    mClassMap.emplace(rep_sig_str, fclass->id());
  }

  // グループを追加する．
  fclass->add_group(fgroup, xmap);

  return *fgroup;
}

// @brief 論理式に対応する LcGroup を求める．
// @param[in] expr 論理式
//
// こちらは1出力の論理セル用
LcGroup&
LibComp::_find_group(
  const Expr& expr
)
{
  LcSignature sig(expr);
  LcGroup& fgroup = _find_group(sig);

  // expr からパタングラフを作り登録する．
  _reg_expr(expr, fgroup);

  return fgroup;
}

// @brief 新しいグループを作る．
LcGroup*
LibComp::_new_group()
{
  auto new_id = mGroupList.size();
  auto fgroup = new LcGroup(new_id);
  mGroupList.push_back(unique_ptr<LcGroup>{fgroup});

  return fgroup;
}

// @brief 新しいクラスを作る．
// @param[in] rep_sig 代表シグネチャ
LcClass*
LibComp::_new_class(
  const LcSignature& rep_sig
)
{
  auto new_id = mClassList.size();
  LcClass* fclass = new LcClass(new_id, rep_sig);
  mClassList.push_back(unique_ptr<LcClass>{fclass});
  fclass->mIdmapList = _find_idmap_list(rep_sig);

  return fclass;
}

// @brief expr から生成されるパタンを登録する．
void
LibComp::_reg_expr(
  const Expr& expr,     ///< [in] 論理式
  const LcGroup& fgroup ///< [in] expr の属している機能グループ
)
{
  const LcClass& fclass = fgroup.parent();

  // fclass->rep_func() を用いる理由は論理式に現れる変数が
  // 真のサポートとは限らないから

  auto ni = fclass.rep_sig().input_num();

  if ( ni <= 1 ) {
    // 定数関数およびバッファ，インバータは別に処理する．
    return;
  }

  // expr を変換したパタンを登録する．
  Expr cexpr = xform_expr(expr, fgroup.map());
  ASSERT_COND( !cexpr.is_constant() );

  if ( ni <= 8 ) {
    mPatMgr.reg_pat(cexpr, fclass.id());
  }
  else {
    // 登録できなかったことを通知する？
  }
}

// @brief 同位体変換リストを求める．
vector<NpnMapM>
LibComp::_find_idmap_list(
  const LcSignature& sig ///< [in] シグネチャ
)
{
#warning "TODO: 未完"
  return vector<NpnMapM>{};
}

// @brief グラフ構造全体をダンプする．
// @param[in] s 出力先のストリーム
void
LibComp::display(
  ostream& s
) const
{
  // セルグループの情報を出力する．
  s << "*** Cell Group BEGIN ***" << endl;
  for ( auto i = 0; i < group_num(); ++ i ) {
    const LcGroup& group1 = group(i);
    ASSERT_COND( group1.id() == i );
    s << "GROUP#" << i
      << ": CLASS#" << group1.parent().id()
      << ": " << group1.map()
      << endl;
    s << "  CELL:";
    for ( auto cell: group1.cell_list() ) {
      s << " " << cell->name();
    }
    s << endl;
  }
  s << "*** Cell Group END ***" << endl
    << endl;

  // NPN同値クラスの情報を出力する．
  s << "*** NPN Class BEGIN ***" << endl;
  for ( auto i = 0; i < npn_class_num(); ++ i ) {
    const LcClass& cclass = npn_class(i);
    ASSERT_COND( cclass.id() == i );
    s << "CLASS#" << i << ": ";
#warning "TODO: 未完"
    //cclass->rep_sig().print(s, 2);
    s << endl;
    s << "  equivalence = ";
    for ( auto group: cclass.group_list()) {
      s << " GROUP#" << group->id();
    }
    s << endl;
  }
  s << "*** NPN Class END ***" << endl
    << endl;

  // パタングラフの情報を出力する．
  mPatMgr.display(s);
}

END_NAMESPACE_YM_CLIB_LIBCOMP
