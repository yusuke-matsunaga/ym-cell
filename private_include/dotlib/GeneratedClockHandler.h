#ifndef GENERATEDCLOCKHANDLER_H
#define GENERATEDCLOCKHANDLER_H

/// @file GeneratedClockHandler.h
/// @brief GeneratedClockHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class GeneratedClockHandler GeneratedClockHandler.h "GeneratedClockHandler.h"
/// @brief 'generated_clock' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * ヘッダ名は名前を表す．
/// * Simple Attributes
///   - clock_pin : "name1 [name2 ... ]" ;
///   - master_pin: name ;
///   - divided_by : integer ;
///   - multipled_by : integer ;
///   - invert : true | false ;
///   - duty_cycle : float ;
/// * Complex Attributes
///   - edges ( edge1, edge2, edge3 ) ; // edge1 は integer ?
///   - shifts ( shift1, shift2, shift3 ) ; // shift1 は float ?
//////////////////////////////////////////////////////////////////////
class GeneratedClockHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  GeneratedClockHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~GeneratedClockHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif generated_clock の記述をパースする．
  /// @param[in] dst 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(const AstGeneratedClock*& dst);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock_pin
  const AstStringVector* mClockPin;

  // master_pin
  const AstString* mMasterPin;

  // divided_by
  const AstInt* mDividedBy;

  // multipled_by
  const AstInt* mMultipledBy;

  // invert
  const AstBool* mInvert;

  // duty_cycle
  const AstFloat* mDutyCycle;

  // edges
  const AstInt* mEdges[3];

  // shifts
  const AstFloat* mShifts[3];

};

END_NAMESPACE_YM_DOTLIB

#endif // GENERATEDCLOCKHANDLER_H
