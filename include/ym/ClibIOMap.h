#ifndef CLIBIOMAP_H
#define CLIBIOMAP_H

/// @file ClibIOMap.h
/// @brief ClibIOMap のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibPinMap.h"
#include "ym/BinDec.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibIOMap ClibIOMap.h "ClibIOMap.h"
/// @brief
//////////////////////////////////////////////////////////////////////
class ClibIOMap
{
public:

  /// @brief 空のコンストラクタ
  ClibIOMap() = default;

  /// @brief 1出力用のコンストラクタ
  explicit
  ClibIOMap(
    const vector<ClibPinMap>& input_map ///< [in] 入力ピンのマッピング
  ) : mInputMap{input_map},
      mOutputMap{ClibPinMap{0}}
  {
  }

  /// @brief 多出力用のコンストラクタ
  ClibIOMap(
    const vector<ClibPinMap>& input_map, ///< [in] 入力ピンのマッピング
    const vector<ClibPinMap>& output_map ///< [in] 出力ピンのマッピング
  ) : mInputMap{input_map},
      mOutputMap{output_map}
  {
  }

  /// @brief 入出力ピンを持つ場合のコンストラクタ
  ClibIOMap(
    const vector<ClibPinMap>& input_map,  ///< [in] 入力ピンのマッピング
    const vector<ClibPinMap>& output_map, ///< [in] 出力ピンのマッピング
    const vector<ClibPinMap>& inout_map   ///< [in] 入出力ピンのマッピング
  ) : mInputMap{input_map},
      mOutputMap{output_map},
      mInoutMap{inout_map}
  {
  }

  /// @brief 恒等変換を作るクラス関数
  static
  ClibIOMap
  identity(
    SizeType ni,     ///< [in] 入力数
    SizeType no = 1, ///< [in] 出力数
    SizeType nb = 0  ///< [in] 入出力数
  )
  {
    vector<ClibPinMap> input_map(ni);
    for ( SizeType i = 0; i < ni; ++ i ) {
      input_map[i] = ClibPinMap(i);
    }
    vector<ClibPinMap> output_map(no);
    for ( SizeType i = 0; i < no; ++ i ) {
      output_map[i] = ClibPinMap(i);
    }
    vector<ClibPinMap> inout_map(nb);
    for ( SizeType i = 0; i < nb; ++ i ) {
      inout_map[i] = ClibPinMap(i);
    }
    return ClibIOMap{input_map, output_map, inout_map};
  }

  /// @brief デストラクタ
  ~ClibIOMap() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力数を返す．
  SizeType
  input_num() const
  {
    return mInputMap.size();
  }

  /// @brief 入力のマッピングを返す．
  ClibPinMap
  input_map(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < input_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < input_num() );
    return mInputMap[pos];
  }

  /// @brief 入力のマッピングのリストを返す．
  const vector<ClibPinMap>&
  input_map_list() const
  {
    return mInputMap;
  }

  /// @brief 出力数を返す．
  SizeType
  output_num() const
  {
    return mOutputMap.size();
  }

  /// @brief 出力のマッピングを返す．
  ClibPinMap
  output_map(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < output_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < output_num() );
    return mOutputMap[pos];
  }

  /// @brief 出力のマッピングのリストを返す．
  const vector<ClibPinMap>&
  output_map_list() const
  {
    return mOutputMap;
  }

  /// @brief 入出力数を返す．
  SizeType
  inout_num() const
  {
    return mInoutMap.size();
  }

  /// @brief 入出力のマッピングを返す．
  ClibPinMap
  inout_map(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos && pos < inout_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < inout_num() );
    return mInoutMap[pos];
  }

  /// @brief 入出力のマッピングのリストを返す．
  const vector<ClibPinMap>&
  inout_map_list() const
  {
    return mInoutMap;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    BinEnc& bos ///< [in] 出力先のストリーム
  ) const;

  /// @brief バイナリダンプされた内容を読み込む．
  void
  restore(
    BinDec& bis ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピンのマッピング
  vector<ClibPinMap> mInputMap;

  // 出力ピンのマッピング
  vector<ClibPinMap> mOutputMap;

  // 入出力ピンのマッピング
  vector<ClibPinMap> mInoutMap;

};

/// @relates ClibIOMap
/// @brief ClibIOMap のストリーム出力演算子
ostream&
operator<<(
  ostream& s, ///< [in] 出力先のストリーム
  const ClibIOMap& iomap ///< [in] 入出力のマッピング
);

END_NAMESPACE_YM_CLIB

#endif // CLIBIOMAP_H
