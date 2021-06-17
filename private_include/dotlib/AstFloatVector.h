#ifndef ASTFLOATVECTOR_H
#define ASTFLOATVECTOR_H

/// @file AstFloatVector.h
/// @brief AstFloatVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstFloatVector AstFloatVector.h "AstFloatVector.h"
/// @brief ベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstFloatVector :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstFloatVector(const vector<double>& value_list, ///< [in] 値のリスト
		 const FileRegion& loc);           ///< [in] ファイル上の位置

  /// @brief デストラクタ
  ~AstFloatVector() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタの全体を取り出す．
  vector<double>
  float_vector_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ベクタの本体
  vector<double> mBody;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTFLOATVECTOR_H
