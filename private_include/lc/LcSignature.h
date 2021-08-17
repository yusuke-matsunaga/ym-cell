#ifndef LCSIGNATURE_H
#define LCSIGNATURE_H

/// @file LcSignature.h
/// @brief LcSignature のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcSignature LcSignature.h "LcSignature.h"
/// @brief セルの機能を表すシグネチャ
///
/// 基本的には各出力の機能を表す論理関数だが，FF,ラッチの場合が面倒．
/// 外部インターフェイスとしては2つのシグネチャが等しいかの比較と
/// ハッシュ関数用のハッシュ値生成ができればよい．
/// ただし，入力と出力の順序入れ替えおよび極性反転を行なうNPN変換
/// に対応する必要がある．
///
/// 具体的には
/// - 組み合わせ論理
/// - FF
/// - ラッチ
/// の3種類に分けて考える．
///
/// 組み合わせ論理の場合に各出力に対して
/// - 機能を表す論理関数
/// - トライステート条件を表す論理関数
/// を持つ．
/// ともに入力変数の番号はセルの入力ピン番号に一致する．
/// トライステート条件を表す論理関数はその関数の出力が1の時に
/// 出力がトライステートになるものとする．
/// トライステートにならない出力の場合，トラーステート条件は
/// 恒偽関数となる．
/// 場合によっては入力変数として現れない入力ピンや出力の機能が
/// 定義されていない出力ピンがある場合もある．
///
/// FF の場合には
/// - 出力のタイプ( q のみ，xq のみ，q と xq )
/// - クロックエッジを表す論理関数
/// - 次状態関数
/// - クリア条件を表す論理関数(もしあれば)
/// - プリセット条件を表す論理関数(もしあれば)
///
/// ラッチの場合には
/// - 出力のタイプ( q のみ，xq のみ，q と xq )
/// - イネーブルを表す論理関数
/// - データ入力を表す論理関数
/// - クリア条件を表す論理関数(もしあれば)
/// - プリセット条件を表す論理関数(もしあれば)
///
/// FFとラッチの場合，入力変数番号0番は内部状態 IQ を表す．
/// IQN は常に IQ の否定なので変数としては用意しない．
/// 以降，clock, data, clear, preset が続く．
//////////////////////////////////////////////////////////////////////
class LcSignature
{
public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  LcSignature() = default;

  /// @brief コピーコンストラクタ
  LcSignature(
    const LcSignature& src ///< [in] コピー元のオブジェクト
  ) = default;

  /// @brief 変換付きのコピーコンストラクタ
  ///
  /// この形式は単一出力のトライステートなしの論理型のみ
  LcSignature(
    const LcSignature& src, ///< [in] コピー元のオブジェクト
    const NpnMap& xmap      ///< [in] 変換マップ
  );

  /// @brief 1出力の論理セルのシグネチャを作るコンストラクタ
  LcSignature(
    const Expr& expr ///< [in] 論理式
  );

  /// @brief 単純なFFセル/ラッチセルのシグネチャを作るコンストラクタ
  ///
  /// type == Type::Logic は不適
  /// has_q == false && has_xq == false は不適
  LcSignature(
    LcType type,    ///< [in] 種類 (Type::FF/Type::Latch)
    bool has_q,     ///< [in] Q出力の有無
    bool has_xq,    ///< [in] 反転Q出力の有無
    bool has_clear, ///< [in] クリア端子の有無
    bool has_preset ///< [in] プリセット端子の有無
  );

  /// @brief セルを指定したコンストラクタ
  LcSignature(
    const ClibCell* cell ///< [in] セル
  );

  /// @brief デストラクタ
  ~LcSignature() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を返す．
  LcType
  type() const
  {
    auto b0 = mTypeBits[0];
    auto b1 = mTypeBits[1];
    return static_cast<LcType>(b0 | (b1 << 1));
  }

  /// @brief 入力数
  SizeType
  input_num() const
  {
    return mInputNum;
  }

  /// @brief 出力数
  SizeType
  output_num() const
  {
    return mOutputNum;
  }

  /// @brief クロック/イネーブルの論理関数を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  /// ラッチの時は enable を表す論理関数を返す．
  TvFunc
  clock() const
  {
    return mClockFunc;
  }

  /// @brief 次状態関数を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  /// ラッチの時は data_in を表す論理関数を返す．
  TvFunc
  next_state() const
  {
    return mNextStateFunc;
  }

  /// @brief クリア条件を持つ時に true を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  bool
  has_clear() const
  {
    return mTypeBits[2];
  }

  /// @brief クリア条件を表す論理関数を返す．
  ///
  /// has_clear() == true の時のみ意味を持つ．
  TvFunc
  clear_func() const
  {
    return mClearFunc;
  }

  /// @brief プリセット条件を持つ時に true を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  bool
  has_preset() const
  {
    return mTypeBits[3];
  }

  /// @brief プリセット条件を表す論理関数を返す．
  ///
  /// has_preset() == true の時のみ意味を持つ．
  TvFunc
  preset_func() const
  {
    return mPresetFunc;
  }

  /// @brief 論理式を持つ時に true を返す．
  bool
  has_logic(
    SizeType opos ///< [in] 出力位置 ( 0 <= opos < output_num() )
  ) const
  {
    ASSERT_COND( opos < output_num() );
    return mOutputBits[opos][0];
  }

  /// @brief 出力の論理関数を返す．
  ///
  /// has_state_var() == true の時は変数の数が input_num() + 2 となる．
  TvFunc
  output_func(
    SizeType opos ///< [in] 出力位置 ( 0 <= opos < output_num() )
  ) const
  {
    ASSERT_COND( opos < output_num() );
    return mOutputFunc[opos];
  }

  /// @brief tristate 条件を持つ時に true を返す．
  bool
  is_tristate(
    SizeType opos ///< [in] 出力位置 ( 0 <= opos < output_num() )
  ) const
  {
    ASSERT_COND( opos < output_num() );
    return mOutputBits[opos][1];
  }

  /// @brief tristate 条件を返す．
  ///
  /// is_tristate(opos) == false の時の値は不定
  TvFunc
  tristate_func(
    SizeType opos ///< [in] 出力位置 ( 0 <= opos < output_num() )
  ) const
  {
    ASSERT_COND( opos < output_num() );
    return mTristateFunc[opos];
  }

  /// @brief 内容を表す文字列を作る．
  string
  str() const;

  /// @brief 等価比較演算子
  bool
  operator==(
    const LcSignature& right ///< [in] 比較対象のオペランド
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Logic タイプにセットする．
  void
  set_Logic()
  {
    mTypeBits.set(0, 0);
    mTypeBits.set(1, 0);
  }

  /// @brief FF タイプにセットする．
  void
  set_FF()
  {
    mTypeBits.set(0, 0);
    mTypeBits.set(1, 1);
  }

  /// @brief Latch タイプにセットする．
  void
  set_Latch()
  {
    mTypeBits.set(0, 1);
    mTypeBits.set(1, 1);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 種類とクリア端子，プリセット端子のフラグを組み合わせたもの
  // 0-1: タイプ
  // 2: クリア端子
  // 3: プリセット端子
  bitset<4> mTypeBits{0};

  // 入力ピン数
  SizeType mInputNum{0};

  // 出力ピン数
  SizeType mOutputNum{0};

  // 論理式を持つかどうかのフラグと tristate 条件を持つかどうかのフラグの配列
  // 要素数は mOutputNum
  vector<bitset<2>> mOutputBits;

  // クロックの論理関数
  TvFunc mClockFunc;

  // 次状態関数
  TvFunc mNextStateFunc;

  // クリア条件の論理関数
  TvFunc mClearFunc;

  // プリセット条件の論理関数
  TvFunc mPresetFunc;

  // 出力の論理関数の配列
  // 要素数は mOutputNum
  vector<TvFunc> mOutputFunc;

  // 出力の tristate 条件の関数の配列
  // 要素数は mOutputNum
  vector<TvFunc> mTristateFunc;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCSIGNATURE_H
