#ifndef DOMAINHANDLER_H
#define DOMAINHANDLER_H

/// @file DomainHandler.h
/// @brief DomainHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DomainHandler DomainHandler.h "DomainHandler.h"
/// @brief domain group 用のハンドラ
///
/// 現時点ではこのクラスは syntactical にパースするだけ．
//////////////////////////////////////////////////////////////////////
class DomainHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  DomainHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~DomainHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif timing group statement の記述をパースする．
  /// @return 正しく読み込めたら true を返す．
  bool
  parse_value();


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
  /// @retval true 正常に処理した．
  /// @retval false 処理中にエラーが起こった．
  bool
  read_group_attr(AttrType attr_type,
		  const FileRegion& attr_loc) override;

  /// @brief グループ記述の終わり
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で使われる下請け関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_DOTLIB

#endif // DOMAINHANDLER_H
