#ifndef ASTTIMINGTYPE_H
#define ASTTIMINGTYPE_H

/// @file AstTimingType.h
/// @brief AstTimingType の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTimingType AstTimingType.h "AstTimingType.h"
/// @brief timing type のノードを表すクラス
//////////////////////////////////////////////////////////////////////
class AstTimingType :
  public AstValue
{
public:

  /// @brief コンストラクタ
  AstTimingType(ClibTimingType value,        ///< [in] 値
		const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
    : AstValue(val_loc),
      mValue{value}
  {
  }

  /// @brief デストラクタ
  ~AstTimingType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief TimingType を返す．
  ClibTimingType
  timing_type_value() const override;

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s) const override; ///< [in] 出力先のストリーム


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ClibTimingType mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMINGTYPE_H
