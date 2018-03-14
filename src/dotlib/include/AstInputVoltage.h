#ifndef ASTINPUTVOLTAGE_H
#define ASTINPUTVOLTAGE_H

/// @file AstInputVoltage.h
/// @brief AstInputVoltage のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstInputVoltage AstInputVoltage.h "AstInputVoltage.h"
/// @brief input voltage を表すクラス
//////////////////////////////////////////////////////////////////////
class AstInputVoltage :
  public AstNode
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] vil 'vil'
  /// @param[in] vih 'vih'
  /// @param[in] vimin 'vimin'
  /// @param[in] vimax 'vimax'
  AstInputVoltage(const FileRegion& loc,
		  const AstString* name,
		  const AstExpr* vil,
		  const AstExpr* vih,
		  const AstExpr* vimin,
		  const AstExpr* vimax);

  /// @brief デストラクタ
  virtual
  ~AstInputVoltage();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief 'vil' を返す．
  const AstExpr*
  vil() const;

  /// @brief 'vih' を返す．
  const AstExpr*
  vih() const;

  /// @brief 'vimin' を返す．
  const AstExpr*
  vimin() const;

  /// @brief 'vimax' を返す．
  const AstExpr*
  vimax() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const AstString* mName;

  // vil
  const AstExpr* mVil;

  // vih
  const AstExpr* mVih;

  // vimin
  const AstExpr* mViMin;

  // vimax
  const AstExpr* mViMax;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstInputVoltage::name() const
{
  return mName;
}

// @brief 'vil' を返す．
inline
const AstExpr*
AstInputVoltage::vil() const
{
  return mVil;
}

// @brief 'vih' を返す．
inline
const AstExpr*
AstInputVoltage::vih() const
{
  return mVih;
}

// @brief 'vimin' を返す．
inline
const AstExpr*
AstInputVoltage::vimin() const
{
  return mViMin;
}

// @brief 'vimax' を返す．
inline
const AstExpr*
AstInputVoltage::vimax() const
{
  return mViMax;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTINPUTVOLTAGE_H
