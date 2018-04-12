#ifndef ASTOUTPUTvolTAGE_H
#define ASTOUTPUTvolTAGE_H

/// @file AstOutputVoltage.h
/// @brief AstOutputVoltage のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "AstNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstOutputVoltage AstOutputVoltage.h "AstOutputVoltage.h"
/// @brief output voltage を表すクラス
//////////////////////////////////////////////////////////////////////
class AstOutputVoltage :
  public AstNode
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] name 名前
  /// @param[in] vol 'vol'
  /// @param[in] voh 'voh'
  /// @param[in] vomin 'vomin'
  /// @param[in] vomax 'vomax'
  AstOutputVoltage(const FileRegion& loc,
		   const AstString* name,
		   const AstExpr* vol,
		   const AstExpr* voh,
		   const AstExpr* vomin,
		   const AstExpr* vomax);

  /// @brief デストラクタ
  virtual
  ~AstOutputVoltage();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief 'vol' を返す．
  const AstExpr*
  vol() const;

  /// @brief 'voh' を返す．
  const AstExpr*
  voh() const;

  /// @brief 'vomin' を返す．
  const AstExpr*
  vomin() const;

  /// @brief 'vomax' を返す．
  const AstExpr*
  vomax() const;

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

  // vol
  const AstExpr* mVol;

  // voh
  const AstExpr* mVoh;

  // vomin
  const AstExpr* mVoMin;

  // vomax
  const AstExpr* mVoMax;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前を返す．
inline
const AstString*
AstOutputVoltage::name() const
{
  return mName;
}

// @brief 'vol' を返す．
inline
const AstExpr*
AstOutputVoltage::vol() const
{
  return mVol;
}

// @brief 'voh' を返す．
inline
const AstExpr*
AstOutputVoltage::voh() const
{
  return mVoh;
}

// @brief 'vomin' を返す．
inline
const AstExpr*
AstOutputVoltage::vomin() const
{
  return mVoMin;
}

// @brief 'vomax' を返す．
inline
const AstExpr*
AstOutputVoltage::vomax() const
{
  return mVoMax;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTOUTPUTvolTAGE_H
