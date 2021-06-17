#ifndef ASTINTVECTOR_H
#define ASTINTVECTOR_H

/// @file AstIntVector.h
/// @brief AstIntVector のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstIntVector AstIntVector.h "AstIntVector.h"
/// @brief 整数値のベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class AstIntVector :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstIntVector(const vector<int>& value, ///< [in] 値
	       const FileRegion& loc);   ///< [in] ファイル上の位置

  /// @brief デストラクタ
  ~AstIntVector() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ベクタを取り出す．
  vector<int>
  int_vector_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 本体の配列
  vector<int> mBody;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTINTVECTOR_H
