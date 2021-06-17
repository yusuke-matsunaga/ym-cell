#ifndef ASTTECHNOLOGY_H
#define ASTTECHNOLOGY_H

/// @file AstTechnology.h
/// @brief AstTechnology のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTechnology AstTechnology.h "AstTechnology.h"
/// @brief technology のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTechnology :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstTechnology(ClibTechnology value,       ///< [in] 値
		const FileRegion& val_loc); ///< [in] 値のファイル上の位置

  /// @brief デストラクタ
  ~AstTechnology() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief Technology を返す．
  ClibTechnology
  technology_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTechnology mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTECHNOLOGY_H
