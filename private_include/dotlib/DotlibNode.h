#ifndef DOTLIBNODE_H
#define DOTLIBNODE_H

/// @file DotlibNode.h
/// @brief DotlibNode のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibNode DotlibNode.h "DotlibNode.h"
/// @brief パース木の構造を表すための基底クラス
///
/// ノードの種類は以下の通り
/// - 数値型
///   * 整数型:       kInt    int
///   * 浮動小数点型: kFloat  double
/// - ベクタ型:       kFloatVector vector<double>
/// - 文字列型:       kString ShString
/// - 演算子型
///   * +演算:        kPlus   (DotlibNode*, NodelibNode*)
///   * -演算:        kMinus  (DotlibNode*, NodelibNode*)
///   * *演算:        kMult   (DotlibNode*, NodelibNode*)
///   * /演算:        kDiv    (DotlibNode*, NodelibNode*)
///   * NOT演算:      kNot    DotlibNode*
///   * AND演算:      kAnd    (DotlibNode*, NodelibNode*)
///   * OR演算:       kOr     (DotlibNode*, NodelibNode*)
///   * XOR演算:      kXor    (DotlibNode*, NodelibNode*)
/// - リスト型:       kList   [DotlibNode* ...]
/// - 属性値型
///   * ClibTechnology:
///   * ClibDelayModel:
///   * ClibCellPinDirection:
///   * ClibTimingSense:
///   * ClibTimingType:
///   * ClibVarType:
//////////////////////////////////////////////////////////////////////
class DotlibNode
{
public:

  /// @brief 型の定義
  enum Type {
    /// @brief 整数型の定数
    kInt,
    /// @brief 浮動小数点型の定数
    kFloat,
    /// @brief 文字列型の定数
    kString,
    /// @brief 浮動小数点数ベクタ型の定数
    kVector,
    /// @brief + 演算子
    kPlus,
    /// @brief - 演算子
    kMinus,
    /// @brief * 演算子
    kMult,
    /// @brief / 演算子
    kDiv,
    /// @brief NOT 演算子
    kNot,
    /// @brief AND 演算子
    kAnd,
    /// @brief OR 演算子
    kOr,
    /// @brief XOR 演算子
    kXor,
    /// @brief リスト
    kList,
    /// @brief グループ
    kGroup,
    /// @brief ClibTechnology
    kTechnology,
    /// @brief ClibDelayModel
    kDelayModel,
    /// @brief ClibCellPinDirection
    kCellPinDirection,
    /// @brief ClibTimingSense
    kTimingSense,
    /// @brief ClibTimingType
    kTimingType,
    /// @brief ClibVarType
    kVarType,
  };


protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibNode(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~DotlibNode();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照するための関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // パーズ用の便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 1つの文字列からなるリストの場合に文字列を返す．
  ///
  /// 仮定が外れたらアボートする．
  virtual
  ShString
  get_string_from_value_list() const;

  /// @brief 2つの文字列からなるリストの内容を取り出す．
  /// @param[out] str1 1つ目の文字列を格納する変数
  /// @param[out] str2 2つ目の文字列を格納する変数
  /// @retval true 正しく読み込めた．
  /// @retval false エラーが起こった．
  /// @note エラーは MsgMgr に出力する．
  virtual
  bool
  expect_string_pair(ShString& str1,
		     ShString& str2) const;

  /// @brief float 値を取り出す．
  ///
  /// 型が違ったらエラーを MsgMgr に出力する．
  virtual
  bool
  expect_float(double& value) const;

  /// @brief 文字列を取り出す．
  ///
  /// 型が違ったらエラーを MsgMgr に出力する．
  virtual
  bool
  expect_string(ShString& value) const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いる便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief インデント数分だけ空白を出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  static
  void
  dump_indent(ostream& s,
	      int indent);

  /// @brief 文字列を出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] str 対象の文字列
  ///
  /// str 中に [a-zA-Z0-9_] 以外の文字が含まれていたら
  /// " " で囲んで出力する．
  static
  void
  dump_string(ostream& s,
	      const char* str);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ファイル上の位置
  FileRegion mLoc;

};

/// @brief ストリーム出力演算子
inline
ostream&
operator<<(ostream& s,
	   const DotlibNode* node)
{
  node->dump(s, 0);
  return s;
}


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ファイル上の位置を返す．
inline
FileRegion
DotlibNode::loc() const
{
  return mLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODE_H
