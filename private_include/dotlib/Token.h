#ifndef TOKEN_H
#define TOKEN_H

/// @file Token.h
/// @brief Token のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "dotlib/TokenType.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class Token Token.h "Token.h"
/// @brief トークンを表すクラス
//////////////////////////////////////////////////////////////////////
class Token
{
public:

  /// @brief 空のコンストラクタ
  Token() = default;

  /// @brief 内容を指定したコンストラクタ
  Token(TokenType type,        ///< [in] トークンの種類
	const FileRegion& loc) ///< [in] トークンの位置
    : mType{type},
      mLoc{loc}
  {
  }

  /// @brief デストラクタ
  ~Token() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief トークンの種類を返す．
  TokenType
  type() const { return mType; }

  /// @brief トークンの位置を返す．
  FileRegion
  loc() const { return mLoc; }

  /// @brief トークンを表す文字列を返す．
  operator string() const
  {
    ostringstream buf;
    buf << loc() << ": " << type();
    return buf.str();
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 種類
  TokenType mType{TokenType::ERROR};

  // 位置
  FileRegion mLoc{};

};

END_NAMESPACE_YM_DOTLIB

#endif // TOKEN_H
