#ifndef LCSIGNATURE_H
#define LCSIGNATURE_H

/// @file LcSignature.h
/// @brief LcSignature のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "lc/libcomp_nsdef.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcSignature LcSignature.h "LcSignature.h"
/// @brief セルの機能を表すシグネチャ
//////////////////////////////////////////////////////////////////////
class LcSignature
{
public:

  /// @brief 種類を表す列挙型
  enum class Type {
    /// @brief 組み合わせ論理
    Logic = 0,
    /// @brief FF
    FF = 1,
    /// @brief ラッチ
    Latch = 2
  };


public:

  /// @brief コンストラクタ
  ///
  /// 内容は不定
  LcSignature() = default;

  /// @brief コピーコンストラクタ
  /// @param[in] src コピー元のオブジェクト
  LcSignature(const LcSignature& src) = default;

  /// @brief 変換付きのコピーコンストラクタ
  /// @param[in] src コピー元のオブジェクト
  /// @param[in] xmap 変換マップ
  LcSignature(const LcSignature& src,
	      const NpnMapM& xmap);

  /// @brief 1出力の論理セルのシグネチャを作るコンストラクタ
  /// @param[in] expr 論理式
  LcSignature(const Expr& expr);

  /// @brief 単純なFFセル/ラッチセルのシグネチャを作るコンストラクタ
  /// @param[in] type 種類 (kFFType/Type::Latch)
  /// @param[in] has_q Q出力の有無
  /// @param[in] has_xq 反転Q出力の有無
  /// @param[in] has_clear クリア端子の有無
  /// @param[in] has_preset プリセット端子の有無
  ///
  /// type == kLogicType は不適
  /// has_q == false && has_xq == false は不適
  LcSignature(Type type,
	      bool has_q,
	      bool has_xq,
	      bool has_clear,
	      bool has_preset);

  /// @brief セルを指定したコンストラクタ
  /// @param[in] cell セル
  LcSignature(const ClibCell* cell);

  /// @brief デストラクタ
  ~LcSignature();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 種類を返す．
  Type
  type() const;

  /// @brief 入力数
  SizeType
  input_num() const;

  /// @brief 出力数
  SizeType
  output_num() const;

  /// @brief クロック/イネーブルの論理関数を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  /// ラッチの時は enable を表す論理関数を返す．
  TvFunc
  clock() const;

  /// @brief 次状態関数を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  /// ラッチの時は data_in を表す論理関数を返す．
  TvFunc
  next_state() const;

  /// @brief クリア条件を持つ時に true を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  bool
  has_clear() const;

  /// @brief クリア条件を表す論理関数を返す．
  ///
  /// has_clear() == true の時のみ意味を持つ．
  TvFunc
  clear_func() const;

  /// @brief プリセット条件を持つ時に true を返す．
  ///
  /// type() == Type::FF, Type::Latch の時のみ意味を持つ．
  bool
  has_preset() const;

  /// @brief プリセット条件を表す論理関数を返す．
  ///
  /// has_preset() == true の時のみ意味を持つ．
  TvFunc
  preset_func() const;

  /// @brief 論理式を持つ時に true を返す．
  /// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
  bool
  has_logic(int opos) const;

  /// @brief 出力の論理関数を返す．
  /// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
  ///
  /// has_state_var() == true の時は変数の数が input_num() + 2 となる．
  TvFunc
  output_func(int opos) const;

  /// @brief tristate 条件を持つ時に true を返す．
  /// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
  bool
  is_tristate(int opos) const;

  /// @brief tristate 条件を返す．
  /// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
  ///
  /// is_tristate(opos) == false の時の値は不定
  TvFunc
  tristate_func(int opos) const;

  /// @brief 内容を表す文字列を作る．
  string
  str() const;

  /// @brief 等価比較演算子
  bool
  operator==(const LcSignature& right) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief Logic タイプにセットする．
  void
  set_Logic();

  /// @brief FF タイプにセットする．
  void
  set_FF();

  /// @brief Latch タイプにセットする．
  void
  set_Latch();


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
  vector<ymuint> mOutputBits;

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


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 種類を返す．
inline
LcSignature::Type
LcSignature::type() const
{
  ymuint b0 = mTypeBits[0];
  ymuint b1 = mTypeBits[1];
  return static_cast<Type>(b0 | (b1 << 1));
}

// @brief Logic タイプにセットする．
inline
void
LcSignature::set_Logic()
{
  mTypeBits.set(0, 0);
  mTypeBits.set(1, 0);
}

// @brief FF タイプにセットする．
inline
void
LcSignature::set_FF()
{
  mTypeBits.set(0, 1);
  mTypeBits.set(1, 0);
}

// @brief Latch タイプにセットする．
inline
void
LcSignature::set_Latch()
{
  mTypeBits.set(0, 0);
  mTypeBits.set(1, 1);
}

// @brief 入力数
inline
SizeType
LcSignature::input_num() const
{
  return mInputNum;
}

// @brief 出力数
inline
SizeType
LcSignature::output_num() const
{
  return mOutputNum;
}

// @brief クロック/イネーブルの論理関数を返す．
//
// type() == Type::FF, Type::Latch の時のみ意味を持つ．
inline
TvFunc
LcSignature::clock() const
{
  return mClockFunc;
}

// @brief 次状態関数を返す．
//
// type() == Type::FF, Type::Latch の時のみ意味を持つ．
// ラッチの時は data_in を表す論理関数を返す．
inline
TvFunc
LcSignature::next_state() const
{
  return mNextStateFunc;
}

// @brief クリア条件を持つ時に true を返す．
inline
bool
LcSignature::has_clear() const
{
  return mTypeBits[2];
}

// @brief クリア条件を表す論理関数を返す．
//
// has_clear() == true の時のみ意味を持つ．
inline
TvFunc
LcSignature::clear_func() const
{
  return mClearFunc;
}

// @brief プリセット条件を持つ時に true を返す．
inline
bool
LcSignature::has_preset() const
{
  return mTypeBits[3];
}

// @brief プリセット条件を表す論理関数を返す．
//
// has_preset() == true の時のみ意味を持つ．
inline
TvFunc
LcSignature::preset_func() const
{
  return mPresetFunc;
}

// @brief 論理式を持つ時に true を返す．
// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
inline
bool
LcSignature::has_logic(int opos) const
{
  ASSERT_COND( opos < output_num() );
  return static_cast<bool>((mOutputBits[opos] >> 0) & 1U);
}

// @brief 出力の論理関数を返す．
// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
//
// has_state_var() == true の時は変数の数が input_num() + 2 となる．
inline
TvFunc
LcSignature::output_func(int opos) const
{
  ASSERT_COND( opos < output_num() );
  return mOutputFunc[opos];
}

// @brief tristate 条件を持つ時に true を返す．
// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
inline
bool
LcSignature::is_tristate(int opos) const
{
  ASSERT_COND( opos < output_num() );
  return static_cast<bool>((mOutputBits[opos] >> 1) & 1U);
}

// @brief tristate 条件を返す．
// @param[in] opos 出力位置 ( 0 <= opos < output_num() )
//
// is_tristate(opos) == false の時の値は不定
inline
TvFunc
LcSignature::tristate_func(int opos) const
{
  ASSERT_COND( opos < output_num() );
  return mTristateFunc[opos];
}

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCSIGNATURE_H
