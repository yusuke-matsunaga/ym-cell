#ifndef CGGENLOGICSIG_H
#define CGGENLOGICSIG_H

/// @file CgGenLogicSig.h
/// @brief CgGenLogicSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "CgPolInfo.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

struct CgPinGroup;
struct CgSymInfo;

//////////////////////////////////////////////////////////////////////
/// @class CgGenLogicSig CgGenLogicSig.h "CgGenLogicSig.h"
/// @brief 一般的な論理関数のシグネチャを表すクラス
//////////////////////////////////////////////////////////////////////
class CgGenLogicSig :
  public CgSigRep
{
public:

  /// @brief コンストラクタ
  CgGenLogicSig(
    SizeType ni,                        ///< [in] 入力数
    SizeType no,                        ///< [in] 出力数
    SizeType nb,                        ///< [in] 入出力数
    const vector<TvFunc>& func_list,    ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list ///< [in] tristate条件のリスト
  );

  /// @brief デストラクタ
  ~CgGenLogicSig() = default;

  /// @brief シグネチャを作る．
  static
  unique_ptr<const CgSigRep>
  make_signature(
    SizeType ni,                        ///< [in] 入力数
    SizeType no,                        ///< [in] 出力数
    SizeType nb,                        ///< [in] 入出力数
    const vector<TvFunc>& func_list,    ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list ///< [in] tristate条件のリスト
  )
  {
    auto ptr = new CgGenLogicSig{ni, no, nb, func_list, tristate_list};
    return unique_ptr<const CgSigRep>{ptr};
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャ文字列を返す．
  string
  str() const override;

  /// @brief 変換を施した後のシグネチャを返す．
  unique_ptr<const CgSigRep>
  xform(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // CgSigRep の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 正規形への変換を求める．
  vector<ClibIOMap>
  gen_cannonical_map() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Walsh_0 を用いて出力のグループ分けを行う．
  void
  w0_refine(
    const vector<SizeType>& pos_list, ///< [in] 出力番号のリスト
    vector<CgPinGroup>& og_list,      ///< [out] 出力のグループのリスト
    vector<CgPolInfo>& opol_list      ///< [out] 出力の反転属性のリスト
  ) const;

  /// @brief 対称グループを作る．
  vector<SizeType>
  gen_symgroup(
    vector<CgSymInfo>& syminfo_list, ///< [out] 対称グループのリスト
    vector<bool>& syminv_list        ///< [out] 反転属性のリスト
  ) const;

  /// @brief Walsh_1_sum を用いて入力グループの細分化を行う．
  void
  w1sum_refine(
    const vector<SizeType>& src_list,
    const vector<CgPolInfo>& opol_list,
    vector<CgPinGroup>& ig_list,
    vector<CgPolInfo>& ipol_list
  ) const;

  /// @brief 入力の対称性を調べる．
  bool
  check_sym(
    SizeType i1,
    SizeType i2,
    bool inv
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力数
  SizeType mNi;

  // 出力数
  SizeType mNo;

  // 入出力数
  SizeType mNb;

  // 論理関数
  vector<TvFunc> mFuncList;

  // tristate 条件
  vector<TvFunc> mTristateList;

};

END_NAMESPACE_YM_CLIB

#endif // CGGENLOGICSIG_H
