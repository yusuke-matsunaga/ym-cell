#ifndef ASTNODE_H
#define ASTNODE_H

/// @file AstNode.h
/// @brief AstNode のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AttrType.h"
#include "ym/FileRegion.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstNode AstNode.h "AstNode.h"
/// @brief パース木の構造を表すための基底クラス
///
/// ノードの種類は以下の通り
/// - 数値型
///   * 整数型:            AstInt
///   * 浮動小数点型:      AstFloat
/// - 文字列型:            AstString
/// - ベクタ型
///   * 整数型:            AstIntVector
///   * 浮動小数点型:      AstFloatVector
///   * 文字列型:          AstStringVector
/// - 属性値型
///   * ClibTechnology:
///   * ClibDelayModel:
///   * ClibCellPinDirection:
///   * ClibTimingSense:
///   * ClibTimingType:
///   * ClibVarType:
/// - 式型:                AstExpr
///   * NOT演算:           AstNot
///   * 2項演算:           AstOpr
///   * ブール定数:        AstBoolExpr
///   * 実数定数:          AstFloatExpr
///   * シンボル定数:      AstVDD, AstVSS, AstVcc
/// - 複合型
///   * 単位               AstUnit
///   * 折れ線             AstPieceWise
///   * input_voltage:     AstInputVoltage
///   * output_voltage:    AstOutputVoltage
///   * timing:            AstTiming
///   * pin:               AstPin
///   * cell:              AstCell
///   * lu_table_template: AstTemplate
///   * lut:               AstLut
///   * ff:                AstFF
///   * ff_bank:           AstFF
///   * Latch:             AstLatch
///   * Latch_bank:        AstLatch
///   * StateTable:        AstStateTable
///
/// 共通の仮想関数は dump() のみ．
//////////////////////////////////////////////////////////////////////
class AstNode
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
   AstNode(const FileRegion& loc); ///< [in] ファイル上の位置

  /// @brief デストラクタ
  virtual
  ~AstNode();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照するための関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ファイル上の位置を返す．
  FileRegion
  loc() const
  {
    return mLoc;
  }

  /// @brief 内容をストリーム出力する．
  virtual
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いる便利関数
  //////////////////////////////////////////////////////////////////////

  /// @brief インデント数分だけ空白を出力する．
  static
  void
  dump_indent(ostream& s,  ///< [in] 出力先のストリーム
	      int indent); ///< [in] インデント量

  /// @brief 文字列を出力する．
  ///
  /// str 中に [a-zA-Z0-9_] 以外の文字が含まれていたら
  /// " " で囲んで出力する．
  static
  void
  dump_string(ostream& s,       ///< [in] 出力先のストリーム
	      const char* str); ///< [in] 対象の文字列


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
	   const AstNode* node)
{
  node->dump(s, 0);
  return s;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTNODE_H
