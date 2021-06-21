
/// @file Parser.cc
/// @brief Parser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstValue.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief Group Statement を読み込む．
// @retrun 結果の AstAttr を返す．
//
// エラーが起こったら nullptr を返す．
AstAttrPtr
Parser::parse_group_statement(const AttrKwd& attr,
			      HeaderHandler& header_handler,
			      const AttrHandlerDict& attr_handler_dict)
{
  auto header_value{parse_header(header_handler)};
  if ( header_value == nullptr ) {
    return {};
  }

  // グループ本体の始まり
  Token lcb_token = mScanner.read_and_verify(TokenType::LCB);
  if ( lcb_token.type() != TokenType::LCB ) {
    return {};
  }

  // 仮想関数の呼び出し
  vector<AstAttrPtr> child_list;
  for ( ; ; ) {
    Token token = mScanner.read_token();
    if ( token.type() == TokenType::NL ) {
      // 改行は読み飛ばす．
      continue;
    }
    if ( token.type() == TokenType::RCB ) {
      FileRegion rcb_loc{token.loc()};

      // グループ本体の終わり．
      Token token = mScanner.read_and_verify(TokenType::NL);
      if ( token.type() != TokenType::NL ) {
	return {};
      }

      FileRegion loc{lcb_token.loc(), rcb_loc};
      auto group_value{AstValue::new_group(std::move(header_value), child_list, loc)};
      return AstAttrPtr{new AstAttr(attr, std::move(group_value))};
    }

    // 子供の要素を読み込む．
    AttrKwd child_attr{mScanner.read_attr()};
    if ( child_attr.type() == AttrType::none ) {
      return {};
    }
    if ( attr_handler_dict.count(child_attr.type()) > 0 ) {
      auto handler{attr_handler_dict.at(child_attr.type())};
      auto child{handler(*this, child_attr)};
      if ( child == nullptr ) {
	return {};
      }
      child_list.push_back(std::move(child));
    }
    else {
      // 対応するハンドラが登録されていない．
      syntax_error(child_attr);
      return {};
    }
  }
}

// @brief 'cell' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_cell(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sCellGroupDict);
}

// @brief 'domain' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_domain(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sDomainGroupDict);
}

// @brief 'ff' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_ff(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrStrHeader, sFFGroupDict);
}

// @brief 'ff_bank' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_ff_bank(const AttrKwd& attr)
{
  // ヘッダが異なるだけで本体は 'ff' group と同じ
  return parse_group_statement(attr, sStrStrIntHeader, sFFGroupDict);
}

// @brief 'input_voltage' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_input_voltage(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sInputVoltageGroupDict);
}

// @brief 'latch' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_latch(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrStrHeader, sLatchGroupDict);
}

// @brief 'latch_bank' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_latch_bank(const AttrKwd& attr)
{
  // ヘッダが異なるだけで本体は 'latch' group と同じ
  return parse_group_statement(attr, sStrStrIntHeader, sLatchGroupDict);
}

// @brief 'Library' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_library(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sLibraryGroupDict);
}

// @brief 'OutputVoltage' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_output_voltage(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sOutputVoltageGroupDict);
}

// @brief 'pin' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_pin(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrListHeader, sPinGroupDict);
}

// @brief 'table' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_table(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sTableGroupDict);
}

// @brief 'lut_template' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_template(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrHeader, sTemplateGroupDict);
}

// @brief 'timing' Group Statement のパースを行う．
AstAttrPtr
Parser::parse_timing(const AttrKwd& attr)
{
  return parse_group_statement(attr, sStrListHeader, sTimingGroupDict);
}

END_NAMESPACE_YM_DOTLIB
