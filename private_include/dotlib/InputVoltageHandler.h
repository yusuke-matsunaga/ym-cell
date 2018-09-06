#ifndef INPUTVOLTAGEHANDLER_H
#define INPUTVOLTAGEHANDLER_H

/// @file InputVoltageHandler.h
/// @brief InputVoltageHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str1GroupHandler.h"
#include "ym/HashMap.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class InputVoltageHandler InputVoltageHandler.h "InputVoltageHandler.h"
/// @brief 'input_voltage' Group Statement 用のハンドラ
//////////////////////////////////////////////////////////////////////
class InputVoltageHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  InputVoltageHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~InputVoltageHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'input_voltage' group statement の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstInputVoltage*& dst);


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  read_group_attr(AttrType attr_type,
		  const FileRegion& attr_loc) override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  using ParseFunc = bool (*)(GroupHandler&, AttrType, const FileRegion&);

  // 各属性をパースするための辞書
  HashMap<AttrType, ParseFunc> mFuncHash;

  // vil
  const AstExpr* mVil;

  // vih
  const AstExpr* mVih;

  // vimin
  const AstExpr* mVimin;

  // vimax
  const AstExpr* mVimax;

  // 読み込んだ値
  const AstInputVoltage* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // INPUTVOLTAGEHANDLER_H
