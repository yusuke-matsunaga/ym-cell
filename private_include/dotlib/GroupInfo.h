#ifndef GROUPINFO_H
#define GROUPINFO_H

/// @file GroupInfo.h
/// @brief GroupInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "ym/ShString.h"
//#include "ym/clib.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GroupInfo GroupInfo.h "GroupInfo.h"
/// @brief グループ構造を表すクラス
//////////////////////////////////////////////////////////////////////
class GroupInfo
{
public:

  //////////////////////////////////////////////////////////////////////
  /// @brief 返り値の型
  //////////////////////////////////////////////////////////////////////
  enum RetType {
    OK,        ///< 成功
    NOT_FOUND, ///< 未指定
    ERROR      ///< エラー
  };


public:

  /// @brief コンストラクタ
  GroupInfo() = default;

  /// @brief デストラクタ
  ~GroupInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  void
  set(
    const AstValue* val ///< [in] パース木の値
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素の辞書を返す．
  const unordered_map<string, vector<const AstValue*>>&
  elem_dict() const
  {
    return mElemDict;
  }

  /// @brief キーワードの値を返す．
  ///
  /// singleton 属性と仮定している．
  RetType
  get_value(
    const char* keyword, ///< [in] キーワード
    const AstValue*& val ///< [out] 値を格納する変数
  ) const;

  /// @brief string の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_string(
    const char* keyword, ///< [in] キーワード
    ShString& val        ///< [out] 値を格納する変数
  ) const;

  /// @brief technology の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_technology(
    const char* keyword, ///< [in] キーワード
    ClibTechnology& val  ///< [out] 値を格納する変数
  ) const;

  /// @brief area の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_area(
    const char* keyword, ///< [in] キーワード
    ClibArea& val        ///< [out] 値を格納する変数
  ) const;

  /// @brief capacitance の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_capacitance(
    const char* keyword, ///< [in] キーワード
    ClibCapacitance& val ///< [out] 値を格納する変数
  ) const;

  /// @brief resistance の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_resistance(
    const char* keyword, ///< [in] キーワード
    ClibResistance& val  ///< [out] 値を格納する変数
  ) const;

  /// @brief time の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 二回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_time(
    const char* keyword, ///< [in] キーワード
    ClibTime& val	 ///< [out] 値を格納する変数
  ) const;

  /// @brief ClibCPV の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR エラー
  ///
  /// OK以外の場合には val の値は変更されない．
  ///
  /// 以下の場合にエラーとなる．
  /// - 2回以上指定されている．
  /// - 値が 'L', 'H', 'N', 'T', 'X' 以外
  RetType
  get_cpv(
    const char* keyword, ///< [in] キーワード
    ClibCPV& val	 ///< [out] 値を格納する変数
  ) const;

  /// @brief ClibVarType の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR エラー
  ///
  /// OK以外の場合には val の値は変更されない．
  ///
  /// 以下の場合にエラーとなる．
  /// - 2回以上指定されている．
  /// - 値が ClibVarType 以外
  RetType
  get_vartype(
    const char* keyword, ///< [in] キーワード
    ClibVarType& val     ///< [out] 値を格納する変数
  ) const;

  /// @brief direction の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_direction(
    const char* keyword, ///< [in] キーワード
    ClibDirection& val   ///< [out] 値を格納する変数
  ) const;

  /// @brief timing_type の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_timing_type(
    const char* keyword,  ///< [in] キーワード
    ClibTimingType& val   ///< [out] 値を格納する変数
  ) const;

  /// @brief timing_sense の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_timing_sense(
    const char* keyword,  ///< [in] キーワード
    ClibTimingSense& val  ///< [out] 値を格納する変数
  ) const;

  /// @brief delay_model の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_delay_model(
    const char* keyword,  ///< [in] キーワード
    ClibDelayModel& val   ///< [out] 値を格納する変数
  ) const;

  /// @brief float_vector の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_float_vector(
    const char* keyword,  ///< [in] キーワード
    vector<double>& val	  ///< [out] 値を格納する変数
  ) const;

  /// @brief expr の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_expr(
    const char* keyword, ///< [in] キーワード
    const AstExpr*& val  ///< [out] 値を格納する変数
  ) const;

  /// @brief complex 形式の float_vector の値を取り出す．
  /// @retval OK 成功
  /// @retval NOT_FOUND 定義されていなかった
  /// @retval ERROR 2回以上定義されていた．
  ///
  /// OK以外の場合には val の値は変更されない．
  RetType
  get_complex_float_vector(
    const char* keyword,  ///< [in] キーワード
    vector<double>& val	  ///< [out] 値を格納する変数
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素の辞書
  unordered_map<string, vector<const AstValue*>> mElemDict;

};

END_NAMESPACE_YM_DOTLIB

#endif // GROUPINFO_H
